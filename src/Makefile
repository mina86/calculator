##
## Makefile
## $Id: Makefile,v 1.5 2008/05/27 18:11:15 mina86 Exp $
##

LDFLAGS		+= -lm

OBJS		:= $(addsuffix .o,$(basename $(wildcard *.cpp))) parser.o

all: main

objs: $(OBJS)


parser.o: parser.cpp

parser.cpp: parser.hpp

parser.hpp: parser.y
	exec bison parser.y

%.o: %.cpp $(wildcard *.hpp) parser.hpp
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

main: $(OBJS)
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ *.o


doc:
	exec rm -rf -- ../doc/html
	exec doxygen

clean:
	exec rm -rf -- *.o main parser.cpp parser.hpp *.hh parser.output

.PHONY: all clean doc FORCE
