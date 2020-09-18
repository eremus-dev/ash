#include "parser.h"
#include "ashell_const.h"

#include <stdbool.h>

void exec_shell(void);
void get_command(char * commandline);
int parse_commandline(char * commandline, JOB * job_queue);