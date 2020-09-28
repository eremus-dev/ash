#include "ashell.h"


void exec_command(command * com)
{
    int status;
    int check = fork();
    if(check < 0)
    {
        perror("fork");
    }
    else if(check == 0)
    {
        if(execvp(com->argv[0], com->argv) == -1)
        {
            perror(com->argv[0]);
            exit(-1);
        }
    } 
    else if( (check > 0) && (com->background == 0) )
    {
        wait(&status);
    } 
    
    return;
}

void print_prompt(char * prompt)
{
    printf("\n%s ", prompt);
}

void exit_shell(int stat)
{
    printf("exit\n");
}

