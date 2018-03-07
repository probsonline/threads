#include "defs.h"

int main(int argc, char **argv)
{
    int pid, buff_count;

    appPrint("\n\n ******** Starting the system ******** \n");  

    /* Created the matrix server process that will actually compute the 
	   multiplication of the vectors. */
    pid = initMatrixServer();

    /* Check if the matrix server initialized successfully and the 
	   execution context is now in the calling process. */
    if(APP_PROCESS(pid))
    {
		/* Create the matrix seeder. */
		pid = InitSeeder();

		/* Check if the matrix seeder initialized successfully and the 
		   execution context is now in the calling process. */
		if(APP_PROCESS(pid))
		{
			/* Create the client for matrix server. */
			pid = InitClient();
		}        
    }

	if (!APP_PROCESS(pid))
	{
		exit(1);
	}

    return 0;
}

