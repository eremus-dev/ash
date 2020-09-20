#include "ashell.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

bool example_test(void);

int main(void) {
        
    int fail = 0;
    int success = 0;

    JOB j1[2];
    char *com = "ls -l";
    parse_commandline(com, j1);

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

