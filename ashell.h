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
 * 
 */
void exec_command(command * com);

/**
 * 
 */
void print_prompt(char * prompt);

/**
 * 
 */
void exit_shell(int stat);


#endif