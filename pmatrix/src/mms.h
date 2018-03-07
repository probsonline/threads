#ifndef _MMS_H
#define _MMS_H

#include "app_defs.h"

/* Identifier for the shared memory between the matrix seeder and
   the matrix server. */
#define MS_SHARED_MEM_ID 15

/* Semaphore to protect the shared memory region. */
#define MS_SHMEM_SEM_ID 1

#define MS_MAX_CLIENT_SUPPORTED 2

#endif  /* _MMS_H */

