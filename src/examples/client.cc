#include <unistd.h>

#include <stdio.h>
#include <string>

#include "casock/util/Logger.h"
#include "casock/base/Dispatcher.h"
#include "casock/base/Communicator.h"
#include "casock/base/CASException.h"
#include "casock/base/CASClosedConnectionException.h"
#include "casock/client/ClientSocket.h"
#include "casock/client/CASClientException.h"
#include "ClientSockReaderHandler.h"

using std::string;

int main ()
{
  LOGGER->setDebugLevel (MAX_LEVEL);
  LOGMSG (LOW_LEVEL, "main () - start\n");

  casock::base::Dispatcher::initialize ();

  try
  {
    casock::client::ClientSocket client ("localhost", 2000);
    client.connect ();
    ClientSockReaderHandler handler (&client);
    casock::base::Communicator& communicator = handler.communicator ();

    if (client.connected ())
    {
      //    string s = "Hello World!";
      //    communicator.write (s.c_str (), s.length ());
      //    string s2 = "";
      //    communicator.write (s2.c_str (), s2.length ());

//      string s (8 * BUFSIZ, 'a');
//      communicator.write (s.c_str (), s.length ());

//      string s2 (8 * BUFSIZ, 'a');
//      communicator.write (s2.c_str (), s2.length ());

      //Dispatcher::getInstance ()->wait (10);
      //Dispatcher::getInstance ()->waitForever ();

      size_t sent = 0;

      while (true)
      {
        string s (10 * BUFSIZ, 'a');
        communicator.write (s.c_str (), s.length ());
        sent += s.length ();

        printf ("main () - sent: %Zu\n", sent);

        casock::base::Dispatcher::getInstance ()->wait (10);
      }

      client.close ();
      handler.unregister ();
    }
    else
      printf ("client not connected!\n");

  }
  catch (casock::base::CASClosedConnectionException& e)
  {
    printf ("main () - casock::client::CASClosedConnectionException [%s]\n", e.what ());
  }
  catch (casock::client::CASClientException& e)
  {
    printf ("main () - casock::client::CASClientException [%s]\n", e.what ());
  }
  catch (casock::base::CASException& e)
  {
    printf ("main () - casock::base::CASException [%s]\n", e.what ());
  }

  casock::base::Dispatcher::destroy ();
}
