#ifndef _SERVER_SOCK_ACCEPTOR_HANDLER_H_
#define _SERVER_SOCK_ACCEPTOR_HANDLER_H_

#include "casock/server/SockAcceptorHandler.h"

namespace casock {
  namespace base {
    class FileDescriptor;
  }
}

class ServerSockAcceptorHandler : public casock::server::SockAcceptorHandler
{
  public:
    ServerSockAcceptorHandler (const casock::base::FileDescriptor* const pFileDescriptor) : casock::server::SockAcceptorHandler (pFileDescriptor) { }

  private:
//    void createHandler (const FileDescriptor* const pFileDescriptor);
    void createHandler (const int& fd);
};

#endif // _SERVER_SOCK_ACCEPTOR_HANDLER_H_
