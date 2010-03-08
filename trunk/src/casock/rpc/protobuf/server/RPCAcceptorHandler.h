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
 * \file casock/rpc/protobuf/server/RPCAcceptorHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_ACCEPTOR_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_ACCEPTOR_HANDLER_H_

#include "casock/server/SockAcceptorHandler.h"


namespace casock {
  namespace base {
    class FileDescriptor;
  }

  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCallQueue;

        class RPCAcceptorHandler : public casock::server::SockAcceptorHandler
        {
          public:
            RPCAcceptorHandler (const casock::base::FileDescriptor* const pFileDescriptor, RPCCallQueue& rCallQueue);

          private:
            void createHandler (const int& fd);

          private:
            RPCCallQueue& mrCallQueue;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER_RPC_ACCEPTOR_HANDLER_H_
