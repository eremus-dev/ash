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
#define argumentseparators " \n"


/**
 *  The struct to store the context associated with a command.
 *  
 */
typedef struct Commands {
    //char * commands[MAX_COMMAND_LEN]; // points to token in commandline ashell.c:commandline:6
    int first; //index of first command arg in token array
    int last; //index of last command arg in token array
    char * in_sep; // points to special in_sep condition, eg. < or | (NULL if no condition)
    char * out_sep; // points to special out_sep condition
} Command;

/**
 * The struct to store the command queue that composes a job and the context of the job.
 */
typedef struct Jobs {
    // pointers to command structs commandline in ashell.c:commandline:6 
    // to be dynamically allocated by parsers and free'd from ashell exec_command
    // 
    Command *command_queue[MAX_COMMAND_LEN]; //array of command structs, remember to free()
    int command_count; //number of command structs in command_queue.
    int sep; //index of separator in token array for this job (& or ;). 
} JOB;

/**
 * Function to parse the string received from the commandline.
 * returns number of Jobs in commandline.
 */
int parse_commandline(char * commandline, JOB * job_queue, char * tokens[]);

/**
 * Function to free memory allocated in Job queue in the event of bad grammar
 */
void abort_parsing(int job_count, JOB * queue);

/**
 * Function to terminate commandline with ';' if not already terminated
 */
void terminate_command(char line[]);

/**
 * Function to separate a string into an array of tokens.
 */
int tokenise (char line[], char *token[]);

/**
 * Function that splits tokens into jobs, to be assigned to JOB structs.
 */
int fill_structs(char *token[], JOB *job_queue);

/**
 * Function that fills out a job struct, creating and saving its command structs.
 */
void build_job_struct(JOB *job, char *token[], int start, int end, int sep);

/**
 * Function that assigns command information to command struct.
 */
void build_command_struct(Command *com, char *token[], int start, int end, int sep, int last_sep); 

/**
 * Function that prints all information about a job queue. (for troublshooting).
 */
void print_jobs(JOB * queue, int num_jobs, char * token[]);

/**
 * Function that prints all tokens in a token array. (for troubleshooting).
 */
void print_tokens(char *token[]);

/**
 * Function that frees all malloced memory in job queue.
 */
void free_queue(JOB *queue, int job_count);

/**
 * Function that adds space characters between each of the special separator characters ';','&','|','<','>'.
 */
void add_sep_spacers(char * commandline);

#endif