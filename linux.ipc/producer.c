#include "defs.h"

void shutdownProducer();

/* This function creates a process and returns the pid. */
int createProducer(int *buffers)
{
    int pid;

    /* Created a process. */
    pid = fork();

    switch(pid)
    {
    case APP_FAIL:
        printf("Process creation failed\n");
        break;

    case CHILD_PID:
        {
            int shm_id;
            key_t key = SHARED_MEM_ID;

            /* Return the number of buffers. */
            *buffers = P_BUFF_COUNT;

            printf("\nIn the producer \n");
            printf("I am the producer. My ID is %d. I have %d buffer. .\n", getpid(), *buffers);

            /* Create a share memory region. */
            shm_id = shmget(key, SHARED_MEM_SIZE, 0);

            /* Check if operation successed. */
            if(shm_id != APP_FAIL)
            {
                char *shm_ptr;
                char alphabet;
                char *tmp;

                /* Attach the memory region to the process. */
                shm_ptr = (char *)shmat(shm_id, 0, SHM_RND);
                tmp = shm_ptr;
                if(shm_ptr != (char *)APP_FAIL)
                {
                    printf("Shared memory region created. Now writing data: ");

                    /* Get the data from the shared region. */
                    for(alphabet = 'A'; alphabet <= 'Z'; alphabet++)
                    {
                        *shm_ptr =  alphabet;
                        shm_ptr++;
                    }

                    /* Null terminate the string. */
                    *shm_ptr = NULL_CHAR;
                    printf(tmp);
                    printf("\n");
                }
                else
                {
                    printf("Shared memory region creation failed.\n");
                }
            }
            else
            {
                printf("Share memory region for producer couldn't be created.\n");
            }

            atexit(shutdownProducer);
        }
        break;

    default:
        printf("\n");
        break;
    }

    return pid;
}


void shutdownProducer()
{
    printf("Prdoducer is now shutting down.");
}
