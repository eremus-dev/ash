#include "ashell.h"


void exec_command(command * com, int * in, int *out, int * off)
{
    int status;

    int check = fork();

    if(check < 0)
    {
        perror("fork");
        exit(-1);
    }
    else if(check == 0)
    {
        // redirect stdin if in != 0
        if(*in != 0)
        {
            if(dup2(*in, 0) == -1)
            {
                perror("stdin dup2");
                exit(-1);
            }
        }

        // redirect stdout if out != 0
        if(*out != 0){
            if(dup2(*out, 1) == -1){
                perror("stdout dup2");
                exit(-1);
            } 
        }
        
        // shut unused pipe end.
        if(*off != 0)
        {
            close(*off);
            *off = 0;
        }

        if(execvp(com->argv[0], com->argv) == -1)
        {
            perror(com->argv[0]);
            exit(-1);
        }
        
        // should be unreachable.
        printf("exec failed this should be unreachable\n");
        exit(-1);
    } 
    else if( (check > 0) && (com->background == 0) )
    {
        wait(&status);
    } 

    if(*out != 0)
    {
        close(*out);
        *out = 0;
    }

    if(*in != 0)
    {
        close(*in);
        *in = 0;
    }
    
    return;
}

int handle_redirection(command * com, int * in, int * out, int * off, int * pipefd)
{
    if(com->redirect_in != NULL)
    {
        // stops including spaces in file names.

        int count = 0;
        while(*(com->redirect_in+count) == ' ')
        {
            count++;
        }

        //open file descript and save to in
        if((*in = open(com->redirect_in+count, O_RDWR)) == -1)
        {
            perror("open");
            *in = 0;
            return -1;
        }
    } else if(fcntl(pipefd[0], F_GETFD) != -1) {
        *in = pipefd[0];
        *off = pipefd[1];
    }

    if(com->redirect_out != NULL)
    {
        // stops including spaces in file names.
        int count = 0;
        while(*(com->redirect_out+count) == ' ')
        {
            count++;
        }

        // open redirect_out save fd in out
        if((*out = open((com->redirect_out+count), O_RDWR | O_CREAT)) == -1)
        {
            perror("open");
            *out = 0;
            return -1;
        }
    } 
    else if(com->pipe_to != 0) 
    {
        if(pipe(pipefd) == -1)
        {
            perror("pipe");
            return -1;
        } else {
            *out = pipefd[1];
        }
    } 

    return 0;
}

void print_prompt(char * prompt)
{
    printf("\n\033[1;32m%s\033[0m ", prompt);
}

void exit_shell(int stat)
{
    printf("exit\n");
}

