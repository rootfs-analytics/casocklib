/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/rpc/protobuf/server/RPCCallHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCCallHandler.h"

#include <google/protobuf/descriptor.h>

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"
#include "casock/rpc/protobuf/server/RPCReaderHandler.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        using casock::rpc::protobuf::api::RpcRequest;
        using casock::rpc::protobuf::api::RpcResponse;

        RPCCallHandler::RPCCallHandler (RPCCallQueue& rCallQueue, google::protobuf::Service* pService) : mrCallQueue (rCallQueue), mpService (pService)
        {
        }

        void RPCCallHandler::callback (RPCCallEntry* pCallEntry)
        {
          RPCCall* pCall = pCallEntry->call ();

          RpcResponse* pRpcResponse = new RpcResponse ();
          pRpcResponse->set_id (pCall->request ()->id ());
          pRpcResponse->set_type (casock::rpc::protobuf::api::RESPONSE_TYPE_OK);
          pRpcResponse->set_response (pCallEntry->response ()->SerializeAsString ());

          pCall->lock ();
          if (pCall->handler ())
            pCall->handler ()->communicator ().write (pRpcResponse);
          pCall->unlock ();

          delete pCallEntry;
        }

        void RPCCallHandler::run ()
        {
          while (true)
          {
            LOGMSG (LOW_LEVEL, "RPCCallHandler::%s () - calling mrCallQueue.get ()...\n", __FUNCTION__);
            RPCCall* pCall = mrCallQueue.get ();
            LOGMSG (LOW_LEVEL, "RPCCallHandler::%s () - got pCall [%p]!\n", __FUNCTION__, pCall);

            const RpcRequest* const pRpcRequest = pCall->request ();

            /*
            RpcResponse* pRpcResponse = new RpcResponse ();
            pRpcResponse->set_id (pRpcRequest->id ());
            pRpcResponse->set_type (casock::rpc::protobuf::api::RESPONSE_TYPE_ERROR);

            pCall->lock ();
            if (pCall->handler ())
              pCall->handler ()->communicator ().write (pRpcResponse);
            pCall->unlock ();
            */

            //////

            const google::protobuf::MethodDescriptor* method = mpService->GetDescriptor ()->FindMethodByName (pRpcRequest->operation ());

            if (method != NULL)
            {
              LOGMSG (NO_DEBUG, "RPCCallHandler::%s () - OK\n", __FUNCTION__);

              google::protobuf::Message* request = mpService->GetRequestPrototype (method).New ();
              request->ParseFromString (pRpcRequest->request ());
              google::protobuf::RpcController* controller = NULL; // TODO: create a controller
              google::protobuf::Message* response = mpService->GetResponsePrototype (method).New ();
              google::protobuf::Closure* closure = google::protobuf::NewCallback (RPCCallHandler::callback, new RPCCallEntry (pCall, response, controller));

              mpService->CallMethod (method, controller, request, response, closure);
            }
            else
              LOGMSG (NO_DEBUG, "RPCCallHandler::%s () - no method called [%s]\n", __FUNCTION__, pRpcRequest->operation ().c_str ());

//            delete pRpcResponse;
//            delete pCall;
          }
        }

        RPCCallHandler::RPCCallEntry::~RPCCallEntry ()
        {
          delete mpCall;
          delete mpResponse;
          delete mpController;
        }
      }
    }
  }
}
