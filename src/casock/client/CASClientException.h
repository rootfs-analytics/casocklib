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
 * \file casock/client/CASClientException.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_CLIENT__CAS_CLIENT_EXCEPTION_H_
#define __CASOCKLIB__CASOCK_CLIENT__CAS_CLIENT_EXCEPTION_H_

#include "casock/base/CASException.h"

namespace casock {
  namespace client {
    class CASClientException : public casock::base::CASException
    {
      public:
        CASClientException (const std::string& m) throw () : CASException (m) { }
    };
  }
}

#endif // __CASOCKLIB__CASOCK_CLIENT__CAS_CLIENT_EXCEPTION_H_
