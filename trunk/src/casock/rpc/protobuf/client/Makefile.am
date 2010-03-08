SRCS = RPCClientProxy.cc RPCChannel.cc RPCCallController.cc \
			 RPCReaderHandler.cc RPCClientCommunicator.cc RPCCallHandler.cc

LIBS = $(top_srcdir)/src/casock/client/libcasclient.la \
			 $(top_srcdir)/src/casock/rpc/protobuf/base/libcasrpcpbbase.la \
       $(top_srcdir)/src/casock/rpc/protobuf/api/libcasrpcpbapi.la

noinst_LTLIBRARIES = libcasrpcpbclient.la

libcasrpcpbclient_la_SOURCES  = $(SRCS)
libcasrpcpbclient_la_LIBADD   = $(LIBS)
