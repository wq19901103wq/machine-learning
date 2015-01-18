CXX=g++
CC=g++
CXXFLAGS=-g -O3 -Wall
LDFLAGS=-g -O3
INCLUDE=-I/usr/include/Eigen 


test: test.cpp matrix.o ${ADDLD}
	${CXX} -o test test.cpp matrix.o ${INCLUDE} ${LDFLAGS} 

matrix.o: ./matrix/matrix.cpp
	${CXX} -c -o matrix.o ./matrix/matrix.cpp ${INCLUDE} ${LDFLAGS}

clean:
	rm -f test 
	rm *~
