#include "ashell.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

bool example_test(void);

//parser tests:
bool parser_test(void);
bool parser_semicol_and_amp_test(void);
bool parser_pipe_test(void);
bool parser_spacing_test(void);
bool parser_double_sep_test(void);



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

    //';' and '&' separator recognition test
    if (parser_semicol_and_amp_test())
    {
        printf("function parser_semicol_and_amp_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_semicol_and_amp_test() failed.\n");
        fail++;
    }

    //'|' separator recognition test
    if (parser_pipe_test())
    {
        printf("function parser_pipe_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_pipe_test() failed.\n");
        fail++;
    }

    //multiple spaces no effect test
    if (parser_spacing_test())
    {
        printf("function parser_spacing_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_spacing_test() failed.\n");
        fail++;
    }

    //multiple spaces no effect test
    if (parser_double_sep_test())
    {
        printf("function parser_double_sep_test() passed.\n");
        success++;
    }
    else
    {
        printf("function parser_double_sep_test() failed.\n");
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
    /*
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls ; ; ls\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int i = 0;
    while (com_queue[i] != NULL) 
    {
        dump_structure(com_queue[i], i);  //print command structs
        //print_human_readable(com_queue[i], i);
        i++;
    }

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline*/

    return true;
}

bool parser_semicol_and_amp_test(void)
{
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls -l; ls & echo; ps&\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int com_count = 0;
    while (com_queue[com_count] != NULL) 
    {
        com_count++;
    }

    if (com_count != 4)
    {
        perror("ERROR: num of commands not matching\n");
        return false;
    }
    if (com_queue[0]->background != 0)
    {
        perror("ERROR: first command non matching background\n");
        return false;
    }
    if (com_queue[1]->background != 1)
    {
        perror("ERROR: second command non matching background\n");
        return false;
    }
    if (com_queue[2]->background != 0)
    {
        perror("ERROR: third command non matching background\n");
        return false;
    }
    if (com_queue[3]->background != 1)
    {
        perror("ERROR: fourth command non matching background\n");
        return false;
    }

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline

    return true;
}

bool parser_pipe_test(void)
{
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls | ps | echo\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int com_count = 0;
    while (com_queue[com_count] != NULL) 
    {
        com_count++;
    }

    if (com_count != 3)
    {
        perror("ERROR: num of commands not matching\n");
        return false;
    }
    
    if (com_queue[0]->pipe_to != 1)
    {
        perror("ERROR: first command pipe non matching correct com_queue element\n");
        return false;
    }
    if (com_queue[1]->pipe_to != 2)
    {
        perror("ERROR: second command pipe non matching correct com_queue element\n");
        return false;
    }
    if (com_queue[2]->pipe_to != 0)
    {
        perror("ERROR: third command pipe non matching correct com_queue element\n");
        return false;
    }

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline

    return true;
}

bool parser_spacing_test(void)
{
    char *newline_p;  //points to and replaces \n with \0.
    command **com_queue;  //array of pointers to command structs.
    char *commandline;  //holds commandline input.

    commandline = malloc(sizeof(char) * MAX_COMMAND_LEN);  //allocate memory to cmd
    
    //line = fgets(line, MAX_COMMAND_LEN, stdin);
    char *temp_line = "ls;ls ;ls;  ls     ;\n";  //newline required.
    strcpy(commandline, temp_line);

    newline_p = index(commandline, '\n');
    *newline_p = '\0';  //replace '\n' with '\0'

    com_queue = process_cmd_line(commandline, 1);

    int com_count = 0;
    while (com_queue[com_count] != NULL) 
    {
        com_count++;
    }

    if (com_count != 4)
    {
        perror("ERROR: num of commands not matching\n");
        return false;
    }
    

    clean_up(com_queue);  //free com_queue
    free(commandline);  //free commandline

    return true;
}

bool parser_double_sep_test(void)
{
    char *com1 = "ls ;; ls";
    char *com2 = "ls ; ; ls";
    char *com3 = "ls ;     ; ls";
    char *com4 = "ls;;ls";
    char *com5 = "ls;ls;";
    char *com6 = "ls ; ls";


    if(!check_double_sep(com1))
    {
        perror("ERROR: bad sep pair not found in com1\n");
        return false;
    }
    if(!check_double_sep(com2))
    {
        perror("ERROR: bad sep pair not found in com2\n");
        return false;
    }
    if(!check_double_sep(com3))
    {
        perror("ERROR: bad sep pair not found in com3\n");
        return false;
    }
    if(!check_double_sep(com4))
    {
        perror("ERROR: bad sep pair not found in com4\n");
        return false;
    }
    if(check_double_sep(com5))
    {
        perror("ERROR: false positive in com5\n");
        return false;
    }
    if(check_double_sep(com6))
    {
        perror("ERROR: false positive in com6\n");
        return false;
    }
    
    return true;
}