#include "ashell.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

bool example_test(void);

//parser tests:
bool parser_test(void);
bool parser_semicolon_test(void);


int main(void) 
{  
    int fail = 0;
    int success = 0;

    

    //parser tests

    //general parser testing test
    if (parser_test())
    {
        printf("function parser_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_test() failed.\n");
        fail++;
    }

    //semicolon separator recognition test
    if (parser_semicolon_test())
    {
        printf("function parser_semicolon_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_semicolon_test() failed.\n");
        fail++;
    }




    //Example test
    if (example_test())
    {
        printf("function example_test() passed.\n");
        success++;
    }
    else
    {
        printf("function example_test() failed.\n");
        fail++;
    }

    printf("PASSES: %d, FAILS: %d\n", success, fail);
}

bool example_test(void)
{
    if(true)
    {
        //printf("Test example_test: test passed\n");
        return true;
    } 
    else 
    {
        //printf("Test example_test: test_failed\n");
        return false;
    }
}

bool parser_test(void)
{
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls -l |ps -H & file.txt\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int i = 0;
    while (com_queue[i] != NULL) {
        dump_structure(com_queue[i], i);  //print command structs
        //print_human_readable(com_queue[i], i);
        i++;
    }

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline

    return true;
}

bool parser_semicolon_test(void)
{
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls -l|ps&\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int i = 0;
    while (com_queue[i] != NULL) {
        dump_structure(com_queue[i], i);  //print command structs
        //print_human_readable(com_queue[i], i);
        i++;
    }

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline

    return true;
}