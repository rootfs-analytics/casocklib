SRCS = RPCServerProxy.cc RPCCall.cc RPCCallHandler.cc RPCAcceptorHandler.cc \
       RPCReaderHandler.cc RPCService.cc RPCServerCommunicator.cc

LIBS = $(top_srcdir)/src/casock/server/libcasserver.la \
			 $(top_srcdir)/src/casock/rpc/protobuf/base/libcasrpcpbbase.la \
       $(top_srcdir)/src/casock/rpc/protobuf/api/libcasrpcpbapi.la

noinst_LTLIBRARIES = libcasrpcpbserver.la

libcasrpcpbserver_la_SOURCES  = $(SRCS)
libcasrpcpbserver_la_LIBADD   = $(LIBS)
