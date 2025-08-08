# Mish
Mish - My Interactive SHell 
Bare 60 lines of C++ of build your own shell.

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

I had to add if (result[0] == "exit" || result[0] == "logout") break; line because system exec funtions actually can't understand
what is "exit" or "logout" command. The next step is parsing user input. 

# Parsing input 
``` C++
std::vector<std::string> parse_input(std::string& buffer)
{
    std::vector<std::string> commands;
    std::stringstream stream(buffer);
    std::string command;
    while(stream >> command)
        commands.push_back(command);
    return commands;
}
```

In this case using STL's stringstream is best choice. it will produce {"Hello","World!"} from "Hello World!". 

# Running commands
``` C++
void run_command(std::vector<std::string> coms)
{
    pid_t pid = fork();
    if (pid  == -1) 
    {
        std::cout << "Error while creating child process!\n";
        return;
    } 
    if (pid > 0)
    {
        wait(NULL);
    }
    else {
        size_t size_of_vector = coms.size();
        const char* args[size_of_vector + 1];
        for (int i=0; i < size_of_vector; i++)
            args[i] = coms.at(i).c_str();
        args[size_of_vector] = NULL;
        execvp(args[0], (char* const*)args);
        std::cerr << "Error: invalid command or syntax!\n";
        return;
    }

}
```
In funcution main() we run our program in parent process. And when user enter the command, we have to execute it as child process.
Because if we run it as parent, at some point command will end and it will terminate program after the job is done. But we want 
our terminal to run commands repeatedly. It is where fork() comes with solution. fork() will create a new process(child process).
return value of fork is pid_t which is simply an integer. 
if return value is 0, it means we succeed on creating a new child process. If the value is greater than zero, something like 234, 5678 ... it means there is already a child process running on it and as a result fork() returns the process
id of  parent process. otherwise(return value = -1) it means fork() failed to create a child process. 
For executing a command after creating child process we use exec commands. They vary for their parameter list but all of their 
target purpose is same - execute command. There is list of exec commands and their params: 
``` C++
int execvp (const char *file, char *const argv[]);
int execv (const char *path, char *const argv[]);

int execlp (const char *file, const char *arg,...
(char  *) NULL);
int execl (const char *path, const char *arg,...
(char  *) NULL);

int execvpe (const char *file, char *const argv[],char *const envp[]);
int execle (const char *path, const char *arg, ..., (char *) NULL, 
char * const envp[] );
```
### 1. execv and execvp
take a look at their param list. only different thing is file and path params. In linux, every shell command has its executable
file in /usr/bin folder. You can take a look in your own linux machine. You will see /usr/bin/echo, /usr/bin/ls and so on. They 
are actual executables that computer runs when we run echo or something. execv takes path variable which is something like 
"/usr/bin/echo" in order to run the command. but execvp takes only "echo" and runs it. second variable is an array of cstrings.
It is parameter list of command. For example for command ls -la it is {"ls","-la"}. Note , command name itself is included in this array and you have to push back NULL to the end of this array. For our project, i used execvp. because it is simpler than
other ones. 
``` C++
execvp(args[0],(char* const*)args);
```
This line takes first argument as filename and passes argument list after casting it to const char**.




