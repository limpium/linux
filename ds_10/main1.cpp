#include <fcntl.h>
#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <vector>

class Thread_ {
private:
  pthread_mutex_t *mutex;
  int thread_num_;
  std::string op_;
  int num1_, num2_;

public:
  Thread_() = default;
  Thread_(int thread_num, const std::string &op, int num1, int num2)
      : thread_num_(thread_num), op_(op), num1_(num1), num2_(num2) {

    mutex = new pthread_mutex_t();
    pthread_mutex_init(mutex, nullptr);
  }

  void result() {

    int res = 0;
    pthread_mutex_lock(mutex);

    if (op_ == "s") {
      res = num1_ + num2_;
    }
    else if (op_ == "m") {
      res = num1_ * num2_;
    }
    else if (op_ == "ss") {
      res = num1_ * num1_ + num2_ * num2_;
    }

    std::string file = "out_" + std::to_string(thread_num_);
    int fd = open(file.c_str(), O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1) {
      std::perror("open");
      exit(EXIT_FAILURE);
    }
    std::string str = std::to_string(num1_) + " " + op_ + " " + std::to_string(num2_) + " = " + std::to_string(res);

    int writtenBytes = write(fd, str.c_str(), str.size());
    if (writtenBytes == -1) {
      std::perror("write");
      exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
      std::perror("close");
      exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(mutex);
  }

  ~Thread_() {
    pthread_mutex_destroy(mutex);
    delete mutex;
  }
};

void *p_result(void *arg) {
  Thread_ *threadData = static_cast<Thread_ *>(arg);
  threadData -> result();
  delete threadData;
  return nullptr;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<pthread_t> tids(N);


  for (int i = 0; i < N; ++i) {
    std::string op;
    int num1, num2;

    std::cin >> num1 >> num2 >> op;
    Thread_ *threadData = new Thread_(i + 1, op, num1, num2);

    pthread_create(&tids[i], nullptr, p_result, static_cast<void *>(threadData));
  }

  for (int i = 0; i < N; ++i) {
    pthread_join(tids[i], nullptr);
  }



  return 0;
}
