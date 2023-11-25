#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout<<"wrong arg"<<std::endl;
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(errno);
    }

    pid_t cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(errno);
    }

    if (cpid == 0) {  
        close(pipefd[0]);
        
        
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if(cpid > 0) { 
        close(pipefd[1]); 
        
        
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        if (execvp(argv[2], &argv[2]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
