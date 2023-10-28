#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv){

if(argc != 3){
	std::perror("wrong arguments");
	exit(EXIT_FAILURE);
}

int fd_to = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
if(fd_to == -1){
	std::perror("open");
	exit(EXIT_FAILURE);
}



int fd_from = open(argv[1], O_RDWR, 0666);
if(fd_from == -1){
	std::perror("open");
	exit(EXIT_FAILURE);
}

int buffer_s = 4096;
std::vector<char> buf(buffer_s);

ssize_t byte_to_read;
ssize_t bytes_written;

while((byte_to_read = read(fd_from, buf.data(), buffer_s)) > 0){
	bytes_written = write(fd_to, buf.data(), byte_to_read);
	if(bytes_written == -1){
		std::perror("write");
		exit(EXIT_FAILURE);
	}
}

if(byte_to_read == -1){
	std::perror("read");
	exit(EXIT_FAILURE);
}

if(close(fd_from) == -1 || close(fd_to) == -1){
	std::perror("close");
	exit(EXIT_FAILURE);
}

std:: cout << "The programm was completed successfully" << std::endl;
return 0;
} 
