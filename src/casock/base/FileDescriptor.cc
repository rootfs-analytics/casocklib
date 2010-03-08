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
 * \file casock/base/FileDescriptor.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/base/FileDescriptor.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "casock/base/CASException.h"
#include "casock/util/SafeLock.h"

namespace casock {
  namespace base {
    FileDescriptor::FileDescriptor (const int& fd) : m_fd (fd)
    {
      //  if (m_fd == -1)
      //    throw (casock::base::CASException (strerror (errno)));
    }

    void FileDescriptor::write (const char* buff, const size_t& len) const
    {
      casock::util::SafeLock lock (*this);
      ::write (m_fd, buff, len);
    }

    const ssize_t FileDescriptor::read (char* buff, const size_t& len) const
    {
      casock::util::SafeLock lock (*this);
      return ::read (m_fd, buff, len);
    }

    void FileDescriptor::close () const
    {
      casock::util::SafeLock lock (*this);
      ::close (m_fd);
    }
  }
}
