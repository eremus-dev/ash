#include "parser.h"
#include "ashell_const.h"

#include <stdbool.h>

void exec_shell(void);
void get_commandline(char * commandline);
//int parse_commandline(char * commandline, JOB * job_queue);  moved to parser.h
void exec_command(Command * command_queue);