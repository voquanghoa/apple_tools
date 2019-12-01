#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#ifdef WIN32
#include <winsock2.h>
typedef unsigned int socklen_t;
#else
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>
#endif
#include "socket.h"
#include "usbmuxd.h"

namespace usbmuxd{
  int CreateListen(const char* device_udid1, const int& local_port1, const int& device_port1);
}

