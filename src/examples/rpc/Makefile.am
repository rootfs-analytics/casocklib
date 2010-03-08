SUBDIRS = api

SRCS_RPCCLIENT = rpcclient.cc
SRCS_RPCSERVER = rpcserver.cc

LIB_UTIL      = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_RPCCLIENT = $(top_srcdir)/src/casock/rpc/protobuf/client/libcasrpcpbclient.la
LIB_RPCSERVER = $(top_srcdir)/src/casock/rpc/protobuf/server/libcasrpcpbserver.la
LIB_PROTOBUF	= @LIB_PROTOBUF_PATH@/libprotobuf.a
LIB_RPCHELLO  = api/libcasrpcpbexapi.la

bin_PROGRAMS = rpcclient rpcserver

rpcclient_SOURCES = $(SRCS_RPCCLIENT)
rpcclient_LDADD   = $(LIB_RPCCLIENT) $(LIB_UTIL) $(LIB_RPCHELLO) $(LIB_PROTOBUF)
rpcclient_LDFLAGS = -static

rpcserver_SOURCES = $(SRCS_RPCSERVER)
rpcserver_LDADD   = $(LIB_RPCSERVER) $(LIB_UTIL) $(LIB_RPCHELLO) $(LIB_PROTOBUF)
rpcserver_LDFLAGS = -static
