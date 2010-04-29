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
 * \file casock/rpc/protobuf/server/RPCCall.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_H_

#include "casock/util/Logger.h"
#include "casock/util/Lockable.h"
#include "casock/util/SafeLock.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcRequest;
        class RpcResponse;
      }

      namespace server {
        using casock::rpc::protobuf::api::RpcRequest;
        using casock::rpc::protobuf::api::RpcResponse;

        template<typename _TpResponseHandler>
          class RPCCall : public casock::util::Lockable
        {
          public:
            RPCCall (_TpResponseHandler* const pResponseHandler, const RpcRequest* const pRequest);
            virtual ~RPCCall ();

          public:
            void invalidateHandler ();
            void callback (const RpcResponse& response);
            const RpcRequest* const request () { return mpRequest; }

          private:
            _TpResponseHandler*     mpResponseHandler;
            const RpcRequest* const mpRequest;
        };


        /*
         * template definitions
         */

        template<typename _TpResponseHandler>
          RPCCall<_TpResponseHandler>::RPCCall (_TpResponseHandler* const pResponseHandler, const RpcRequest* const pRequest)
          : mpResponseHandler (pResponseHandler), mpRequest (pRequest)
          {
            if (mpResponseHandler)
              mpResponseHandler->registerCall (mpRequest->id (), this);
          }

        template<typename _TpResponseHandler>
          RPCCall<_TpResponseHandler>::~RPCCall ()
          {
            /*
             * We need unregister the call.
             * We need a way to avoid deadlock when a disconnect happens:
             */

            bool unregistered = false;

            do
            {
              lock ();
              if (mpResponseHandler)
              {
                LOGMSG (LOW_LEVEL, "RPCCall::~RPCCall () - trying to unregister from response handler [%p]...\n", __FUNCTION__, mpResponseHandler);
                unregistered = mpResponseHandler->tryUnregisterCall (mpRequest->id ());
              }
              unlock ();
            } while (! unregistered && ! sleep (1));

            delete mpRequest;
          }

        template<typename _TpResponseHandler>
          void RPCCall<_TpResponseHandler>::invalidateHandler ()
          {
            casock::util::SafeLock lock (*this);
            mpResponseHandler = NULL;
          }

        template<typename _TpResponseHandler>
          void RPCCall<_TpResponseHandler>::callback (const RpcResponse& response)
          {
            if (mpResponseHandler)
              mpResponseHandler->callback (response);
          }
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_H_
