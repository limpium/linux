#include <iostream>
#include <fcntl.h>
#include <vector>
#include <cerrno>
#include <unistd.h>


int main(int argc, char** argv){

if(argc != 2)
{
	std::perror("wronh  arguments");
	exit(EXIT_FAILURE);
}

int fd = open(argv[1], O_RDWR, 0666);

if(fd == -1){
	std::perror("Cannot open file:");
	exit(EXIT_FAILURE);
}

int buffer_s = 4096;
std::vector<char> buffer(buffer_s); 

ssize_t bytes_to_read;
ssize_t written_b;

while((bytes_to_read = read(fd, buffer.data(), buffer_s)) > 0){
	
	written_b = write(1, buffer.data(), bytes_to_read);
	if(written_b == -1){
		std::perror("Cannot write in file:");
		exit(EXIT_FAILURE);
}
}

 if(bytes_to_read == -1){
                 
                 std::perror("Cannot read a file:");
		 exit(EXIT_FAILURE);
 }


	if(close(fd) == -1)
{
	std::perror("Cannot close");
	exit(EXIT_FAILURE);
}

return 0;
}
