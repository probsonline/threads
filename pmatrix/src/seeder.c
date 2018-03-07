#include "seeder.h"

extern int MS_SeederMemProtector;

void shutdownSeeder();

/* This function creates a process and returns the pid. */
int InitSeeder()
{
	int pid;

	/* Created a process. */
	pid = fork();

	switch(pid)
	{
	case APP_FAIL:
		myPrint("Matrix seeder couldn't be initialized.\n");
		break;

	case CHILD_PID:
		{
			int shm_id;
			key_t key			 = SHARED_MEM_ID;
			key_t shared_mem_key = MS_SH_MEM_SEM_ID;
			struct sembuf shm_sem;

			myPrint("Matrix Seeder: My ID is %d. I'll provide the seed for matrix multiplication.\n", getpid());

			/* Obtain the semaphore. */
			shm_sem.sem_num  = SEM_NUM_IN_SET;
			shm_sem.sem_op   = SEM_LOCK_INC_VAL;
			shm_sem.sem_flag = SEM_LOCK_WAIT_BEHAVIOR;

			status = semop(MS_SeederMemProtector, &shm_sem, 1);
			if (status == APP_FAIL)
			{
				return status;
			}

			myPrint("Semaphore locked successfully\n");

			/* Get the shared memory region. */
			shm_id = shmget(key, 0, 0);

			/* Check if operation succeeded. */
			if(shm_id != APP_FAIL)
			{
				int *shm_ptr;

				/* Attach the memory region to the process. */
				shm_ptr = (int *)shmat(shm_id, 0, 0);

				if(shm_ptr != (int*)APP_FAIL)
				{
					/* Three possibilities for the seed.
					default
					random with rows and cols from client (RPC)
					fixed from client through pipe.
					Make a function called submit seed.
					*/
					/* Check if default seeder will be used. */
					if(1) //Kaleem: todo: check the custom seed???
					{
						initDefaultSeed(shm_ptr);
					}
					else
					{
						//random see with rows and columns from the client (Could be RPC).
						//Kaleem: todo: get the custom seed???
					}

					/* Release the shared memory protection semaphore. */
				}                
				else
				{
					myPrint("Couldn't access the shared memory region from matrix server\n");
				}
			}
			else
			{
				myPrint("Couldn't find the memory region shared by matrix server.\n");
			}

			/* Attach the process exit function. */
			atexit(shutdownSeeder);
		}
		break;

	default:
		/* This will be executed by the parent as well as the child process. */
		myPrint("\n");
		break;
	}

	return pid;
}

void initDefaultSeed(int *mem)
{
	int row, col;

	/* set the number of rows for the default seed matrix. */
	*mem++ = SEEDER_DEF_ROWS;

	/* set the number of columns for the default seed matrix. */
	*mem++ = SEEDER_DEF_COLS;

	/* Generate an identity matrix like seed. */    
	for(row=0; row<SEEDER_DEF_COLS; row++)
	{
		for(col=0; col<SEEDER_DEF_ROWS; col++)
		{
			/* Check if this is diagonal entry. */
			if(row == col)
			{
				*mem++ = SEEDER_DEF_ELEMENT;
			}
			else
			{
				*mem++ = 0;
			}
		}
	}
}

void initCustomSeed(int *mem, char** argv)
{
	int i;
	int total_elements = SeedRows + SeedCols;

	/* set the number of rows for the default seed matrix. */
	*mem++ = SeedRows;

	/* set the number of columns for the default seed matrix. */
	*mem++ = SeedCols;

	if((argc-3) == total_elements)
	{
		for(i=0; i<total_elements; i++)
		{
			*mem++ = atoi(argv[i]);
		}
	}
}

void shutdownSeeder()
{
	myPrint("Shutting down seeder \n");
}
