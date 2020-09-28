#ifndef ASHELL_H
#define ASHELL_H

#include "parser.h"
#include "ashell_const.h"
#include "utilities.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * Function to execute to fork child process and execvp the command given
 * including the arguments passed in command struct.
 * 
 * If the command struct background is not set, waits on child process.
 * 
 * Should not return in the child process, 
 */
void exec_command(command * com);

/**
 * Function to print the prompt set in the main.c 
 * 
 * Can be changed by calling function prompt with an argument or without for interactive change.
 */
void print_prompt(char * prompt);

/**
 * Function to print exit on exit, probably shouldn't exist.
 */
void exit_shell(int stat);


#endif