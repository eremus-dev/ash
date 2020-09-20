/*
Header file for the Job and Command Parser.

Returns a JOB queue of job structs for the ashell to execute.
*/
#ifndef PARSER_H
#define PARSER_H

#include "ashell_const.h"
#include <stddef.h> //for NULL
#include <string.h> //for strtok()
#include <stdio.h>
#include <stdlib.h> //for malloc()

#define jobseparators ";&\n"
#define commandseparators "<>|"
#define argumentseparators " "


/**
 *  The struct to store the context associated with a command.
 *  
 */
typedef struct Commands {
    //char * commands[MAX_COMMAND_LEN]; // points to token in commandline ashell.c:commandline:6
    int first; //index of first command arg in token
    int last; //index of last command arg in token
    char * stdin; // points to special stdin condition, eg. < or |
    char * stdout; // points to special stdout condition
} Command;

/**
 * The struct to store the command queue that composes a job and the context of the job.
 */
typedef struct Jobs {
    // pointers to command structs commandline in ashell.c:commandline:6 
    // to be dynamically allocated by parsers and free'd from ashell exec_command
    // 
    Command *command_queue[MAX_COMMAND_LEN]; 
    int command_count;
    char sep;
} JOB;

/**
 * Function to parse the string received from the commandline.
 * returns number of Jobs in commandline.
 */
int parse_commandline(char * commandline, JOB * job_queue);

/**
 * Function to free memory allocated in Job queue in the event of bad grammar
 */
void abort_parsing(int job_count, JOB * queue);

int tokenise (char line[], char *token[]);

void fill_structs(char *token[], JOB *job_queue);

void build_job_struct(JOB *job, char *token[], int start, int end, int sep);

void build_command_struct(Command *com, char *token[], int start, int end, int sep, int last_sep); 

#endif