/*
 * pipe_command.c  :  deal with pipes
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"

#define STD_OUTPUT 1
#define STD_INPUT  0

void pipe_and_exec(char **myArgv) {
  	int pipe_argv_index = pipe_present(myArgv);
  	int pipefds[2];
	char **left_argv;
	char **right_argv;

  	switch (pipe_argv_index) {

    	case -1:	/* Pipe at beginning or at end of argv;  See pipe_present(). */
      		fputs ("Missing command next to pipe in commandline.\n", stderr);
      		errno = EINVAL;	/* Note this is NOT shell exit. */
      		break;

    	case 0:	/* No pipe found in argv array or at end of argv array.
			See pipe_present().  Exec with whole given argv array. */
      		break;

    	default:	/* Pipe in the middle of argv array.  See pipe_present(). */
                left_argv=(char **)malloc(100000);
                right_argv=(char **)malloc(100000);
                for(int w=0;w<pipe_argv_index;w++){
                    left_argv[w]=myArgv[w];
                }

                int u;
                u=pipe_argv_index+1;
                while(myArgv[u]!=0){
                    right_argv[u-pipe_argv_index-1]=myArgv[u];
                    u++;
                }
      		/* Split arg vector into two where the pipe symbol was found.
       		 * Terminate first half of vector.
			 *
       		 * Fill in code. */

      		/* Create a pipe to bridge the left and right halves of the vector.
			 *
			 * Fill in code. */

			 int fd[2];
             pid_t pid;
             pipe(fd);
             pid=fork();
      		/* Create a new process for the right side of the pipe.
       		 * (The left side is the running "parent".)
       		 *
			 * Fill in code to replace the underline. */
      		switch(pid) {

        		case -1 :
	  				break;

        		/* Talking parent.  Remember this is a child forked from shell. */
        		default :

	  				/* - Redirect output of "parent" through the pipe.
	  				 * - Don't need read side of pipe open.  Write side dup'ed to stdout.
	 	 			 * - Exec the left command.
					 *
					 * Fill in code. */
					 close(1);
                     dup2(fd[1],1);
                     close(fd[0]);
                     execvp(left_argv[0],left_argv);
	  				break;

        		/* Listening child. */
        		case 0 :

	  				/* - Redirect input of "child" through pipe.
					  * - Don't need write side of pipe. Read side dup'ed to stdin.
				  	 * - Exec command on right side of pipe and recursively deal with other pipes
					 *
					 * Fill in code. */
					 close(0);
                     dup2(fd[0],0);
                     close(fd[1]);
                     execvp(right_argv[0],right_argv);

          			//pipe_and_exec(&myArgv[pipe_argv_index+1]);//?????
			}
	}
	perror("Couldn't fork or exec child process");
  	exit(errno);
}
