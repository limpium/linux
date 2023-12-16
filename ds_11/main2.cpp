#include <iostream>
#include <pthread.h>
#include <vector>

class BankAccount{
private:

pthread_mutex_t* mutex;
int balance_;

public:

BankAccount(int balance) :balance_(balance){
mutex = new pthread_mutex_t();
pthread_mutex_init(mutex, nullptr);
}

~BankAccount(){
pthread_mutex_destroy(mutex);
delete mutex; 
}

void debit(int amount){
  pthread_mutex_lock(mutex);
  balance_ -= amount;
  pthread_mutex_unlock(mutex);
}

void credit(int amount){
  pthread_mutex_lock(mutex);
  balance_ += amount;
  pthread_mutex_unlock(mutex);
}

int get_balance() const{
return balance_;
}

};

void* debit_func(void* arg){
 BankAccount* acc = static_cast<BankAccount*>(arg);
  for(int i = 0; i < 10; ++i){
	acc -> debit(1000);
}

return nullptr;
}

void* credit_func(void* arg)
{
BankAccount* acc = static_cast<BankAccount*>(arg);
  for(int i = 0; i < 10; ++i){
	acc -> credit(50);
}

return nullptr;
}

int main(){

BankAccount*  my_acc = new BankAccount(10000);

std::vector<pthread_t> tids(31);

for(int i = 0; i < 31; ++i){

		if(pthread_create(&tids[i], nullptr, credit_func, (void*)my_acc) != 0){
			std::cerr<< "Cannot create";
			exit(EXIT_FAILURE);
		}
  
		if(pthread_create(&tids[i], nullptr, debit_func, (void*)my_acc) != 0){
			std::cerr<< "Cannot create";
			exit(EXIT_FAILURE);
		}
   
}

for(int i = 0; i < 31; ++i){
if(pthread_join(tids[i], nullptr) != 0)
{
    std::cerr<< "Cannot join";
    exit(EXIT_FAILURE);
}

}

std::cout<< my_acc->get_balance()<<std::endl;
delete my_acc;
return 0;
}
