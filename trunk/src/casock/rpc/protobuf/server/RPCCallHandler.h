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
 * \file casock/rpc/protobuf/server/RPCCallHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_CALL_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_CALL_HANDLER_H_

#include "casock/util/Thread.h"

namespace google {
  namespace protobuf {
    class Message;
    class RpcController;
    class Service;
  }
}

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCall;
        class RPCCallQueue;

        class RPCCallHandler : public casock::util::Thread
        {
          private:
            class RPCCallEntry
            {
              public:
                RPCCallEntry (RPCCall* pCall, google::protobuf::Message* pResponse, google::protobuf::RpcController* pController) : mpCall (pCall), mpResponse (pResponse), mpController (pController) { }
                virtual ~RPCCallEntry ();

              public:
                RPCCall* call () { return mpCall; }
                google::protobuf::Message* response () { return mpResponse; }
                google::protobuf::RpcController* controller () { return mpController; }

              private:
                RPCCall*                          mpCall;
                google::protobuf::Message*        mpResponse;
                google::protobuf::RpcController*  mpController;
            };

          public:
            RPCCallHandler (RPCCallQueue& rCallQueue, google::protobuf::Service* pService);

          public:
            static void callback (RPCCallEntry* pCallEntry);

          public:
            void run ();

          private:
            RPCCallQueue& mrCallQueue;
            google::protobuf::Service* mpService;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_CALL_HANDLER_H_
