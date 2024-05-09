CCX = g++
CXXFLAGS = -Wall -Wdeprecated -pedantic -DMEMTRACE -g -std=c++11

HEADERS := $(wildcard *.h) $(wildcard *.hpp)
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)

all: $(OBJECTS)
	$(CCX) $^ -g -ldl -O0
	
%.o: %.c $(HEADERS)
	$(CCX) $(CXXFLAGS) -c $<
	
clean:
	rm -rf $(OBJECTS) a.out
