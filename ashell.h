#ifndef ASHELL_H
#define ASHELL_H

#include "parser.h"
#include "ashell_const.h"
#include "utilities.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exec_shell(void);
//char * get_commandline(void);
//void exec_command(JOB * job, char * token[]);
void print_prompt(void);
void exit_shell(int stat);


#endif