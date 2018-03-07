#ifndef _DEFS_H
#define _DEFS_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/mmap.h>

#include <fcntl.h>

/* ******** System Configuration section. ******** */
/* If a conflict for the signature of some service occurs 
   then use the definition from POSIX. */
#define _GNU_SOURCE
#define APP_DEBUG_PRINT	1

/* Linux system globals extern. */
extern int errno;

/* ******** Constants ******** */
#define	APP_FAIL	-1
#define CHILD_PID    0
#define NULL_CHAR    '\0'
#define APP_PROCESS(pid)	((pid == APP_FAIL) && (pid != CHILD_PID))
#if		(APP_DEBUG_PRINT)
#define appPrint(str)	printf(str)
#else
#define appPrint(str)	(void)str;
#endif	/* APP_DEBUG_PRINT */

#define MY_APP_ASSERT(status)				if (status == APP_FAIL)return status

/* Semaphore related. */
#define MS_SEM_COUNT			 2
#define SHM_SEM_NUM				 0
#define MS_SERVER_CLIENT_CONNECTED 0
#define SEM_LOCK_INC_VAL		-1
#define SEM_UNLOCK_INC_VAL		 1
#define SEM_LOCK_WAIT_BEHAVIOR	 0
#define SHARED_MEM_SIZE			 100

#define TEMP_FILE_LENGTH		0x100

/* ******** Function prototypes ******** */
extern int initMatrixServer();
extern int InitSeeder();
extern int InitClient();


#endif  /* _DEFS_H */
