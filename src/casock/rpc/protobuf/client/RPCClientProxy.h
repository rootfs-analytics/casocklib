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
 * \file casock/rpc/protobuf/client/RPCClientProxy.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CLIENT_PROXY_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CLIENT_PROXY_H_

#include <string>

#include "casock/rpc/protobuf/client/RPCChannel.h"
#include "casock/util/LockableHash.h"

namespace casock {
  namespace client {
    class ClientSocket;
  }

  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcService;
      }

      namespace client {
        class RPCClientCommunicator;
        class RPCChannel;
        class RPCReaderHandler;
        class RPCCall;
        class RPCCallQueue;
        class RPCCallHandler;
        using casock::util::LockableHash;
        using casock::client::ClientSocket;
        using casock::rpc::protobuf::api::RpcService;

        class RPCClientProxy : public google::protobuf::RpcChannel
        {
          public:
            RPCClientProxy (const std::string& host, const unsigned int& port);

          public:
            void CallMethod (const google::protobuf::MethodDescriptor*, google::protobuf::RpcController*, const google::protobuf::Message*, google::protobuf::Message*, google::protobuf::Closure*);

//          private:
//            static void callback ();

          private:
            ClientSocket*     mpClientSocket;
            RPCChannel*       mpChannel;
            RPCReaderHandler* mpReaderHandler;
            RpcService*       mpService;

            LockableHash<uint32, RPCCall*>  mCallHash;

            RPCCallQueue*     mpCallQueue;
            RPCCallHandler*   mpCallHandler;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CLIENT_PROXY_H_
