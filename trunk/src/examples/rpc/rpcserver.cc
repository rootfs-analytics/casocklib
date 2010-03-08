#include "casock/util/Logger.h"
#include "casock/base/Dispatcher.h"
#include "casock/server/CASServerException.h"
#include "casock/rpc/protobuf/server/RPCServerProxy.h"

#include "api/rpc_hello.pb.h"

class HelloServiceImpl : public  HelloService
{
  public:
    void HelloCall(::google::protobuf::RpcController* controller,
        const ::HelloRequest* request,
        ::HelloResponse* response,
        ::google::protobuf::Closure* done)
    {
      LOGMSG (LOW_LEVEL, "HelloServiceImpl::%s () - request->message () [%s]\n", __FUNCTION__, request->message ().c_str ());
      response->set_id (request->id ());
      response->set_message ("I'm the server. You sent me: " + request->message ());
      done->Run ();
    }
};

int main ()
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  casock::base::Dispatcher::initialize ();

  try
  {
    casock::rpc::protobuf::server::RPCServerProxy proxy (2000, new HelloServiceImpl ());
    proxy.start ();

    casock::base::Dispatcher::getInstance ()->waitForever ();
  }
  catch (casock::server::CASServerException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASServerException [%s]\n", __FUNCTION__, e.what ());
  }
  catch (casock::base::CASException& e)
  {
    LOGMSG (NO_DEBUG, "%s () - CASException [%s]\n", __FUNCTION__, e.what ());
  }

  casock::base::Dispatcher::destroy ();
}
