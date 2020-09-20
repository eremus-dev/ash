#include "parser.h"



int parse_commandline(char * commandline, JOB * job_queue)
{
    
    char *tokens[MAX_COMMAND_LEN];

    tokenise(commandline, tokens);

    //fill_structs(tokens, job_queue);
    
    return 0;
}

void abort_parsing(int job_count, JOB * queue)
{
    return;
}

int tokenise (char line[], char *token[])
{
    char *tk;
    int i=0;

    tk = strtok(line, argumentseparators);
    token[i] = tk;

    while (tk != NULL) {

        ++i;
        if (i>=MAX_COMMAND_LEN) {
            i = -1;
            break;
        }

        tk = strtok(NULL, argumentseparators);
        token[i] = tk;
    }
    return i;
}