#include "ClientSockReaderHandler.h"

#include <stdio.h>
#include <strings.h>

#include <string>
using std::string;

#include "casock/util/Logger.h"
#include "casock/base/Communicator.h"
#include "casock/base/CASClosedConnectionException.h"

void ClientSockReaderHandler::handle ()
{
  /*
  SockReaderHandler::handle ();

  if (m_offset)
  {
    LOGMSG (LOW_LEVEL, "ClientSockReaderHanlder::%s () - m_buffer [%s]\n", __FUNCTION__, m_buffer);
    bzero (m_buffer, 1024);
    m_offset = 0;
  }
  else
  {
    LOGMSG (LOW_LEVEL, "ClientSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
    unregister ();
    destroy ();
  }
  */

  try
  {
    stringstream sstream;
    ssize_t s = mCommunicator.read (sstream);

    if (s)
      LOGMSG (LOW_LEVEL, "ClientSockReaderHandler::%s () - sstream [%s]\n", __FUNCTION__, sstream.str ().c_str ());
  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    LOGMSG (LOW_LEVEL, "ClientSockReaderHandler::%s () - connection closed\n", __FUNCTION__);
    unregister ();
//    destroy ();
    throw (e);
  }
}
