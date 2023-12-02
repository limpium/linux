CXX=g++

run: init set check destroy
	./init
	./set
	./check $(N)
	./destroy

init: init.cpp
	$(CXX) init.cpp -o init 

destroy: destroy.cpp
	$(CXX) destroy.cpp -o destroy

set: set.cpp
	$(CXX) set.cpp -o set

check: check.cpp
	$(CXX) check.cpp -o check 

clean:
	 rm -f init set check destroy
