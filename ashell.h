#ifndef ASHELL_H
#define ASHELL_H

#include "parser.h"
#include "ashell_const.h"

#include <stdbool.h>
#include <unistd.h>

void exec_shell(void);
char * get_commandline(void);
void exec_command(Command * command_queue);
void print_prompt(void);
void exit_shell(int stat);

#endif