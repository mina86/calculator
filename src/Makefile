LDFLAGS		+= -lm

OBJS		:= $(addsuffix .o,$(basename $(wildcard *.cpp))) parser.o

all: calc

objs: $(OBJS)


parser.o: parser.cpp

parser.cpp: parser.hpp

parser.hpp: parser.y
	exec bison parser.y

%.o: %.cpp $(wildcard *.hpp) parser.hpp
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

calc: $(OBJS)
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ *.o


doc::
	exec rm -rf -- ../doc/html
	exec doxygen

clean::
	exec rm -rf -- *.o calc parser.cpp parser.hpp *.hh parser.output
