#include "ServerSockAcceptorHandler.h"

#include <stdio.h>

#include "ServerSockReaderHandler.h"
#include "casock/base/Communicator.h"
#include "casock/base/FileDescriptor.h"

/*
void ServerSockAcceptorHandler::createHandler (const FileDescriptor* const pFileDescriptor)
{
  printf ("ServerSockAcceptorHandler::%s () - begin\n", __FUNCTION__);
  new ServerSockReaderHandler (pFileDescriptor);
}
*/

void ServerSockAcceptorHandler::createHandler (const int& fd)
{
  printf ("ServerSockAcceptorHandler::%s () - begin\n", __FUNCTION__);
  new ServerSockReaderHandler (fd);
}
