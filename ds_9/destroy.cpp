#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main(){
 
  const char *file_path = "/shared_memory";
  const int file_size = 1000;

int shm_fd =shm_open(file_path, O_RDWR | O_CREAT, 0666);

if(shm_fd == -1){
	perror("Error opening shared memory");
	exit(EXIT_FAILURE);
}

if(shm_unlink(file_path) == -1){
	perror("Error unlinked shared memmory");
	exit(EXIT_FAILURE);
}

if(close(shm_fd) == -1){
        perror("Error closing shared memmory");
        exit(EXIT_FAILURE);
}



return 0;
}
