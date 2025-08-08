#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


std::vector<std::string> parse_input(std::string& buffer)
{
    std::vector<std::string> commands;
    std::stringstream stream(buffer);
    std::string command;
    while(stream >> command)
        commands.push_back(command);
    return commands;
}

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

int main()
{
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
    return EXIT_SUCCESS;
}
