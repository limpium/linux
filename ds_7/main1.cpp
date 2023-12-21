#include <iostream>
#include <signal.h>
#include <unistd.h>


int count = 0;
void handleAbort(int signum){
if(signum == SIGUSR1){
return ;
}
if(signum == SIGUSR2){

count++;
}

if(signum == SIGINT){
std::cout<< count;
exit(0);
}

//exit(1);


}
int main(){

struct sigaction act = {};
act.sa_handler = SIG_IGN;

if(sigaction(SIGUSR2, &act, nullptr) == -1){ 
 perror("sigaction");
 exit(errno);
}
if(sigaction(SIGUSR2, &act, nullptr) == -1){

perror("sigaction");
exit(errno);
}

if(sigaction(SIGINT, &act, nullptr) == -1){

perror("sigaction");
exit(errno);
}

while(true){
std::cout<< "I am still alive/n";
sleep(5);
}

return 0;
}
