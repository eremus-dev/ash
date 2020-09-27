#include "ashell.h"


void exec_shell() {

    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.
    
    bool exit_flag = true;  //for checking if exit was entered

    // never returns
    while(exit_flag){
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
            dump_structure(com_queue[com_count], com_count);  //prints command structs, comment out in final version.
            com_count++;
        }

        for(int i=0; i<com_count; i++) //iterates through array of commands, executing each.
        {
            printf("executing command %d\n", i);
            if (strcmp(com_queue[i]->com_name, "exit") == 0) //checks if exit is com_name
            {
                exit_flag = false;
                break;  //breaks out of for loop, com_queue and commandline should still free before prog terminates.
            }
            
            //exec_command(&job_queue[i], tokens);
        }

        clean_up(com_queue);
        free(commandline);
    }

    return;
}

// Function partly inspired by write up: https://brennan.io/2015/01/16/write-a-shell-in-c/
/*char * get_commandline(void)
{
    char * commandline = NULL;
    ssize_t MAX = 0;

    int check = getline(&commandline, &MAX, stdin);

    if(check == -1){
        if(feof(stdin)){
            exit_shell(EOF);
            exit(0);
        } else {
            perror("get_commandline");
            exit(-1);
        }
    }
 
    return commandline;
}*/

/*void exec_command(command * job, char * token[])
{

    for(int i = 0; i < job->command_count; i++){
        int com_len = (job->command_queue[i]->last - job->command_queue[i]->first);
        char * com_vec[com_len+1];

        // handle redirection
        if(job->command_queue[i]->in_sep != NULL | job->command_queue[i]->out_sep != NULL){
            //handle redirection
        }

        int count = 0;
        for(int j = job->command_queue[i]->first; j <= job->command_queue[i]->last; j++) {
            com_vec[count++] = token[j];
            printf("Argument %d to exec: %s\n", count, com_vec[count-1]);
        }

        com_vec[count] = (char *) NULL;

        // do something about the PATH.

        pid_t child = fork();
        
        if(child < 0){
            perror("fork");
            exit(-1);
        } else if (child == 0) {
            int check = execv("/usr/bin", com_vec);
        
            if(check == -1){
                perror("execv");
            }

            printf("child exiting\n");
            exit(-1);
        } else if(!strcmp(token[job->sep],";")) {
            printf("Child: %d\n", child);
            waitpid(child, NULL, 0);
        }
    }
    
    return;
}*/

void print_prompt(void){
    printf(">> ");
}

void exit_shell(int stat){
    printf("exit\n");
}