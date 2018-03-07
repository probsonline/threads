#include "mms.h"

int MS_SeederMemProtector;

void shutdownMatrixServer();

/* This function creates a process and returns the pid. */
int initMatrixServer()
{
    int pid;

    /* Created a process. */
    pid = fork();

    switch(pid)
    {
    case APP_FAIL:
        myPrint("Matrix server couldn't be initialized. \n");
        break;

    case CHILD_PID:
        {
			int status;

			int   shm_id;
			key_t key			 = SHARED_MEM_ID;

			key_t  shm_sem_key = MS_SH_MEM_SEM_ID;
			struct sembuf shm_sem;

			myPrint("Matrix Server: My ID is %d. I'll perform matrix multiplication for you with the seed .\n", getpid());

			/* Create the semaphore group for matrix server. */
			status = semget(shm_sem_key, MS_SEM_COUNT, 0666|IPC_CREAT|IPC_EXCL);
			MY_APP_ASSERT(status);
			myPrint("Matrix Server: Semaphore created successfully.\n");
			MS_SeederMemProtector = status;

			/* Initialize the shared memory protection semaphore. */
			status = semctl(MS_SeederMemProtector, 1, SETVAL);
			MY_APP_ASSERT(status);
			myPrint("Matrix Server: Semaphore initialized successfully\n");

			/* Lock the shared memory protection semaphore. */
			shm_sem.sem_num  = SHM_SEM_NUM;
			shm_sem.sem_op   = SEM_LOCK_INC_VAL;
			shm_sem.sem_flag = SEM_LOCK_WAIT_BEHAVIOR;
			status = semop(MS_SeederMemProtector, &shm_sem, 1);
			MY_APP_ASSERT(status);
			myPrint("Matrix Server: Semaphore locked successfully\n");

            /* Create a shared memory region. */
            status = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | 0666);
			MY_APP_ASSERT(status);
			myPrint("Matrix Server: Shared memory region created successfully\n");

			/* Unlock the shared memory protection semaphore. */
			shm_sem.sem_op   = SEM_UNLOCK_INC_VAL;
			status = semop(MS_SeederMemProtector, &shm_sem, 1);
			MY_APP_ASSERT(status);
			myPrint("Matrix Server: Semaphore unlocked successfully\n");


			//Create the pipe for the clients. (as per max supported clients).
			//wait until one is filled.
			//When one is filled create processes as per the number of clinets where each process will have multiple threads.
			/* Run forever to provide multiplication facilities. */

			while (1)
			{

			}

            /* Attach the process exit function. */
            atexit(shutdownMatrixServer);
        }
        break;

    default:
        myPrint("\n");
        break;
    }


    return pid;
}

void shutdownMatrixServer()
{
	int status;
    myPrint("Shutting down Matrix Server \n");

	/* Detach shared memory. */
	status = shmdt();

	/* Free the shared memory. */

	status = smectl(MS_SeederMemProtector, 0, IPC_RMID);
	MY_APP_ASSERT(status);
}

