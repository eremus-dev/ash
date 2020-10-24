#include "ashell.h"

void exec_command(command *com, fd_control *control)
{
    int status;

    pid_t check = fork();

    if (check < 0)
    {
        perror("fork");
        exit(-1);
    }
    else if (check == 0)
    {
        // redirect stdin if in != 0
        if (control->in != 0)
        {
            if (dup2(control->in, 0) == -1)
            {
                perror("stdin dup2");
                exit(-1);
            }
        }

        // redirect stdout if out != 0
        if (control->out != 0)
        {
            if (dup2(control->out, 1) == -1)
            {
                perror("stdout dup2");
                exit(-1);
            }
        }

        // shut unused pipe end.
        if (control->off != 0)
        {
            close(control->off);
            control->off = 0;
        }

        // if (execvp(com->argv[0], com->argv) == -1)
        // {
        //     perror(com->argv[0]);
        //     exit(-1);
        // }

        if (glob_exec(com) == -1)                      //execvp -> glob_exec() here
        {
            perror(com->argv[0]);
            exit(-1);
        }
        
    }
    else if ((check > 0) && (com->background == 0))
    {
        int again = 1;
        while (again)
        { // handle slow system call interrupt
            again = 0;
            pid_t pid = waitpid(check, &status, 0); // parent waits collecting child process for sequential commands.
            if (pid == -1)
            {
                if (errno == EINTR)
                {
                    again = 1;
                }
            }
        }
    }
    else if ((check > 0) && (com->background == 1))
    {
        printf("%d\n", check);
    }

    if (control->out != 0)
    {
        close(control->out);
        control->out = 0;
    }

    if (control->in != 0)
    {
        close(control->in);
        control->in = 0;
    }

    return;
}

int handle_redirection(command *com, fd_control *control)
{
    umask(0); // set umask for subsequent file openings.

    if (com->redirect_in != NULL)
    {
        // stops including spaces in file names.
        int count = 0;
        while (*(com->redirect_in + count) == ' ')
        {
            count++;
        }

        //open file descript and save to in
        if ((control->in = open(com->redirect_in + count, O_RDWR)) == -1)
        {
            perror("open");
            control->in = 0;
            return -1;
        }
    }
    else if (fcntl(control->pipefd[0], F_GETFD) != -1)
    {
        control->in = control->pipefd[0];
        control->off = control->pipefd[1];
    }

    if (com->redirect_out != NULL)
    {
        // stops including spaces in file names.
        int count = 0;
        while (*(com->redirect_out + count) == ' ')
        {
            count++;
        }

        // open redirect_out save fd in out
        if ((control->out = open((com->redirect_out + count), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG)) == -1)
        {
            perror("open");
            control->out = 0;
            return -1;
        }
    }
    else if (com->pipe_to != 0)
    {
        if (pipe(control->pipefd) == -1)
        {
            perror("pipe");
            return -1;
        }
        else
        {
            control->out = control->pipefd[1];
        }
    }

    return 0;
}


int glob_exec(command *com)
{
    glob_t globcom;

    int i=0;
    int wildcard = -1;

    for (i=0; i < sizeof(com->argv); i++)
    {
        if (has_wildcard(com->argv[i]) == 0)
        {
            wildcard = i;
            break;
        }
    }

    globcom.gl_offs = wildcard;

    int check;
  
    if( (check = glob(com->argv[wildcard], GLOB_DOOFFS | GLOB_PERIOD, NULL, &globcom)) != 0)
    {
        perror("glob");
        return -1;
    }
  

    for (int j=0; j<wildcard; j++)
    {
        globcom.gl_pathv[j] = com->argv[j];
    }


    if (wildcard != -1)
    {
        if(execvp(com->argv[0], &globcom.gl_pathv[0]) == -1){
            return -1;
        }
    }
    else
    {
        if(execvp(com->argv[0], com->argv) == -1)
        {
            return -1;
        }
    }
    
    // should never return
    printf("End of glob: Should never print\n");

    
    return 0;
}

int has_wildcard(char *arg)
{ 
    int l = strlen(arg);

    for (int i=0; i<l-1; i++)
    {
        if (arg[i] == '*' || arg[i] == '?')
        {
            return 0;
        }        
    }
    return -1;
}
