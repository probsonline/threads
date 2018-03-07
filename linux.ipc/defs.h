#ifndef _DEFS_H
#define _DEFS_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//#include <sys/mmap.h>	/* nmap related memory management. */

/* If a conflict for the signature of some service occurs 
   then use the definition from POSIX. */
#define _GNU_SOURCE

extern int errno;


#define	APP_FAIL	-1
#define CHILD_PID    0

#define NULL_CHAR    '\0'

#define SHARED_MEM_ID   15
#define SHARED_MEM_SIZE 32

#define P_BUFF_COUNT 	1
#define P_BUFF_SIZE		(SHARED_MEM_SIZE/P_BUFF_COUNT)


int createConsumer();
int createProducer(int *buffers);


#endif  /* _DEFS_H */

