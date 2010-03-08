#include "ServerSockReaderHandler.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <string>
using std::string;

#include "casock/util/Logger.h"
#include "casock/base/FileDescriptor.h"
#include "casock/base/CASClosedConnectionException.h"

ServerSockReaderHandler::ServerSockReaderHandler (const int& fd) : Handler (new casock::base::FileDescriptor (fd)), mCommunicator (mpFileDescriptor)
{
  LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::ServerSockReaderHandler () - begin\n");

  received = 0;

  string msg1 = "CONNECTED!";
  mCommunicator.write (msg1.c_str (), msg1.length ());
};

void ServerSockReaderHandler::handle ()
{
  LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - treating request...\n", __FUNCTION__);

  /*
  SockReaderHandler::handle ();

  if (m_offset)
  {
    LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - m_buffer [%s]\n", __FUNCTION__, m_buffer);
    bzero (m_buffer, 1024);
    m_offset = 0;
    //::send (m_fd, "OK", 2, 0);
    char* msg1 = "OK";
    mpCommunicator->write (msg1, strlen (msg1));
    //::send (m_fd, "OK2", 3, 0);
    char* msg2 = "OK2";
    mpCommunicator->write (msg2, strlen (msg2));
  }
  else
  {
    LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
    unregister ();
    destroy ();
  }
  */

  try
  {
    stringstream request;
    ssize_t s = mCommunicator.read (request);

    if (s)
    {
      stringstream response;
      response << "received " << request.str ().length () << " bytes";
      received += request.str ().length ();
      LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - response[%s], received: %Zu bytes\n", __FUNCTION__, response.str ().c_str (), received);
      mCommunicator.write (response);
    }
  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    LOGMSG (LOW_LEVEL, "ServerSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
    unregister ();
    destroy ();
  }
}
