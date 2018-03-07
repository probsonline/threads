#include "defs.h"

int main(int argc, char **argv)
{
    int pid, buff_count;

    printf("\n\nStarting the system-----\n");
    printf("\nCreating the producer. ");
    printf("wait........................................\n");

    /* Created producer process that puts data in the buffer. */
    pid = createProducer(&buff_count);

    /* Check if process couldn't be created. */
    if(pid == APP_FAIL)
    {
        exit(1); 
    }
    else
    {
        if(pid != CHILD_PID)
        {
            printf("\nNow Creating the consumer. ");
            printf("wait........................................\n");

            /* Created consumer process that gets data from the buffer. */
            pid = createConsumer();

            /* Check if process couldn't be created. */
            if(pid == APP_FAIL)
            {
                exit(1); 
            }
            else
            {
                if(pid !=  CHILD_PID)
                {
                    printf("\nBack In the main application.\n\n");
                }
            }
        }
    }
    return 0;
}
