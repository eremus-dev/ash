#include "utilities.h"

int pwd_command(command * com)
{
    char current_path[PATH_MAX];

    int num_args = 0;
    while (com->argv[num_args+1] != NULL)
    {
        num_args++;
    }

    if (num_args != 0)
    {
        return -1;
    }
    

    char *r = getcwd(current_path, PATH_MAX);

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

    while (com->argv[num_args+1] != NULL)
    {
        num_args++;
    }

    if (num_args < 1)
    {
        char * path_home = getenv("HOME");
        r = chdir(path_home);
    }
    else if (num_args > 1)
    {
        r = -1;
    }
    else
    {
        //cd /path/to/dir.
    }
    
    
    return r;
}

