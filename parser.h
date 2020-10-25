#ifndef _PARSER_H
#define _PARSER_H

/*
 * Parser.h
 * Data structures and various defines for parser.c
 * Author : Michael Roberts <mroberts@it.net.au>
 * Last Update : 15/07/01
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ashell_const.h"

/*The length of the command line.*/
#define CMD_LENGTH 256

/*Whitespaces that are searched for*/
// nick modified this
//static const char white_space[2] = { (char) 0x20, (char) 0x09 };
static const char white_space[3] = { (char) 0x20, (char) 0x09, (char) 0x00 };

/**
 * The Structure we create for the commands.
 * com_name : pointer to command name.
 * argv : pointer to array of command arguments.
 * background : command to be run in background.
 * redirect_in : pointer to file  name string
 * redirect_out : pointer to file name string
 * pipe_to : command array index to pipe output to.
 */
typedef struct Command_struct
{
   char *com_name; // command name string
   char **argv;    // char array of command args
   int background;  //1 if & present, 0 if not.
   char *redirect_in; // pointer to file  name string
   char *redirect_out; // pointer to file  name string
   int pipe_to;  //index to command array element.
}
command;

/*
 * This function processes the command line. It isolates tokens seperated by
 * the '&' or the '|' character. The tokens are then passed on to be processed
 * by other functions. Once the first token has been isolated this function is
 * called recursivly to process the rest of the command line. Once the entire
 * command line has been processed an array of command structures is created
 * and returned.
 *
 * Arguments :
 *      cmd - the command line to be processed.
 *
 * Returns : 
 *      An array of pointers to command structures.
 *
 */
command ** process_cmd_line(char *cmd, int first);

/*
 * This function parses the commands isolated from the command line string in
 * other functions. It searches the string looking for input and output
 * redirection characters. The simple commands found are sent to
 * process_simple_comd(). The redirection information is stored in the result
 * command structure.
 *
 * Arguments :
 *      cmd - the command string to be processed.
 *      result - the command structure to store the results in.
 *
 * Returns :
 *      None.
 *
 */
void process_cmd(char *cmd, command * result);

/*
 * This function breakes the simple command token isolated in other functions
 * into a sequence of arguments. Each argument is bounded by white-spaces, and
 * there is no special character intepretation. The results are stored in the
 * argv array of the result command structure.
 * 
 * Arguments :
 *      cmd - the string to be processed.
 *      result - the comand struct to store the results in.
 *
 * Returns :
 *      None.
 *
 */
void process_simple_cmd(char *cmd, command * result);

/*
 * This function cleans up some of the dynamicly allocated memory. Each array
 * element is visited, and the contained data is free'd before the entire
 * structure is free'd.
 *
 * Arguments :
 *      cmd - the array of pointers to command structures to be cleaned.
 *
 * Returns :
 *      None.
 *
 */
void clean_up(command ** cmd);

/*
 * This function dumps the contents of the structure to stdout.
 *
 * Arguments :
 *      c - the structure to be displayed.
 *      count - the array position of the structure.
 *
 * Returns :
 *      None.
 *
 */
void dump_structure(command * c, int count);

/*
 * This function dumps the contents of the structure to stdout in a human
 * readable format..
 *
 * Arguments :
 *      c - the structure to be displayed.
 *      count - the array position of the structure.
 *
 * Returns :
 *      None.
 *
 */
void print_human_readable(command * c, int count);

/**
 * Checks if two separators are adjecent or separated by only whitespaces. 
 * newline char needs to be replaced with '\0' before call.
 * returns true if an invlaid separator pair is found, and false otherwise.
 */
bool check_double_sep(char *line);

/**
 * Checks if any '>', '<', or '|' are the last separators. newline char needs to be 
 * replaced with '\0' before the call. returns true if an invalid separator is 
 * found, and false otherwise.
 */
bool check_last_separator(char * line);

/**
 * Checks if the input line is only spaces before '\0'. returns true if only spaces found,
 * and false otherwise.
 */
bool check_if_empty(char * line);

#endif
