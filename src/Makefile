##
## Makefile
## $Id: Makefile,v 1.4 2008/02/29 20:51:36 mina86 Exp $
##

LDFLAGS		+= -lm

all: main

objs: $(addsuffix .o,$(basename $(wildcard *.cpp))) parser.o


parser.o: parser.cpp

parser.cpp: parser.hpp

parser.hpp: parser.y
	exec bison parser.y

%.o: %.cpp $(wildcard *.hpp) parser.hpp
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

main: objs
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ *.o


doc:
	exec rm -rf -- ../doc/html
	exec doxygen

clean:
	exec rm -rf -- *.o main parser.cpp parser.hpp *.hh parser.output

.PHONY: all clean doc FORCE
