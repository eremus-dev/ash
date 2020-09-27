/*
Header file for the shell utilties. 
Functions to implement:
    change prompt
    cd
    exit
*/
#ifndef UTILITIES_H
#define UTILITIES_H

#include "parser.h"

#include <unistd.h>
#include <limits.h>

// function to change the current prompt string.
void change_prompt(char * new_string);

// function to change the current working directory.
int pwd_command(command * com);

int cd_command(command * com);


#endif