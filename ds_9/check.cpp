#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char** argv){
const char *file_path = "/shared_memory";
const int file_size = 1000;

if(argc != 2){
	std::cout<< "Wrong arg"<< std::endl;
	exit(EXIT_FAILURE);
}

int N = std::stoi(argv[1]);

int shm_fd = shm_open(file_path, O_RDWR | O_CREAT, 0666);
if(shm_fd == -1){
          perror("Error opening shared memory");
          exit(EXIT_FAILURE);
   }
 
int *p_data = static_cast<int*>(mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
  
if(p_data == MAP_FAILED){
          perror("Error mapping the shared memory into the address space");
          exit(EXIT_FAILURE);
}

if(N < file_size && p_data[N] == 0){

std::cout<<"Yes"<<std::endl;
}
else 
std::cout<<"No"<<std::endl;

if(munmap(p_data, file_size) == -1){
	perror("Error unmapping the shared memory");
	exit(EXIT_FAILURE);
}

if(close(shm_fd) == -1){
	perror("Error closing the shared memory");
	exit(EXIT_FAILURE);
}
return 0;
}
