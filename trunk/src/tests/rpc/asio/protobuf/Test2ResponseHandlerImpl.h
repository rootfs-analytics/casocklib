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
 * \file tests/rpc/asio/protobuf/Test2ResponseHandlerImpl.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_RESPONSE_HANDLER_IMPL_H_
#define __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_RESPONSE_HANDLER_IMPL_H_

#include "casock/rpc/protobuf/client/RPCResponseHandler.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        class RPCCallController;
      }
    }
  }
}

namespace tests {
  namespace rpc {
    namespace protobuf {
      namespace api {
        class TestResponse;
      }
    }

    namespace asio {
      namespace protobuf {
        class Test2Manager;

        class Test2ResponseHandlerImpl : public casock::rpc::protobuf::client::RPCResponseHandler
        {
          public:
            Test2ResponseHandlerImpl (
                casock::rpc::protobuf::client::RPCCallController* pController,
                tests::rpc::protobuf::api::TestResponse* pResponse,
                Test2Manager* pManager);

          public:
            void callback ();

          private:
            casock::rpc::protobuf::client::RPCCallController* mpController;
            tests::rpc::protobuf::api::TestResponse* mpResponse;
            Test2Manager* mpManager;
        };
      }
    }
  }
}

#endif // __CASOCKLIB__TESTS_RPC_ASIO_PROTOBUF__TEST2_RESPONSE_HANDLER_IMPL_H_