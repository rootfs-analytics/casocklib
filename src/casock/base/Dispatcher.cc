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
 * \file casock/base/Dispatcher.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/base/Dispatcher.h"

#include "casock/util/Logger.h"
#include "casock/base/Handler.h"
#include "casock/base/CASException.h"

namespace casock {
  namespace base {
//    struct sigaction Dispatcher::m_sigaction;
//    struct sigaction Dispatcher::m_sigaction2;
    Dispatcher* Dispatcher::mpDispatcher = NULL;

   sigset_t Dispatcher::m_mask;
   sigset_t Dispatcher::m_oldmask;

    Dispatcher::~Dispatcher ()
    {
      unordered_map<int, Handler*>::const_iterator it;
      unordered_map<int, Handler*>::const_iterator itEnd = mFDHandlerHash.end ();

      for (it = mFDHandlerHash.begin (); it != itEnd; ++it)
      {
        close (it->first);
        delete it->second;
      }

      mFDHandlerHash.clear ();
    }

    Dispatcher* Dispatcher::getInstance ()
    {
      if (! mpDispatcher)
        mpDispatcher = new Dispatcher ();

      return mpDispatcher;
    }

    void Dispatcher::initialize ()
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s ()\n", __FUNCTION__);

      /*
      m_sigaction.sa_sigaction = Dispatcher::func_sigaction;
      sigemptyset (&(m_sigaction.sa_mask));
      m_sigaction.sa_flags = SA_SIGINFO;
      sigaction (SIGIO, &m_sigaction, NULL);
//      sigaction (SIGURG, &m_sigaction, NULL);

      m_sigaction2.sa_handler = Dispatcher::func_handler;
      sigemptyset (&(m_sigaction2.sa_mask)); // TODO: ? antes não tinha o 2
      m_sigaction2.sa_flags = 0; // TODO: ? antes não tinha o 2
      sigaction (SIGALRM, &m_sigaction2, NULL);
      */

      struct sigaction act_SIGIO;
      act_SIGIO.sa_sigaction  = Dispatcher::func_sigaction;
      act_SIGIO.sa_flags      = SA_SIGINFO;
      sigemptyset (&(act_SIGIO.sa_mask));
      sigaction (SIGIO, &act_SIGIO, NULL);
//      sigaction (SIGURG, &act_SIGIO, NULL);

      struct sigaction act_SIGALARM;
      act_SIGALARM.sa_handler = Dispatcher::func_handler;
      act_SIGALARM.sa_flags   = 0;
      sigemptyset (&(act_SIGALARM.sa_mask));
      sigaction (SIGALRM, &act_SIGALARM, NULL);

      sigemptyset (&m_mask);
      sigaddset (&m_mask, SIGIO);
      sigprocmask (SIG_BLOCK, &m_mask, &m_oldmask);
    }

    void Dispatcher::destroy ()
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s ()\n", __FUNCTION__);

      if (mpDispatcher)
        delete mpDispatcher;

      mpDispatcher = NULL;
    }

    void Dispatcher::func_sigaction (int signum, siginfo_t* p_siginfo, void* p_data)
    {
      LOGMSG (LOW_LEVEL, "Dispatcher::%s () - signum [%d], fd [%d]\n", __FUNCTION__, signum, p_siginfo->si_fd);
      Dispatcher::getInstance ()->handle (signum, p_siginfo, p_data);
    }

    void Dispatcher::func_handler (int signum)
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - signum [%d]\n", __FUNCTION__, signum);
      Dispatcher::getInstance ()->deactivate ();
    }

    void Dispatcher::handle (int signum, siginfo_t* p_siginfo, void* p_data)
    {
      int& fd = p_siginfo->si_fd;

      if (mFDHandlerHash.find (fd) != mFDHandlerHash.end ())
      {
        if (mFDHandlerHash [fd])
          mFDHandlerHash [fd]->handle ();
        else
          LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - pHandler of fd [%d] not found!\n", __FUNCTION__, fd);
      }
      else
        LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d] not found!\n", __FUNCTION__, fd);
    }

    void Dispatcher::registerHandler (const int& fd, Handler* pHandler)
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d]\n", __FUNCTION__, fd);

      if (mFDHandlerHash.find (fd) != mFDHandlerHash.end ())
        throw (casock::base::CASException ("file descriptor already in use"));

      mFDHandlerHash [fd] = pHandler;
    }

    void Dispatcher::unregisterHandler (const int& fd)
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - fd [%d]\n", __FUNCTION__, fd);

      if (mFDHandlerHash.find (fd) == mFDHandlerHash.end ())
        throw (casock::base::CASException ("file descriptor not found"));

      mFDHandlerHash.erase (fd);
    }

    void Dispatcher::wait (const time_t& timeout)
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - begin\n", __FUNCTION__);

      m_active = true;

      /*
      sigset_t mask, oldmask;
      sigemptyset (&mask);
      sigaddset (&mask, SIGIO);
      sigprocmask (SIG_BLOCK, &mask, &oldmask);
      */

      while (m_active)
      {
        LOGMSG (LOW_LEVEL, "Dispatcher::%s () - pause...\n", __FUNCTION__);
        alarm (timeout);

        /*
        sigset_t sigio_set;
        sigemptyset(&sigio_set);
        sigaddset(&sigio_set, SIGIO);
        sigprocmask (SIG_UNBLOCK, &sigio_set, NULL);

        pause ();
        */
        sigsuspend (&m_oldmask);
        LOGMSG (LOW_LEVEL, "Dispatcher::%s () - returning from pause!\n", __FUNCTION__);
      }

//      sigprocmask (SIG_UNBLOCK, &mask, NULL);

      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - end\n", __FUNCTION__);
    }

    void Dispatcher::waitForever ()
    {
      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - begin\n", __FUNCTION__);

      m_active = true;

      /*
      sigset_t mask, oldmask;
      sigemptyset (&mask);
      sigaddset (&mask, SIGIO);
      sigprocmask (SIG_BLOCK, &mask, &oldmask);
      */

      while (m_active)
      {
        LOGMSG (LOW_LEVEL, "Dispatcher::%s () - pause...\n", __FUNCTION__);

        /*
        sigset_t sigio_set;
        sigemptyset(&sigio_set);
        sigaddset(&sigio_set, SIGIO);
        sigprocmask (SIG_UNBLOCK, &sigio_set, NULL);
        //raise (SIGIO);

        pause ();
        */
        sigsuspend (&m_oldmask);
        LOGMSG (LOW_LEVEL, "Dispatcher::%s () - returning from pause!\n", __FUNCTION__);
      }

//      sigprocmask (SIG_UNBLOCK, &mask, NULL);

      LOGMSG (HIGH_LEVEL, "Dispatcher::%s () - end\n", __FUNCTION__);
    }
  }
}
