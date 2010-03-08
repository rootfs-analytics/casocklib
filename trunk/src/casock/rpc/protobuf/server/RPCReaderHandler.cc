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
 * \file casock/rpc/protobuf/server/RPCReaderHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCReaderHandler.h"

#include <google/protobuf/message.h>

#include "casock/util/Logger.h"
#include "casock/util/LockableQueue.h"
#include "casock/util/SafeLock.h"
#include "casock/util/SafeTryLock.h"
#include "casock/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/base/CASRPCUnfinishedMessageException.h"
#include "casock/rpc/protobuf/server/RPCServerCommunicator.h"
#include "casock/rpc/protobuf/server/RPCCall.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        RPCReaderHandler::RPCReaderHandler (const int& fd, RPCCallQueue& rCallQueue) : Handler (new casock::base::FileDescriptor (fd)), mCommunicator (mpFileDescriptor), mrCallQueue (rCallQueue)
        {
          len = 0;
        };

        void RPCReaderHandler::invalidateCalls ()
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

        void RPCReaderHandler::handle ()
        {
          LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - treating request...\n", __FUNCTION__);

          try
          {
            casock::rpc::protobuf::api::RpcRequest* request = static_cast<casock::rpc::protobuf::api::RpcRequest *>(mCommunicator.read ());
            LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - request received: %d bytes - id [%u], operation [%s]\n", __FUNCTION__, request->ByteSize (), request->id (), request->operation ().c_str ());

            mrCallQueue.push (new RPCCall (this, request));
          }
          catch (casock::base::CASClosedConnectionException& e)
          {
            LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - catch CASClosedCConnectionException\n", __FUNCTION__);

            invalidateCalls ();
            unregister ();
            destroy ();
          }
          catch (casock::rpc::protobuf::base::CASRPCUnfinishedMessageException& e)
          {
            LOGMSG (HIGH_LEVEL, "RPCReaderHandler::%s () - catch CASRPCUnfinishedMessageException\n", __FUNCTION__);
          }
        }

        void RPCReaderHandler::registerCall (const uint32& id, const RPCCall* const pCall)
        {
          casock::util::SafeLock lock (mCallHash);
          mCallHash [id] = pCall;
        }

        void RPCReaderHandler::unregisterCall (const uint32& id)
        {
          casock::util::SafeLock lock (mCallHash);
          mCallHash.erase (id);
        }

        const bool RPCReaderHandler::tryUnregisterCall (const uint32& id)
        {
          bool ret = false;

          if ((ret = mCallHash.tryLock ()) == true)
          {
            mCallHash.erase (id);
            mCallHash.unlock ();
          }

          return ret;
        }
      }
    }
  }
}
