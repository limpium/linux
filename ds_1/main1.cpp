#include <iostream>

int main(int argc, char** argv){
 int array[3];

 array[0] = std::stoi(argv[1]);
 array[1] = std::stoi(argv[2]);
 array[2] = std::stoi(argv[3]);

 int max = array[0];
 int min = array[0];

if(array[1] > max){
  max = array[1];
} else if (array[1] < min){
 min = array[1];
}

if(array[2] > max){
 max = array[2];
} else if(array[2] < min){
 min = array[2];
}

std::cout<< min << " " << max <<std:: endl;



return 0;
}
