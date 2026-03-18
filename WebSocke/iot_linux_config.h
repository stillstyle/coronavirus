
/*
 * Copyright (C) K
 */


#ifndef _IOT_LINUX_CONFIG_H_
#define _IOT_LINUX_CONFIG_H_


#ifndef _GNU_SOURCE
#define _GNU_SOURCE             /* pread(), pwrite(), gethostname() */
#endif

#define _FILE_OFFSET_BITS  64

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        /* TCP_NODELAY, TCP_CORK */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>

#include <time.h>               /* tzset() */
#include <malloc.h>             /* memalign() */
#include <sys/ioctl.h>

// #include <sys/sysctl.h>
#include <sys/sysinfo.h>

#include <crypt.h>
#include <sys/prctl.h>
#include <poll.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <semaphore.h>




#endif /* _IOT_LINUX_CONFIG_H_INCLUDED_ */
