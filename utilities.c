#include "utilities.h"

int pwd_command(command * com)
{
    char current_path[PATH_MAX];  //useing PATH_MAX from limits.h

    //counts number of arguments
    int num_args = 0;
    while (com->argv[num_args] != NULL)
    {
        num_args++;
    }

    //pwd should be by itself, so returns -1 if args not equal to 1.
    if (num_args != 1)
    {
        return -1;
    }
    
    //save current working directory to current_path.
    char *r = getcwd(current_path, PATH_MAX);

    //r == NULL if getcwd() failed in some way.
    if (r == NULL)
    {
        return -1;
    }

    printf("%s\n", current_path);
    
    return 0;
}

int cd_command(command * com)
{
    int num_args = 0;
    int r = 0;

    //count number of arguments.
    while (com->argv[num_args] != NULL)
    {
        num_args++;
    }

    if (num_args < 2) //just cd by itself.
    {
        //gets home directory path, then changes current directory to it.
        char * path_home = getenv("HOME");
        r = chdir(path_home);
    }
    else if (num_args > 2)  //cd x y should be invalid input
    {
        r = -1;
    }
    else  //cd /path/to/dir . returns -1 if chdir() fails.
    {
        r = chdir(com->argv[1]);
    }
    
    return r;
}

int change_prompt(char * curr_prompt, command * com){
    if(com->argv[1] != NULL){
        strncpy(curr_prompt, com->argv[1], MAX_PROMPT);
    } else {
        printf("Enter new prompt: ");
        fgets(curr_prompt, MAX_PROMPT, stdin);
        int len = strlen(curr_prompt);
        curr_prompt[len-1] = '\0';
    }

    return 0;
}

void print_prompt(char * prompt)
{
    printf("\33[2K");
    printf("\n\033[1;32m%s\033[0m ", prompt);
}

void exit_shell(int stat)
{
    printf("exit\n");
}

int signal_handler(void)
{
    // handle signal blocking registration.
    sigset_t sigset;

    if (sigemptyset(&sigset) == 0)
    {
        sigaddset(&sigset, SIGINT);
        sigaddset(&sigset, SIGQUIT);
        sigaddset(&sigset, SIGQUIT);
        sigaddset(&sigset, SIGTSTP);
    }
    else
    {
        return -1;
    }

    if (sigprocmask(SIG_BLOCK, &sigset, NULL) != 0)
    {
        perror("signal block failure");
        return -1;
    }

    // handle sig child registration
    struct sigaction chand;
    chand.sa_handler = child_handler;
    sigfillset(&(chand.sa_mask));

    if (sigaction(SIGCHLD, &chand, NULL) == -1)
    {
        perror("child handler registration");
        return -1;
    }

    return 0;
}

void child_handler(int signum)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        ;
}
