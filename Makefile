CXX=g++
CC=g++
CXXFLAGS=-g -O3 -Wall
LDFLAGS=-g -O3 
INCLUDE=-I/usr/include/Eigen 

eigen: test.cpp ${ADDLD}
	${CXX} -o test test.cpp ${INCLUDE} ${LDFLAGS}

clean:
	rm -f test 
	rm *~
