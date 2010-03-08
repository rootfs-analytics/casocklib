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
 * \file casock/rpc/protobuf/client/RPCCallController.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCCallController.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        RPCCallController::RPCCallController ()
        {
          Reset ();
        }

        void RPCCallController::Reset()
        {
          failed = false;
          reason = "";
          canceled = false;
          cancelListeners.clear ();
        }

        bool RPCCallController::Failed() const
        {
          return failed;
        }

        std::string RPCCallController::ErrorText() const
        {
          return reason;
        }

        void RPCCallController::StartCancel()
        {
          canceled = true;

          std::list<google::protobuf::Closure*>::const_iterator it;
          std::list<google::protobuf::Closure*>::const_iterator itEnd = cancelListeners.end ();

          for (it = cancelListeners.begin (); it != itEnd; ++it)
            (*it)->Run ();
        }

        void RPCCallController::SetFailed(const std::string& reason)
        {
          failed = true;
          this->reason = reason;
        }

        bool RPCCallController::IsCanceled() const
        {
          return canceled;
        }

        void RPCCallController::NotifyOnCancel(google::protobuf::Closure* callback)
        {
          cancelListeners.push_back (callback);
        }
      }
    }
  }
}
