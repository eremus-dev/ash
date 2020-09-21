#include "ashell.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

bool example_test(void);
bool parse_commandline_test(void); 

int main(void) {
        
    int fail = 0;
    int success = 0;

    if(parse_commandline_test()){
        printf("Test parse_commandline_test passed\n");
        success++;
    } else {
        printf("Test parse_commandline_test failed\n");
        fail++;
    }

    if(example_test()){
        success++;
    } else {
        fail++;
    }

    printf("Test passed %d\nTest failed %d\n", success, fail);

    return 0;
}

bool example_test(void){

    if(true){
        printf("Test example_test: test passed\n");
        return true;
    } else {
        printf("Test example_test: test_failed\n");
        return false;
    }
}

bool parse_commandline_test(){ 
 
    JOB job_queue[MAX_JOBS];
 
    char * tokens[MAX_ARG_LEN];
    char com[] = "ls -l | echo ; ps -lH ; ls ; echo ; ls & ps -e ;";
 
    int job_count = parse_commandline(com, job_queue, tokens);

    for(int i = 0; i < job_count; i++){
        printf("\nJob %d:\n", i);
        
        for(int j = 0; j < job_queue[i].command_count; j++){            
            int t = job_queue[i].command_queue[j]->first;
            int n = 0;

            printf("Command %d: ", j); 
            while( (t+n) !=  job_queue[i].command_queue[j]->last+1 ) {
                
                printf("%s ", tokens[t + n]);
                n++;        
            }
        
            printf("\n");
        }
        printf("\n");
    }

    free_queue(job_queue, job_count);
    return false;

}
