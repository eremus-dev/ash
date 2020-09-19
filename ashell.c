#include "ashell.h"

void get_commandline(char * commandline)
{
    return;
}

void exec_command(Command * command_queue)
{
    return;
}

void exec_shell() {

    JOB job_queue[MAX_JOBS]; 
    char commandline[MAX_COMMAND_LEN]; 

    while(true){
        get_commandline(commandline);
        int jobcount = parse_commandline(commandline, job_queue);
        
        if(jobcount == -1)

        for(int i = 0; i < jobcount; i++){
            exec_command(job_queue[i].command_queue);
        }


    }

    return;
}

