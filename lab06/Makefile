#
# Makefile pelda a bicikli feladat (6. labor) megoldasanak forditasara 
# gnumake valtozat
# 	Linuxokon es ural2-n is elerheto
#
PROG = bicikli_teszt  # a program neve (ezt allitjuk elo)
PROG_O = bicikli_teszt0.o  # program object fajljai 
PROG_H = bicikli.h    # program header fajljai
PROG_L =              # program libjei

MTRACE_O = memtrace.o # memtrace object fajl
MTRACE_H = memtrace.h # memtrace header fajlja

CXX = g++   # a C fordito neve
#CXX = clang++ # clang-ot (llvm) is erdemes kiprobalni
CXXFLAGS = -pedantic -Wall -O0# kapcsolok: legyen bobeszedu es pedans
CXXFLAGS += -g -DMEMTRACE -U _FORTIFY_SOURCE# es debug info is
LDFLAGS = -g -DMEMTRACE -O0 -U _FORTIFY_SOURCE # debug a linkelesnel 

# osszes object, osszes header osszes lib
OBJS = $(PROG_O) $(MTRACE_O)
HEADS = $(PROG_H) $(MTRACE_H)
LIBS = $(PROG_L) 

# alapertelmezett cel: program
.PHONY: all
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -DMEMTRACE -g -O0 -U _FORTIFY_SOURCE

# feltetelezzuk, hogy az osszes obj fugg az osszes headertol
$(OBJS): $(HEADS)

# takaritas igeny szerint
.PHONY: clean
clean:
	rm -f $(OBJS) $(PROG)

