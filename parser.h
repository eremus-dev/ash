/*
Header file for the Job and Command Parser.

Returns a JOB queue of job structs for the ashell to execute.

JOB reference a Command Queue:

Command Queue:


*/

#include "ashell_const.h"

// The struct to store the context associated with a command.
typedef struct Command {
    char * commands[MAX_COMMAND_LEN]; // pointers to command token stored in ashell:commandline:6
    char stdin;
    char stdout;
} Command;

/**
 * The struct to store all command queue that compose a job and the context of the job..
 */
typedef struct JOB {
    Command * command_queue;
    int command_count;
    char sep;
} JOB;

/**
 * Function to parse the string received from the commandline.
 * returns number of Jobs in commandline.
 */
int parse_commandline(char * commandline, JOB * job_queue);