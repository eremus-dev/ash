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

/**
 * function to change the current prompt string to the argument passed to prompt command.
 * 
 * Arguments:
 *      prompt - prompt buffer
 *      com - command that carries argument for prompt if no argument get prompt interactively.
 * Return:
 *      void
 */
int change_prompt(char * prompt, command * com);

/**
 * function to display the current working directory.
 *  
 * Arguments:
 *      com - Command Strucutre that holds command context.
 * 
 *  Return:
 *       0 if successful, -1 if not.
 */
int pwd_command(command * com);

/**
 * function to navigate to a particular directory
 * 
 * Arguments:
 *      com - Command Structure that holds commands context
 * 
 * Returns:
 *      0 if successful, -1 if not.
 */
int cd_command(command * com);

/**
 * Function to print the prompt set in the main.c 
 * 
 * Can be changed by calling function prompt with an argument or without for interactive change.
 * 
 * Arguments:
 *      prompt - prompt buffer
 * 
 * Returns:
 *      void
 */
void print_prompt(char * prompt);

/**
 * Function to print exit on exit, probably shouldn't exist.
 */
void exit_shell(int stat);

#endif