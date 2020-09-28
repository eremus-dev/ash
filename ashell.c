#include "ashell.h"


void exec_command(command * com, int in, int out)
{
    int status;

    int check = fork();
    if(check < 0)
    {
        perror("fork");
    }
    else if(check == 0)
    {
        // redirect stdin if in != 0
        if(in != 0){
            if(dup2(in, 0) == -1){
                perror("stdin dup2");
                return;
            }
        }

        // redirect stdout if out != 0
        if(out != 0){
            if(dup2(out, 1) == -1){
                perror("stdout dup2");
                return;
            }
        }

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

int handle_redirection(command * com, int * in, int * out, int * pipefd)
{
    if(com->redirect_out != NULL)
    {
        int count = 0;
        // open redirect_out save fd in out
        while(*(com->redirect_out+count) == ' '){
            count++;
        }
        if((*out = open((com->redirect_out+count), O_RDWR | O_CREAT)) == -1){
            perror("open");
            *out = 0;
            return -1;
        }
    } 
    else if(com->pipe_to != 0) 
    {
        if(pipe(pipefd) == -1){
            perror("pipe");
            return -1;
        } else {
            *out = pipefd[1];
        }
    }

    if(com->redirect_in != NULL)
    {
        if((*in = open(com->redirect_in, O_RDWR)) == -1){
            perror("open");
            *in = 0;
            return -1;
        }
    } else if(fcntl(pipefd[0], F_GETFD) != -1) {
        *in = pipefd[0];
    }

    return 0;
}

void print_prompt(char * prompt)
{
    printf("\n%s ", prompt);
}

void exit_shell(int stat)
{
    printf("exit\n");
}

