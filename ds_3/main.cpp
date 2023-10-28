#include "ComplexNum.h"
#include <vector>
#include <algorithm>

int main(){
  std::vector<ComplexNumber> complex;

   complex.push_back(ComplexNumber(16, -4));
   complex.push_back(ComplexNumber(9));  
   complex.push_back(ComplexNumber(89, 90)); 
   complex.push_back(ComplexNumber(79, 4));
   complex.push_back(ComplexNumber(89, 90));
   complex.push_back(ComplexNumber(35));

	std::sort(complex.begin(), complex.end());

 for(int i = 0; i < complex.size(); ++i){
	std::cout<< complex[i];
}


return 0;
}
