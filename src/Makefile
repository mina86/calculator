##
## Makefile
## $Id: Makefile,v 1.3 2008/02/29 20:47:28 mina86 Exp $
##

LDFLAGS		+= -lm

HPP_FILES	:= $(wildcard *.hpp) parser.hpp
OBJ_FILES	 = $(addsuffix .o,$(basename $(wildcard *.cpp)))


all: main

objs: $(OBJ_FILES) parser.o


parser.o: parser.cpp

parser.cpp: parser.hpp

parser.hpp: parser.y
	exec bison parser.y

%.o: %.cpp $(HPP_FILES)
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

main: objs
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ_FILES)


doc:
	exec rm -rf -- ../doc/html
	exec doxygen

clean:
	exec rm -rf -- *.o main parser.cpp parser.hpp *.hh parser.output

.PHONY: all clean doc FORCE
