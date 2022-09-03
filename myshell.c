#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) 
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */ 
    int should_run = 1; /* flag to determine when to exit program */
    
    char history[MAX_LINE], input[MAX_LINE];
    int i;
    
    while (should_run)
    { 
        printf("mysh:~$ "); 
        fflush(stdout);
        
        /** After reading user input, the steps are:  
         * (1) fork a child process using fork()  
         * (2) the child process will invoke execvp()  
         * (3) parent will invoke wait() unless command included & 
         */
         
         fgets(input, MAX_LINE, stdin);
         input[strlen(input) - 1] = '\0';
         
         if (strcmp(input, "!!") == 0)
         {
         	 if (strlen(history) == 0)
         	 {
         	 	 printf("No commands in history!\n");
         	 	 
         	 	 continue;
         	 }
         	 else
         	 {
         	 	 strcpy(input, history);
         	 }
         }
         else
         {
         	 strcpy(history, input);
         }
         
         if (strcmp(input, "exit") == 0)
         {
         	 should_run = 0;
         }
         else
         {
         	 args[0] = strtok(input, " ");
         	 
         	 for (i = 1; i < strlen(input) - 1; i++)
         	 {
         	 	 if (args[i] == NULL)
         	 	 {
         	 	 	 break;
         	 	 }
         	 	 
         	 	 args[i] = strtok(NULL, " ");
         	 }
         	 
         	 int pid = fork();
         	 
         	 if (pid == 0)
         	 {
         	 	 if (execvp(args[0], args) == -1)
         	 	 {
         	 	 	 exit(EXIT_FAILURE);
         	 	 }
         	 	 
         	 	 if (strcmp(args[0], "cd") == 0)
         	 	 {
         	 	 	 chdir(args[1]);
         	 	 }
         	 	 else
         	 	 {
         	 	 	 execvp(args[0],args);
         	 	 	 
         	 	 	 printf("\n");
         	 	 }
         	 }
         	 else if (pid > 0)
         	 {
         	 	 if (strchr(input, '&') == NULL)
         	 	 {
         	 	 	 wait(NULL);
         	 	 }
         	 }
         	 else
         	 {
         	 	 printf("Fork Error!\n");
         	 }
         }
         
         memset(input, 0, MAX_LINE);
    }

    return 0;
}