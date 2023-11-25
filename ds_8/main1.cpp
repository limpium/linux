#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(){

int pipeFD_1[2];
int pipeFD_2[2];

if(pipe(pipeFD_1) == -1){

	perror("pipe");
	exit(errno);
}

if(pipe(pipeFD_2) == -1){
	perror("pipe");
	exit(errno);
}


pid_t cpid_1 = fork();

if(cpid_1 == -1){
	perror("fork");
	exit(errno);
}

if(cpid_1 == 0){

	close(pipeFD_2[1]);
	close(pipeFD_1[0]);

	pid_t pid1 = getpid();
	std::cout<< "Child 1 s PID: " << pid1 << std::endl;

	int writtenBytes = write(pipeFD_1[1], &pid1, sizeof(pid_t));
	if(writtenBytes == -1){
		perror("write");
		exit(errno);
	}

	close(pipeFD_1[1]);

	pid_t pid1_new;
	int readBytes = read(pipeFD_2[0], &pid1_new, sizeof(pid_t));

	if(readBytes == -1){
		perror("read");
		exit(errno);
	}

	std::cout<< "Child 1 received PID from Child 2 = " << pid1_new << std::endl;

	close(pipeFD_2[0]);

} else if(cpid_1 > 0){

	pid_t cpid_2 = fork();

	if(cpid_2 == -1){
		perror("fork");
		exit(errno);
	}

	if(cpid_2 == 0){

		close(pipeFD_2[0]);
		close(pipeFD_1[1]);

		pid_t pid2 = getpid();
		std::cout<< "Child 2 s PID: " << pid2 << std::endl;

		int writtenBytes = write(pipeFD_2[1], &pid2, sizeof(pid_t));

		if(writtenBytes == -1){
			perror("write");
			exit(errno);
		}

		close(pipeFD_2[1]);

		pid_t pid2_new;
		int readBytes = read(pipeFD_1[0], &pid2_new, sizeof(pid_t));

		if(readBytes == -1){
			
			perror("read");
			exit(errno);
		}

		close(pipeFD_1[0]);

		std::cout<< "Child 2 received PID from Child 1 = " << pid2_new << std::endl;

	}
}


return 0;
}




