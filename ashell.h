/**
 * Header file for the ashell execution module. 
 * Functionality implemented includes:
 *      command execution
 *      file and pipe input output redirection
 *      glob wildcard expansion
 */

#ifndef ASHELL_H
#define ASHELL_H

#include "parser.h"
#include "ashell_const.h"
#include "utilities.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <glob.h>

/**
 * Structure to carry redirection information and factiltate user closing pipe ends to prevent deadlocks.
 */
typedef struct
{
    int in;        // fd to read in from
    int out;       // fd to write out to
    int pipefd[2]; // both ends of the pipe
    int off;       // fd to shutdown to stop deadlocks
} fd_control;

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
void exec_command(command *com, fd_control *control);

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
int handle_redirection(command *com, fd_control *control);

/**
 * Function to handle the execution of commands. Implements handling for glob executing function. 
 * If glob wildcard is detected, execute using glob handline code, else normal execute.
 * Arguments:
 *   com - command * to command to execute.
 * Returns:
 *     -1 on error but should never return.
 */
int glob_exec(command *com);

/**
 * Function for checking if string contains a wildcard character.
 * Arguments:
 *   arg - char * string to check for wildcards.
 * Returns:
 *     int - 0 if wildcard found, -1 otherwise.
 */
int has_wildcard(char *arg);

#endif