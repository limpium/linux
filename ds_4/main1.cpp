#include <iostream>
#include <fcntl.h>
#include <vector>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc != 2){
		std::cout<< "Wrong arguments" << std::endl;
		exit(EXIT_FAILURE);
	}

int fd = open(argv[1], O_RDWR);

if(fd == -1){
	std::perror("open");
	exit(EXIT_FAILURE);
}
int count = 0;
ssize_t byte_to_read;
int buffer_s = 4096;
std::vector<char> buffer(buffer_s);
while((byte_to_read = read(fd, buffer.data(), buffer_s)) > 0){

for(int i = 0; i < byte_to_read; ++i){
	if(buffer[i] == '\n'){
	count++;
	}
}
}
if(byte_to_read == -1){
	std::perror("read");
	exit(EXIT_FAILURE);
}


std::cout<< count << std::endl;

int fd_n = open("output.txt", O_RDWR | O_CREAT | O_TRUNC,  0666);

if(fd_n == -1){
          std::perror("open");
          exit(EXIT_FAILURE);
}

lseek(fd, 0 , SEEK_SET);
ssize_t written_byte;
//ssize_t new_byte_to_read;
while((byte_to_read = read(fd, buffer.data(), buffer_s)) > 0){
for(int i = byte_to_read - 2; i > -1; i--){
     written_byte = write(fd_n, &buffer[i], 1);
}
	if(written_byte == -1){
		std::perror("write");
		exit(EXIT_FAILURE);
	}
}
if(byte_to_read == -1){
	std::perror("read");
	exit(EXIT_FAILURE);
}
if(close(fd) == -1){
         std::perror("close");
         exit(EXIT_FAILURE);
  }

if(close(fd_n) == -1){
	std::perror("close");
	exit(EXIT_FAILURE);
}

return 0;

}
