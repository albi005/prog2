#
# Egyszerű makefile (GNU)
# Feltételezi, hogy minden forrás fugg minden headertől
#
CCX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wdeprecated -pedantic -DMEMTRACE -g -O0 -U _FORTIFY_SOURCE
TARGET  := genetika_teszt

HEADERS := $(wildcard *.h) $(wildcard *.hpp)
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)


$(TARGET): $(OBJECTS)
	$(CCX) $^ -g -o $@ -ldl
	
%.o: %.c $(HEADERS)
	$(CCX) $(CXXFLAGS) -c $<
	
clean:
	rm -fr $(OBJECTS) genetika_teszt
