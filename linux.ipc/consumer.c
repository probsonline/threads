#include "defs.h"

void shutdownConsumer();

/* This function creates a process and returns the pid. */
int createConsumer()
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

            printf("\nIn the consumer \n");
            printf("I am the consumer. My ID is %d. Give me data.\n", getpid());

            /* Create a share memory region. */
            shm_id = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | 0666);

            /* Check if operation successed. */
            if(shm_id != APP_FAIL)
            {
                char *shm_ptr;
                char *buffer = malloc(27);

                /* Attach the memory region to the process. */
                shm_ptr = (char *)shmat(shm_id, 0, 0);

                if(shm_ptr != (char*)APP_FAIL)
                {
                    /* Display the data. */
                    printf("Consumer: I got this data: ");

                    /* Get the data from the shared region. */
                    while(*shm_ptr  != NULL_CHAR)
                    {
                        *buffer = *shm_ptr++;
                         printf(buffer);
                         buffer++;
                    }

                    printf("\n");
                }                
                else
                {
                    printf("Couldn't get the shared memory region from producer\n");
                }
            }
            else
            {
                printf("Couldn't get access to the memory region shared by the producer.\n");
            }

            /* Attach the process exit function. */
            atexit(shutdownConsumer);
        }
        break;

    default:
        printf("\n");
        break;
    }


    return pid;
}

void shutdownConsumer()
{
    printf("Shutting down consumer \n");
}

