#include "parser.h"
#include "ashell_const.h"

#include <stdbool.h>

void exec_shell(void);
void get_commandline(char * commandline);
void exec_command(Command * command_queue);