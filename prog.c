#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) 
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */ 
    int should_run = 1; /* flag to determine when to exit program */
    
    char input[MAX_LINE], history[MAX_LINE];
    
    while (should_run)
    { 
        printf("mysh:~$ "); 
        fflush(stdout);
        
        /** After reading user input, the steps are:  
         * (1) fork a child process using fork()  
         * (2) the child process will invoke execvp()  
         * (3) parent will invoke wait() unless command included & 
         */
         
         // (1)
         
         scanf("%80s", *args);
         
         if (strcmp(*args, "exit") == 0)
         {
         	 should_run = 0;
         }
         
         
         if (strcmp(*args, "!!") != 0)
         {
         	 strcpy(history, *args);
         }
         memset(*args, 0, MAX_LINE);
    }

    return 0;
}