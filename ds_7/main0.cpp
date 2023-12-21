#include <iostream>
#include <signal.h>
#include <unistd.h>


void handleAbort(int signum){
std::cout<< "signal recieved" << std::endl;
exit(1);
}

int main(int argc, char** argv){

if(argc != 3){

	std::cout<< "Wrong args" <<std:: endl;
	return 1;
}

//num, PID

int sig_num = std::stoi(argv[1]);
int pid_ = std::stoi(argv[2]);

if(kill(pid_, sig_num) == -1){
	std::perror("Error sending signal");
	exit(EXIT_FAILURE);
}
std::cout<< "Signal" << sig_num;
return 0;
}
