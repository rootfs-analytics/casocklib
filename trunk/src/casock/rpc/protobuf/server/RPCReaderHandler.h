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
 * \file casock/rpc/protobuf/server/RPCReaderHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_READER_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_READER_HANDLER_H_

#include <stdlib.h>

//#include <tr1/unordered_map>
//using std::tr1::unordered_map;

#include "casock/util/types.h"
#include "casock/util/Lockable.h"
#include "casock/util/LockableHash.h"
#include "casock/base/Handler.h"
#include "casock/rpc/protobuf/server/RPCServerCommunicator.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        class RPCCall;
        class RPCCallQueue;
        using casock::util::LockableHash;

        class RPCReaderHandler : public casock::base::Handler, private casock::util::Lockable
        {
          public:
            RPCReaderHandler (const int& fd, RPCCallQueue& rCallQueue);

          private:
            void destroy () { delete this; }
            void invalidateCalls ();

          public:
            void handle ();
            RPCServerCommunicator& communicator () { return mCommunicator; }
            void registerCall (const uint32& id, const RPCCall* const pCall);
            void unregisterCall (const uint32& id);
            const bool tryUnregisterCall (const uint32& id);

          private:
            RPCServerCommunicator                 mCommunicator;
            LockableHash<uint32, const RPCCall*>  mCallHash;
            RPCCallQueue&                         mrCallQueue;

            size_t len;
            stringstream sstream;
        };
      }
    }
  }
}


#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_READER_HANDLER_H_

