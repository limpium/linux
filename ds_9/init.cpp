#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
  const char *file_path = "/shared_memory";
  const int file_size = 1000;

int shm_fd = shm_open(file_path, O_RDWR | O_CREAT, 0666);

if(shm_fd == -1){
 	perror("Error opening shared memory");
        exit(EXIT_FAILURE);
 }

if(ftruncate(shm_fd, file_size) == -1){
	perror("Error setting the size of shared memory");
	exit(EXIT_FAILURE);
}

int *p_data = static_cast<int*>(mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

if(p_data == MAP_FAILED){
	perror("Error mapping the shared memory into the address space");
	exit(EXIT_FAILURE);
}

for(int i = 0; i < file_size; ++i){
	p_data[i] = 0;
}

if(munmap(p_data, file_size) == -1){
	perror("Error unmapping the shared memory");
	exit(EXIT_FAILURE);
}

if(close(shm_fd) == -1){
	perror("Error closing shared memory");
	exit(EXIT_FAILURE);
}


return 0;
}
