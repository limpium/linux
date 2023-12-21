#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(){

pid_t pid = fork();

if(pid == -1){
	perror("fork");
	exit(errno);
}

if(pid == 0){
//sleep(4);
if(kill(getpid(), SIGTERM) == 0){
	std::cout<<"Child killed parent"<<std::endl;
}
else{
	std::cerr<< "Error";
}

}
else{
int status;
pid_t child = wait(&status);

if(child == -1){
std::cerr<< "wait";
exit(EXIT_FAILURE);

}
std::cout<<"Parent process";

}
return 0;
}

