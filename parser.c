#include "parser.h"



int parse_commandline(char * commandline, JOB * job_queue)
{
    
    char *tokens[MAX_COMMAND_LEN];

    tokenise(commandline, tokens);

    fill_structs(tokens, job_queue);

    
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

void fill_structs(char *token[], JOB *job_queue)
{
    int job_num = 0;
    int i = 0;
    int start = 0;

    while (token[i] != NULL)
    {
        if (token[i] == ";")  //add functionality for ; & separators
        {
            JOB *j1 = malloc(sizeof(JOB));
            build_job_struct(j1, token, start, i-1, i);
            job_queue[job_num] = *j1;
            job_num++;
            start = i+1;

        }
        i++;
    }

    return;
}

void build_job_struct(JOB *job, char *token[], int start, int end, int sep)
{
    int com_num = 0;
    int i = start;
    int last_sep = -1;

    while (token[i] != NULL && i <= end)
    {
        if (token[i] == "|")  //add functionality for | < > separators
        {
            Command *c1 = malloc(sizeof(Command));
            build_command_struct(c1, token, start, i-1, i, last_sep);
            last_sep = i;
            job->command_queue[com_num] = c1;  //why c1 and not *c1 like for *j1?
            com_num++;
            start = i+1;

        }
        else if (token[i+1] == NULL)
        {
            Command *c1 = malloc(sizeof(Command));
            build_command_struct(c1, token, start, i, -1, last_sep);  //bug: if last command, points to last char.
            last_sep = -1;
            job->command_queue[com_num] = c1;
            com_num++;
            start = i+1;

        }
        i++;
    }
    
    job->sep = sep;
    
    return;
}

void build_command_struct(Command *com, char *token[], int start, int end, int sep, int last_sep)
{
    com->first = start;
    com->last = end;
    com->stdout = sep < 0 ? NULL : token[sep];
    com->stdin = last_sep < 0 ? NULL : token[last_sep];
    
    return;
}

/*void print_jobs(JOB * queue, char * token[])
{

}*/