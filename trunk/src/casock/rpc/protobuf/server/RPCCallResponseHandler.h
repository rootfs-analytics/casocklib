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
 * \file casock/rpc/protobuf/server/RPCCallResponseHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_

#include "casock/util/LockableHash.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class RpcResponse;
      }
    }

    namespace protobuf {
      namespace server {
        template<typename _TpResponseHandler>
          class RPCCall;

        using casock::util::LockableHash;
        using casock::rpc::protobuf::api::RpcResponse;

        class RPCCallResponseHandler : private casock::util::Lockable
        {
          protected:
            void invalidateCalls ()
            {
              /*
                 casock::util::SafeLock lock (mCallHash);

                 unordered_map<uint32, const RPCCall*>::const_iterator it;
                 unordered_map<uint32, const RPCCall*>::const_iterator itEnd = mCallHash.end ();

                 for (it = mCallHash.begin (); it != itEnd; ++it)
                 it->second->invalidateHandler ();

                 mCallHash.clear ();
               */
            }

          public:
            void registerCall (const uint32& id, const RPCCall<RPCCallResponseHandler>* const pCall)
            {
              casock::util::SafeLock lock (mCallHash);
              mCallHash [id] = pCall;
            }

            void unregisterCall (const uint32& id)
            {
              casock::util::SafeLock lock (mCallHash);
              mCallHash.erase (id);
            }

            const bool tryUnregisterCall (const uint32& id)
            {
              bool ret = false;

              if ((ret = mCallHash.tryLock ()) == true)
              {
                mCallHash.erase (id);
                mCallHash.unlock ();
              }

              return ret;
            }

            virtual void callback (const RpcResponse& response) = 0;

          private:
            LockableHash<uint32, const RPCCall<RPCCallResponseHandler>*>  mCallHash;
        };
      }
    }
  }
}


#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_SERVER__RPC_CALL_RESPONSE_HANDLER_H_

