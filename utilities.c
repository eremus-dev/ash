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
    
    int num_args = 0;
    int r = 0;

    //count number of arguments.
    while (com->argv[num_args] != NULL)
    {
        num_args++;
    }

    if (num_args != 2)
    {
        r = -1;
    }
    else
    {
        strncpy(curr_prompt, com->argv[1], MAX_PROMPT);
        r = 0;
    }
    

    /*if(com->argv[1] != NULL){
        strncpy(curr_prompt, com->argv[1], MAX_PROMPT);
    } else {
        return -1;
    }*/

    return r;
}
