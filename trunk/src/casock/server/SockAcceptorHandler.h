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
 * \file casock/server/SockAcceptorHandler.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB_CASOCK_SERVER_SOCK_ACCEPTOR_HANDLER_H_
#define __CASOCKLIB_CASOCK_SERVER_SOCK_ACCEPTOR_HANDLER_H_

#include "casock/base/Handler.h"

namespace casock {
  namespace base {
    class FileDescriptor;
  }

  namespace server {
    using casock::base::FileDescriptor;

    class SockAcceptorHandler : public casock::base::Handler
    {
      public:
        SockAcceptorHandler (const FileDescriptor* const pFileDescriptor) : casock::base::Handler (pFileDescriptor) { };

      private:
        //    virtual void createHandler (const FileDescriptor* const pFileDescriptor) = 0;
        virtual void createHandler (const int& fd) = 0;

      public:
        void handle ();
    };
  }
}


#endif // __CASOCKLIB_CASOCK_SERVER_SOCK_ACCEPTOR_HANDLER_H_
