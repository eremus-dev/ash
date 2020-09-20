/*
Header file for the shell utilties. 
Functions to implement:
    change prompt
    cd
    exit
*/
#ifndef UTILITIES_H
#define UTILITIES_H

// function to change the current prompt string.
void change_prompt(char * new_string);

// function to change the current working directory.
void change_pwd(char * path);

// Closes all the shells associated resources and exits.
void exit();

#endif