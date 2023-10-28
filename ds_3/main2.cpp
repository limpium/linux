#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <errno.h>

//constexpr int buffer_size = 4096;

int main(){
char  buffer_size[1024];
char source_file[50];
char destination_file[50];
std::cout<< "Enter the name of the source file:"; 
std::cin >> source_file;

int fd = open(source_file, O_CREAT | O_RDONLY | O_TRUNC); 

if(fd == -1)
{ 
std::cerr << "Cannot open file: " << source_file << std::endl;
exit(EXIT_FAILURE);
}

std::cout<< "Enter the name of the destination file:";
  std::cin >> destination_file;

int ffd = open(destination_file, O_CREAT | O_RDWR | O_TRUNC);

if(ffd == -1)
{
 std::cerr << "Cannot open file: " << destination_file << std::endl;
 exit(EXIT_FAILURE);
 }

off_t source_off;
off_t destination_off;

std::cout<< "Enter the initial offset in the source file (in bytes): " ;
std::cin>> source_off;

std::cout<< "Enter the initial offset in the destination file (in bytes): " ;
std::cin>> destination_off;

int bytes_;

std::cout<< "Enter the number of bytes to copy:";
std::cin>> bytes_;

if(lseek(fd, source_off, SEEK_SET) < 0){

	std::perror("lseek error");
	exit(errno);
}

if(lseek(ffd, destination_off, SEEK_SET) < 0){
	
	std::perror("lseek error");
	exit(errno);
}

int bytes_read;
int bytes_written;

while(bytes_ >= 1){
int b_read;
if(bytes_ >= sizeof( buffer_size))
b_read = 1024;

if(sizeof(buffer_size) > bytes_)
b_read = bytes_;

bytes_read = read(fd, buffer_size, b_read);
	
	if(bytes_read == -1)
	{
	std::cerr << "Cannot read" << std::endl;
	exit(EXIT_FAILURE);
}
       if(bytes_read == 0)
{break;}
bytes_written = read(ffd, buffer_size, bytes_read);

	if(bytes_written == -1)
	{
	std::cerr << "write" << std::endl;
	exit(1);
	}

bytes_ = bytes_ - bytes_read;
}

close(fd);
close(ffd);

std::cout<< "Successfully copied " << bytes_ << "bytes from the source file to the destination file." <<std:: endl;
return 0;
}


