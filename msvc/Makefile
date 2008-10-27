all: update

update::
	exec $(MAKE) -C ../src parser.hpp
	exec cp -- ../src/parser.cpp ../src/parser.hpp ../src/location.hh ../src/position.hh ../src/stack.hh .
