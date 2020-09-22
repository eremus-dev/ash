#include "ashell.h"

void exec_shell() {

    JOB job_queue[MAX_JOBS];
    char * tokens[MAX_ARG_LEN]; 
    
    while(true){
        print_prompt();
        char * commandline = get_commandline();

        int jobcount = parse_commandline(commandline, job_queue, tokens);
        
        printf("Job Count: %d\n", jobcount);

        if(jobcount == -1){
            printf("Job Count Error: -1");
        }

        print_jobs(job_queue, jobcount, tokens);

        for(int i = 0; i <= jobcount; i++){
            //exec_command(job_queue[i].command_queue);
        }
    }

    return;
}

// Function partly inspired by write up: https://brennan.io/2015/01/16/write-a-shell-in-c/
char * get_commandline(void)
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
}

void exec_command(Command * command_queue)
{
    return;
}

void print_prompt(void){
    printf(">> ");
}

void exit_shell(int stat){
    printf("exit\n");
}