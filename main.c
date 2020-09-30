#include "ashell.h"

int main(void) 
{
    
    char prompt[MAX_PROMPT] = "ashell --->"; // can be changed with call to prompt
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.
    int child_count = 0; // for keeping track of backgrounded processes
    bool exit_flag = true;  //for checking if exit was entered
    int print = 1; // for controlling printing of prompt
    
    while(exit_flag){

        if(print){
            print_prompt(prompt);
        }
        print = 1;
        
        commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
        commandline = fgets(commandline, MAX_COMMAND_LEN, stdin);
       
       
        // exits if CTL^D is entered
        if(commandline == NULL){
            feof(stdin);
            exit(0);
        }

        newline_p = index(commandline, '\n');
        *newline_p = '\0';  //replace '\n' with '\0'

        //checks if commandline is only spaces or empty
        if(check_if_empty(commandline))
        {
            perror("ERROR: empty commandline\n");
            free(commandline);
            continue;
        }
        //checks if invalid separator pair, frees commandline, moves to next loop.
        else if(check_double_sep(commandline))
        {
            perror("ERROR: invalid pair of separators\n");
            free(commandline);
            continue;
        }
        //checks if ant hanging '<', '>', or '|' at end of commandline.
        else if (check_last_separator(commandline))
        {
            perror("ERROR: invalid final separator\n");
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

        int in = 0; // file decriptor for stdin redirection
        int out = 0; // file descriptor for stdout redirection
        int off = 0; // pipe end to close.
        int pipefd[2] = {0}; // pipe fd's for handle redirection

        for(int i=0; i<com_count; i++) //iterates through array of commands, executing each.
        {
            // harvest zombies
            int pid;
            while( (pid = waitpid(-1, NULL, WNOHANG)) > 0 ){
                printf("[%d] Done %d\n", child_count, pid);
                child_count--;
                print_prompt(prompt);
                print = 0;
            }

            if (strcmp(com_queue[i]->com_name, "exit") == 0) //checks if exit is com_name
            {
                exit_flag = false;
                exit_shell(0);

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
            else if(strcmp(com_queue[i]->com_name, "") == 0)
            {
                print = 0;
                print_prompt(prompt);
            }
            else
            {
                if(handle_redirection(com_queue[i], &in, &out, &off, pipefd) != -1)
                {
                    //printf("Command: %s, in: %d, out: %d, off: %d\n", com_queue[i]->com_name, in, out, off);
                    exec_command(com_queue[i], &in, &out, &off, &child_count);
                } 
                

            }
            
        }
        
        clean_up(com_queue);
        free(commandline);
    }

    return 0;
}