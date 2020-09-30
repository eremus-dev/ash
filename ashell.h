#ifndef ASHELL_H
#define ASHELL_H

#include "parser.h"
#include "ashell_const.h"
#include "utilities.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


/**
 * Function to execute to fork child process and execvp the command given
 * including the arguments passed in command struct.
 * 
 * If the command struct background is not set, waits on child process.
 * 
 * Arguments:
 *      com - Command Structure containing commands context
 *      in - file descriptor to redirect stdin to
 *      out - file descriptor to redirect stdout to
 * 
 * Returns:
 *      void
 * 
 * Should not return in the child process, 
 */
void exec_command(command * com, int * in, int * out, int * close, int * child_count);

/**
 * Function to handle the redirection of the childs stdin or stdout to either file or pipe.
 * 
 * Identifies the needed redirection including , 
 * sets in and out to the file descriptor of the redirection to be duped in the child process.
 * 
 * Arguments:
 *      com - command * to structure that carries the commands context.
 *      in - int * to file descriptor to change stdin to.
 *      out - int * to file descriptor to change stdout to. 
 *      
 * Returns:
 *      int - 0 on success -1 on error.
 *  
 *      
 */
int handle_redirection(command * com, int * in, int * out, int * off, int * pipefd);

#endif