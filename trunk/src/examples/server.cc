#include "casock/util/Logger.h"
#include "casock/base/Dispatcher.h"
#include "casock/base/CASException.h"
#include "casock/server/ServerSocket.h"
#include "casock/server/CASServerException.h"
#include "ServerSockAcceptorHandler.h"

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  casock::base::Dispatcher::initialize ();

  try
  {
    casock::server::ServerSocket server (2000);

    server.listen ();

    ServerSockAcceptorHandler handler (&server); //, &communicator);
    //Dispatcher::getInstance ()->wait (10);
    casock::base::Dispatcher::getInstance ()->waitForever ();

    server.close ();

    handler.unregister ();
  }
  catch (casock::server::CASServerException& e)
  {
    LOGMSG (NO_DEBUG, "main () - CASServerException [%s]\n", e.what ());
  }
  catch (casock::base::CASException& e)
  {
    LOGMSG (NO_DEBUG, "main () - CASException [%s]\n", e.what ());
  }

  casock::base::Dispatcher::destroy ();
}
