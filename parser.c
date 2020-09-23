#include "parser.h"



int parse_commandline(char * commandline, JOB * job_queue, char * tokens[])
{
    //terminate_command(commandline); 
    
    tokenise(commandline, tokens);

    int job_num = fill_structs(tokens, job_queue);
    
    return job_num;
}

void abort_parsing(int job_count, JOB * queue)
{
    free_queue(queue, job_count);
    exit(-1);
}

/*
segfaults because no space is added before ';', 
however once we add ' ' between tokens then we should be golden. 
this functionality maybe should live in the commandline formatter though.
*/
void terminate_command(char line[]){
    
    size_t len = strlen(line);
    if(line[len - 1] == '\n'){
        if(line[len - 2] != ';' | line[len - 2] != '&'){
            line[len-1] = ';';
        }
    }
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

int fill_structs(char *token[], JOB *job_queue)
{
    int job_num = 0;
    int i = 0;
    int start = 0;

    while (token[i] != NULL)
    {
        if (strcmp(token[i], ";") == 0 | strcmp(token[i], "&") == 0)  //TODO not sure this is sound. Test it.
        {
            JOB j1;
            //= malloc(sizeof(JOB));
            build_job_struct(&j1, token, start, i-1, i);
            job_queue[job_num] = j1;
            job_num++;
            start = i+1;
        }      
        i++;
    }

    return job_num; //returning num of jobs
}

void build_job_struct(JOB *job, char *token[], int start, int end, int sep)
{
    int com_num = 0;
    int i = start;
    int last_sep = -1;

    while (token[i] != NULL && i <= end)
    {
        if (strcmp(token[i], "|") == 0 || strcmp(token[i], "<") == 0 || strcmp(token[i], ">") == 0)  //add functionality for | < > separators
        {
            Command *c1 = malloc(sizeof(Command));
            build_command_struct(c1, token, start, i-1, i, last_sep);
            last_sep = i;
            job->command_queue[com_num] = c1;  //why c1 and not *c1 like for *j1?
            com_num++;
            start = i+1;

        }
        else if (token[i+1] == NULL)  //not sure if still useful
        {
            Command *c1 = malloc(sizeof(Command));
            build_command_struct(c1, token, start, i, -1, last_sep);  //bug: if last command, points to last char.
            last_sep = -1;
            job->command_queue[com_num] = c1;
            com_num++;
            start = i+1;

        }
        else if (i == end)  //add functionality for | < > separators
        {
            Command *c1 = malloc(sizeof(Command));
            build_command_struct(c1, token, start, i, -1, last_sep);
            last_sep = i;
            job->command_queue[com_num] = c1;  //why c1 and not *c1 like for *j1?
            com_num++;
            start = i+1;

        }
        i++;
    }
    
    job->sep = sep;
    job->command_count = com_num;
    
    return;
}

void build_command_struct(Command *com, char *token[], int start, int end, int sep, int last_sep)
{
    com->first = start;
    com->last = end;
    com->out_sep = sep < 0 ? NULL : token[sep];
    com->in_sep = last_sep < 0 ? NULL : token[last_sep];
    
    return;
}

void print_jobs(JOB * queue, int num_jobs, char * token[]) 
{
    
    for (int i=0; i< num_jobs; i++)
    {
        printf("job %d: sep=\"%s\"\n", i+1, token[queue[i].sep]);
        for (int j=0; j<queue[i].command_count; j++)
        {

            printf("\t%d: ", j+1);

            for (int k=queue[i].command_queue[j]->first; k<=queue[i].command_queue[j]->last; k++)
            {
                printf("%s ", token[k]);
            }
            printf("\n");
        }
    }

    return;
}

void print_tokens(char *token[])
{
    int i=0;
    printf("tokens: ");
    while (token[i] != NULL)
    {
        printf("%s  ", token[i]);
        i++;
    }
    printf("\n");
}

void free_queue(JOB *queue, int job_count)
{
    for (int i=0; i<job_count; i++)
    {
        for (int j=0; j<queue[i].command_count; j++)
        {
            free(queue[i].command_queue[j]);
        }
        //free(queue[i]);
    }

    //printf("QUEUE FREED\n"); //removed for testing readability

    return;
}