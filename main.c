#include "ashell.h"

int main(void) 
{
    
    char prompt[MAX_PROMPT] = ">>";
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.
    
    bool exit_flag = true;  //for checking if exit was entered

    while(exit_flag){
        print_prompt(prompt);

        commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
        commandline = fgets(commandline, MAX_COMMAND_LEN, stdin);
       
        // exits if CTL^D is entered
        if(commandline == NULL){
            feof(stdin);
            exit(0);
        }

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
            //dump_structure(com_queue[com_count], com_count);  //prints command structs, comment out in final version.
            com_count++;
        }

        for(int i=0; i<com_count; i++) //iterates through array of commands, executing each.
        {
            //printf("executing command %d\n", i);
            if (strcmp(com_queue[i]->com_name, "exit") == 0) //checks if exit is com_name
            {
                exit_flag = false;
                break;  //breaks out of for loop, com_queue and commandline should still free before prog terminates.
            }
            else if (strcmp(com_queue[i]->com_name, "cd") == 0)
            {
                int r = cd_command(com_queue[i]);
                if (r != 0)
                {
                    perror("cd error");
                    break;
                }
            }
            else if (strcmp(com_queue[i]->com_name, "pwd") == 0)
            {
                int r = pwd_command(com_queue[i]);
                if (r != 0)
                {
                    perror("pwd error");
                    break;
                }
            }
            else if(strcmp(com_queue[i]->com_name, "prompt") == 0)
            {
                if(change_prompt(prompt, com_queue[i]) == -1){
                    perror("prompt");
                    break;
                }
            }
            else
            {
                exec_command(com_queue[i]);
            }
            
        }

        clean_up(com_queue);
        free(commandline);
    }

    return 0;
}