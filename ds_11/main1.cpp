#include <iostream>
#include <vector>
#include <pthread.h>

class Number {
public:
  int x = 0;
};

pthread_mutex_t mutex;

void* example(void* arg) {
  Number* num = (Number*)arg;
  for (int i = 0; i < 10000; ++i) {
    pthread_mutex_lock(&mutex);
    num->x++;
    pthread_mutex_unlock(&mutex);
  }
  return nullptr;
}

int main(int argc, char** argv) {
  Number* num = new Number();
  num->x = 2;
  
  pthread_mutex_init(&mutex, nullptr);
  std::vector<pthread_t> tids(20);

  for (int i = 0; i < 20; ++i){
   if(pthread_create(&tids[i], NULL, example, (void*)num) != 0){
	std::cerr<< "Cannot create";
	exit(EXIT_FAILURE); 
  }

}

  for (int i = 0; i < 20; ++i) {
   if(pthread_join(tids[i], NULL) != 0){
	std::cerr<< "Cannot join";
	exit(EXIT_FAILURE);
 }
  }

  std::cout << num->x << std::endl;
  pthread_mutex_destroy(&mutex);
  delete num;

  return 0;
}
