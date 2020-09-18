#include "ashell.h"
#include <assert.h>
#include <stdio.h>

#define TOTAL 1

int example_test(void);

int main(void) {
        
    int fails = 0;

    fails += example_test(void);

    printf("Test passed %d\nTest failed %d\n", TOTAL-fails, fails);

    return 0;
}

void example_test(void) {

    if(true){
        printf("Test example_test: test passed\n");
        return 0;
    } else {
        printf("Test example_test: test_failed\n");
        return 1;
    }

}
