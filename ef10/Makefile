#
# Makefile a CppMonoton feladathoz
#

CXXFLAGS = -g -Wall 

OBJS = monoton_test.o

monoton_test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -g -O0

#-------------
monoton_test.o: monoton_test.cpp fancy_iterators.hpp monoton.hpp gtest_lite.h

clean:
	rm -f *.o *.log monoton_test

