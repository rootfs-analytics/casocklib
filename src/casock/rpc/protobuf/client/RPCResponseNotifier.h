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
 * \file casock/rpc/protobuf/client/RPCResponseNotifier.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_RESPONSE_NOTIFIER_H_
#define __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_RESPONSE_NOTIFIER_H_

#include "casock/util/Lockable.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCResponseNotifier : private Lockable
        {
          private:
            static void callback (RPCResponeNotifier* pNotifier) { pNotifier->cond_broadcast (); }

          public:
            google::protobuf::Closure* closure () { return google::protobuf::NewCallback (RPCResponseNotifier::callback, this); }

          public:
            void wait (const uint32& timeout = 0) { cond_wait (timeout); }
        };
      }
    }
  }
}

#endif // __CASOCKLIB__CASOCK_RPC_PROTOBUF_CLIENT__RPC_RESPONSE_NOTIFIER_H_
