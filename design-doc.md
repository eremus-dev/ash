## Design Document for Shell Architecture and Project Modules:


#### Module: Command Line Parser.
##### Function: Parses commandline and returns queue of jobs.

#### Module: Shell Utility:
##### Function: Performs specified utility funtions.
 - cd 
 - pwd
 - Redirection stdin
 - Redirection stdout
 

#### Module: Main Program
##### Function: calls parser, get job queue, performs redirection, forks and execs jobs.
 - Calls parser
 - Calls utility
 - Execute
<<<<<<< HEAD
=======

>>>>>>> 95a7b43641d65e131fa0dbf9344cf487cd49fdee
