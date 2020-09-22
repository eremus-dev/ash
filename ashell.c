#include "ashell.h"



void exec_shell() {

    JOB job_queue[MAX_JOBS];
    char * tokens[MAX_ARG_LEN]; 
    
    char * commandline = malloc(MAX_COMMAND_LEN);
    if(commandline == NULL){
        perror("Error: Commandline allocation failure");
    }

    while(true){
        get_commandline(commandline);
        int jobcount = parse_commandline(commandline, job_queue, tokens);
        
        if(jobcount == -1)

        for(int i = 0; i < jobcount; i++){
            //exec_command(job_queue[i].command_queue);
        }


    }

    return;
}

// Function partly inspired by write up: https://brennan.io/2015/01/16/write-a-shell-in-c/
void get_commandline(char * commandline)
{
    int check = getline(commandline, MAX_COMMAND_LEN, stdin);

    if(check == -1){
        if(feof(stdin)){
            exit(0);
        } else {
            perror("ERROR: In get_commandline, getline failed.");
            exit(-1);
        }
    }
 
    return;
}

void exec_command(Command * command_queue)
{
    return;
}
