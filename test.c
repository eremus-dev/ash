#include "ashell.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

bool example_test(void);

//parser tests:
bool parse_commandline_test(void); 
bool parse_check_job_sep(void);
bool parse_check_com_arg(void);
bool parse_check_com_sep(void);


int main(void) {
        
    int fail = 0;
    int success = 0;

    //parser tests

    //struct visual check test
    if(parse_commandline_test()){
        printf("Test parse_commandline_test passed\n");
        success++;
    } else {
        printf("Test parse_commandline_test failed\n");
        fail++;
    }
    
    //job structs separator test
    if(parse_check_job_sep()){
        printf("Test parse_check_job_sep passed\n");
        success++;
    } else {
        printf("Test parse_check_job_sep failed\n");
        fail++;
    }

    //command arg match test
    if(parse_check_com_arg()){
        printf("Test parse_check_com_arg passed\n");
        success++;
    } else {
        printf("Test parse_check_com_arg failed\n");
        fail++;
    }

    //command sep match test
    if(parse_check_com_sep()){
        printf("Test parse_check_com_sep passed\n");
        success++;
    } else {
        printf("Test parse_check_com_sep failed\n");
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

    // TEST for "ls -l | echo ;"
    if (strcmp(tokens[job_queue[0].command_queue[0]->first + 0], "ls") != 0) 
    {
        perror("ERROR: Job 0 - Command 0 - Token 0");
        return false;
    }

    if (strcmp(tokens[job_queue[0].command_queue[0]->first + 1], "-l") != 0) 
    {
        perror("ERROR: Job 0 - Command 0 - Token 1");
        return false;
    }

    if (strcmp(job_queue[0].command_queue[0]->stdout, "|") != 0) 
    {
        perror("ERROR: Job 0 - Command 0 - Stdout");
        return false;
    }

    if (strcmp(tokens[job_queue[0].command_queue[1]->first], "echo") != 0) 
    {
        perror("ERROR: Job 0 - Command 1 - Token 0");
        return false;
    }

    if (strcmp(job_queue[0].command_queue[1]->stdin, "|") != 0) 
    {
        perror("ERROR: Job 0 - Command 1 - stdin");
        return false;
    }

    if (strcmp(tokens[job_queue[0].sep], ";") != 0) 
    {
        perror("ERROR: Job 0 - sep");
        return false;
    }

    // TEST for "ps -lH ;"
    if (strcmp(tokens[job_queue[1].command_queue[0]->first + 0], "ps") != 0) 
    {
        perror("ERROR: Job 1 - Command 0 - Token 0");
        return false;
    }

    if (strcmp(tokens[job_queue[1].command_queue[0]->first + 1], "-lH") != 0) 
    {
        perror("ERROR: Job 1 - Command 0 - Token 1");
        return false;
    }
    
    if (strcmp(tokens[job_queue[1].sep], ";") != 0) 
    {
        perror("ERROR: Job 1 - Command 0 - sep");
        return false;
    }

    free_queue(job_queue, job_count);
    return true;

}

bool parse_check_job_sep(void)
{
    JOB job_queue[MAX_JOBS];
 
    char * tokens[MAX_ARG_LEN];

    //assuming commands and separated are spaced apart, and command is ended with ';'.
    char com[] = "ls -l ; ps & echo ;";
 
    int job_count = parse_commandline(com, job_queue, tokens);

    if (job_count != 3)  //check correct number of jobs were collected.
    {
        perror("ERROR: job_count not matching.");
        return false;
    }
    //to do: add check for index out of range error.
    if (strcmp(tokens[job_queue[0].sep], ";") != 0)  //check that first job has ';' separator.
    {
        perror("ERROR: job struct ';' separator not matching");
        return false;
    }
    
    if (strcmp(tokens[job_queue[1].sep], "&") != 0)  //check that second job has '&' separator.
    {
        perror("ERROR: job struct '&' separator not matching");
        return false;
    }
    
    if (strcmp(tokens[job_queue[2].sep], ";") != 0)  //check that third job has ';' separator.
    {
        perror("ERROR: job struct ';' separator not matching");
        return false;
    }
    
    free_queue(job_queue, job_count);  //free the queue
    return true;
}

bool parse_check_com_arg(void)
{
    JOB job_queue[MAX_JOBS];
 
    char * tokens[MAX_ARG_LEN];

    //assuming commands and separated are spaced apart, and command is ended with ';'.
    char com[] = "ls ; ps -t -a ;";
 
    int job_count = parse_commandline(com, job_queue, tokens);

    if (job_count != 2)  //check correct number of jobs were collected.
    {
        perror("ERROR: job_count not matching.");
        return false;
    }
    //to do: add check for index out of range error.
    if (strcmp(tokens[job_queue[0].command_queue[0]->first], "ls") != 0)  //check that first command is 'ls'.
    {
        perror("ERROR: first job first command not matching.");
        return false;
    }

    if (strcmp(tokens[job_queue[1].command_queue[0]->first], "ps") != 0)  //check that first command is 'ps'.
    {
        perror("ERROR: second job first command not matching");
        return false;
    }

    if (strcmp(tokens[job_queue[1].command_queue[0]->first], "ps") != 0)  //check that second command is '-t'.
    {
        perror("ERROR: second job first command not matching");
        return false;
    }

    if (strcmp(tokens[job_queue[1].command_queue[0]->first], "ps") != 0)  //check that second command is '-a'.
    {
        perror("ERROR: second job second command not matching");
        return false;
    }
    
    free_queue(job_queue, job_count);  //free the queue
    return true;
}

bool parse_check_com_sep(void)
{
    JOB job_queue[MAX_JOBS];
 
    char * tokens[MAX_ARG_LEN];

    //assuming commands and separated are spaced apart, and command is ended with ';'.
    char com[] = "ls -l | echo ; ps > file.txt ; echo < file.txt ;";
 
    int job_count = parse_commandline(com, job_queue, tokens);

    if (job_count != 3)  //check correct number of jobs were collected.
    {
        perror("ERROR: job_count not matching.");
        return false;
    }
    //to do: add check for index out of range error.
    if (job_queue[0].command_queue[0]->stdin != NULL)  //check that first command left separator is null.
    {
        perror("ERROR: first job first command right separator not matching NULL.");
        return false;
    }

    if (strcmp(job_queue[0].command_queue[0]->stdout, "|") != 0)  //check that first command right separator is '|'.
    {
        perror("ERROR: first job first command left separator not matching '|'.");
        return false;
    }

    if (strcmp(job_queue[0].command_queue[1]->stdin, "|") != 0)  //check that second command left separator is '|'.
    {
        perror("ERROR: first job second command left separator not matching '|'.");
        return false;
    }

    if (job_queue[0].command_queue[1]->stdout != NULL)  //check that second command right separator is null.
    {
        perror("ERROR: first job second command right separator not matching NULL.");
        return false;
    }

    if (strcmp(job_queue[1].command_queue[0]->stdout, ">") != 0)  //check that first command right separator is '>'.
    {
        perror("ERROR: second job first command right separator not matching '>'.");
        return false;
    }

    if (strcmp(job_queue[1].command_queue[1]->stdin, ">") != 0)  //check that second command left separator is '>'.
    {
        perror("ERROR: second job second command left separator not matching '>'.");
        return false;
    }

    if (strcmp(job_queue[2].command_queue[0]->stdout, "<") != 0)  //check that first command right separator is '<'.
    {
        perror("ERROR: third job first command right separator not matching '<'.");
        return false;
    }

    if (strcmp(job_queue[2].command_queue[1]->stdin, "<") != 0)  //check that second command left separator is '<'.
    {
        perror("ERROR: third job second command left separator not matching '<'.");
        return false;
    }
    
    free_queue(job_queue, job_count);  //free the queue
    return true;
}