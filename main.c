#include "ashell.h"

int utility_function_handler(command *current, char *prompt);


int main(void)
{
    char prompt[MAX_PROMPT] = "ashell --->"; // can be changed with call to prompt
    char *newline_p;                         //points to and replaces \n with \0.
    command **com_queue;                     //array of pointers to command structs.
    char *commandline = NULL;                //holds commandline input.
    bool exit_flag = true;                   //for checking if exit was entered
    int print = 1;                           // for controlling printing of prompt

    // blocks SIGINT, SIGQUIT, SIGSTOP and registers SIGCHILD handler.
    if (signal_handler() == -1)
    {
        perror("signal handler registration failure");
        exit(-1);
    }

    while (exit_flag)
    {

        if (print)
        {
            print_prompt(prompt);
        }
        print = 1;

        char buf[sizeof(char) * MAX_COMMAND_LEN] = {'\0'}; // buffer for main commandline
        commandline = buf;

        commandline = fgets(commandline, MAX_COMMAND_LEN, stdin);

        // Check for slow system call failure for the slow system calls above.
        if (commandline == NULL)
        { // exits if CTL^D is entered or if slow function call above has failed continue.
            if (feof(stdin) != 0)
            {
                exit(0);
            }
            else if (errno == EINTR)
            {
                continue;
            }
            else
            {
                continue;
            }
        }

        newline_p = index(commandline, '\n');
        *newline_p = '\0'; //replace '\n' with '\0'

        if (check_if_empty(commandline)) //checks if commandline is only spaces or empty
        {
            //perror("ERROR: empty commandline\n");
            continue;
        }
        else if (check_double_sep(commandline)) //checks if invalid separator pair, frees commandline, moves to next loop.
        {
            perror("ERROR: invalid pair of separators\n");
            continue;
        }
        else if (check_last_separator(commandline)) //checks if ant hanging '<', '>', or '|' at end of commandline.
        {
            perror("ERROR: invalid final separator\n");
            continue;
        }

        com_queue = process_cmd_line(commandline, 1); 

        int com_count = 0;
        while (com_queue[com_count] != NULL)
        {
            com_count++;
        }

        fd_control control;    // struct to encode input and output state.
        control.in = 0;        // file decriptor for stdin redirection
        control.out = 0;       // file descriptor for stdout redirection
        control.off = 0;       // pipe end to close.
        control.pipefd[0] = 0; // pipe fd's for handle redirection
        control.pipefd[1] = 0;

        for (int i = 0; i < com_count; i++) //iterates through array of commands, executing each.
        {

            int check;
            if ((check = utility_function_handler(com_queue[i], prompt)) != 0) //checks if exit is com_name
            {
                if (check == 2)
                {
                    exit_flag = false;
                    exit_shell(0);
                    break; //breaks out of for loop, com_queue and commandline should still free before prog terminates.
                }
            }
            else
            {
                if (handle_redirection(com_queue[i], &control) != -1)
                {
                    exec_command(com_queue[i], &control);
                }
            }
        }
        clean_up(com_queue);
    }

    return 0;
}

/**
 * Function to handle the calling of the utility functions specified in utilities.h
 * 
 * Arguments:
 *      current - Commmand to check for utility
 * 
 * Return:
 *      int - 0 if no utility function executed, 1 or 2 to designate side effects of function.
 */
int utility_function_handler(command *com, char *prompt)
{
    if (strcmp(com->com_name, "exit") == 0) //checks if exit is com_name
    {
        return 2; //breaks out of for loop, com_queue and commandline should still free before prog terminates.
    }
    else if (strcmp(com->com_name, "cd") == 0)
    {
        int r = cd_command(com);
        if (r != 0)
        {
            perror("cd error");
            return -1;
        }
        return 1;
    }
    else if (strcmp(com->com_name, "pwd") == 0)
    {
        int r = pwd_command(com);
        if (r != 0)
        {
            perror("pwd error");
            return -1;
        }
        return 1;
    }
    else if (strcmp(com->com_name, "prompt") == 0)
    {
        if (change_prompt(prompt, com) == -1)
        {
            perror("prompt");
            return -1;
        }
        return 1;
    }

    return 0;
}
