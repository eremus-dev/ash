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
#include <linux/limits.h>

// function to change the current prompt string to the argument passed to prompt command.
int change_prompt(char * prompt, command * com);

// function to display the current working directory.
// returns 0 if successful, -1 if not.
int pwd_command(command * com);

// function to navigate to a particular directory
// returns 0 if successful, -1 if not.
int cd_command(command * com);


#endif