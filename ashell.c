#include "ashell.h"

void exec_shell() {

    JOB job_queue[MAX_JOBS];
    char * tokens[MAX_ARG_LEN]; 
    
    // never returns
    while(true){
        print_prompt();
        char * commandline = get_commandline();

        add_sep_spacers(commandline);

        int jobcount = parse_commandline(commandline, job_queue, tokens);
        
        

        if(jobcount == -1){
            perror("parser");
        }

        printf("Job Count: %d\n", jobcount);
        print_jobs(job_queue, jobcount, tokens);

        // for(int i = 0; i <= jobcount; i++){
        //     exec_command(&job_queue[i], tokens);
        // }
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

void exec_command(JOB * job, char * token[])
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
}

void print_prompt(void){
    printf(">> ");
}

void exit_shell(int stat){
    printf("exit\n");
}