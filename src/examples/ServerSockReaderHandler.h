#ifndef _SERVER_SOCK_READER_HANDLER_H_
#define _SERVER_SOCK_READER_HANDLER_H_

#include <stdlib.h>

#include "casock/base/Handler.h"
#include "casock/base/Communicator.h"

class ServerSockReaderHandler : public casock::base::Handler
{
  public:
    ServerSockReaderHandler (const int& fd);

  private:
    void destroy () { delete this; }

  public:
    void handle ();

  private:
    casock::base::Communicator mCommunicator;
    size_t received;
};


#endif // _SERVER_SOCK_READER_HANDLER_H_
