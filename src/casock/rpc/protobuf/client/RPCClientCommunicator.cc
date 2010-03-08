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
 * \file casock/rpc/protobuf/client/RPCClientCommunicator.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCClientCommunicator.h"

#include "casock/util/Logger.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/base/CASRPCException.h"
#include "casock/rpc/protobuf/base/CASRPCUnfinishedMessageException.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        RPCClientCommunicator::RPCClientCommunicator (const casock::base::FileDescriptor* const pFD) : casock::rpc::protobuf::base::RPCCommunicator (pFD)
        {
        }

        google::protobuf::Message* RPCClientCommunicator::createRequest ()
        {
          return new casock::rpc::protobuf::api::RpcResponse ();
        }
      }
    }
  }
}
