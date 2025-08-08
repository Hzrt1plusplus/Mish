# Mish
Mish - My Interactive SHell 
Bare 6o lines of C++ of build your own shell.

# This porject is for who? 
This project is for people who have 0 understanding about systemcall in LINUX/UNIX systems and how to use them. 

# Intro 
Had you thought how shell works? Actually the magic behind shells are very simple. We have to fork() a new process and then call appropirate exec function from exec functions family(execl, execv, execlp, execvp, execle, execve).

``` C++
#include <unistd.h>
```
