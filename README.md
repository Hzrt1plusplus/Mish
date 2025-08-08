# Mish
Mish - My Interactive SHell 
Bare 6o lines of C++ of build your own shell.

# This porject is for who? 
This project is for people who have 0 understanding about systemcall in LINUX/UNIX systems and how to use them. 

# Intro 
Had you thought how shell works? Actually the magic behind shells are very simple. We have to fork() a new process and then call appropirate exec function from exec functions family(execl, execv, execlp, execvp, execle, execve).

``` C++
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
```

### iostream - for i/o (we are going to use stdin/stdout) 
### vector - for storing argument list as vector of strings 
### sstream - for std::stringstream class
### unistd.h - this is the header which contains main system functions fork() and exec functions 
### syd/wait.h and sys/types.h - for type pid_t and function wait() 

# Getting user input 

``` C++
std::string buffer;
bool running = true;
while(running)
{
  std::cout << "mish> ";
  getline(std::cin,buffer);
  std::vector<std::string> result = parse_input(buffer);
  if (result[0] == "exit" || result[0] == "logout") break;
  run_command(result);
}
```
for now running can be replaced with true but it is for small cases. In future when we want to break loop after getting error in
some function, it is necessary to pass running as param. it is what it looks like: 

### mish> 



