#include "ashell.h"


void exec_shell() {

    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.
    
    // never returns
    while(true){
        print_prompt();

        commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
        commandline = fgets(commandline, MAX_COMMAND_LEN, stdin);

        newline_p = index(commandline, '\n');
        *newline_p = '\0';  //replace '\n' with '\0'

        //checks if invalid separator pair, frees commandline, moves to next loop.
        if(check_double_sep(commandline))
        {
            perror("ERROR: invalid pair of separators\n");
            free(commandline);
            continue;
        }

        com_queue = process_cmd_line(commandline, 1);

        int com_count = 0;
        while (com_queue[com_count] != NULL) 
        {
            dump_structure(com_queue[com_count], com_count);
            com_count++;
        }

        clean_up(com_queue);
        free(commandline);
    }

    return;
}

// Function partly inspired by write up: https://brennan.io/2015/01/16/write-a-shell-in-c/
char * get_commandline(void)
{
 
    return (char *) NULL;
}

void exec_command(void)
{
    
    return;
}

void print_prompt(void){
    printf(">> ");
}

void exit_shell(int stat){
    printf("exit\n");
}