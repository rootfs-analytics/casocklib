#ifndef _CLIENT_SOCK_READER_HANDLER_H_
#define _CLIENT_SOCK_READER_HANDLER_H_

#include "casock/base/Handler.h"
#include "casock/base/Communicator.h"

namespace casock {
  namespace base {
    class FileDescriptor;
  }
}

class ClientSockReaderHandler : public casock::base::Handler
{
  public:
    ClientSockReaderHandler (const casock::base::FileDescriptor* const pFileDescriptor) : Handler (pFileDescriptor), mCommunicator (mpFileDescriptor) { }

//  private:
//    void destroy () { delete this; }

  public:
    void handle ();
    casock::base::Communicator& communicator () { return mCommunicator; }

  private:
    casock::base::Communicator mCommunicator;
};


#endif // _CLIENT_SOCK_READER_HANDLER_H_
