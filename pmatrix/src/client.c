#include "defs.h"

void shutdownClient();

/* This function creates a process and returns the pid. */
int InitClient(int *buffers)
{
    int pid;

    /* Created a process. */
    pid = fork();

    switch(pid)
    {
    case APP_FAIL:
        printf("Client initialization failed\n");
        break;

    case CHILD_PID:
        {
			int		file;
			void   *file_mem;
			int pipe_ends[2];
			int read_end, write_end;

			myPrint("Matrix Client: My ID is %d. Please peform the multiplication for my matrix.\n", getpid());

			/* Open the file to read the matrix from it. */
			file = open("matrix", O_RDWR, O_IRUSR | O_IWUSR);

			MY_APP_ASSERT(file);

			/* Map the file to the memory. */
			file_mem = mmap(null, TEMP_FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);

			MY_APP_ASSERT(file_mem);

			/* Close the file. */
			close(file);

			/* Check if server is running. (Through .lock file)*/

			/* Read the memory. */

			/* Open the pipe to the server. */
			pipe(pipe_ends);
			read_end = pipe_ends[0];
			write_end = pipe_ends[1];

			/* Send the matrix to the server. */

			/* Free the memory. */
			munmap(file_mem, TEMP_FILE_LENGTH);

			//Kaleem: Wait until server is running. Nothing now. Make it a lock through file (not sem. to demonstrate the sem).
			//Open a pipe with the server to send the matrix elements in the format rows cols e1, e2, ... , en




            atexit(shutdownClient);
        }
        break;

    default:
        printf("\n");
        break;
    }

    return pid;
}

void ReadMatrixFromFile()
{
	int i;
	int total_elements;
	SeedRows = 1;
	SeedCols = 1;

	total_elements = SeedRows + SeedCols;

}

void shutdownClient()
{
    printf("Client is now shutting down.");
}
