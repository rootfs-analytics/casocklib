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
 * \file casock/rpc/protobuf/client/RPCCallController.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CALL_CONTROLLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CALL_CONTROLLER_H_

#include <string>
#include <list>

#include <google/protobuf/service.h>

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCallController : public google::protobuf::RpcController
        {
          public:
            RPCCallController ();

          public:
            void Reset(); // from google::protobuf::RpcController
            bool Failed() const; // from google::protobuf::RpcController
            std::string ErrorText() const; // from google::protobuf::RpcController
            void StartCancel(); // from google::protobuf::RpcController
            void SetFailed(const std::string&); // from google::protobuf::RpcController
            bool IsCanceled() const; // from google::protobuf::RpcController
            void NotifyOnCancel(google::protobuf::Closure*); // from google::protobuf::RpcController

          private:
            bool failed;
            std::string reason;
            bool canceled;
            std::list<google::protobuf::Closure*> cancelListeners;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT_RPC_CALL_CONTROLLER_H_
