
conlibs = kernel32.lib

DIFF = sdiff
PRE =

.SUFFIXES: .cpp

.cpp.obj:
		cl  /nologo /I $(BOOST_PATH) -c -W0 -Ox  -EHsc $*.cpp

everything:    	main.exe

calc_obj = main.obj environment.obj expression.obj function.obj user-function.obj exceptions.obj file-lexer.obj functions.obj parser.obj

main.exe:   	$(calc_obj)
		link -Out:$@ $(conlibs) $(calc_obj)

main.obj:       main.cpp config.hpp functions.hpp environment.hpp file-lexer.hpp math.hpp function.hpp exceptions.hpp expression.hpp user-function.hpp position.hh location.hh lexer.hpp parser.hpp stack.hh

environment.obj:  	environment.cpp environment.hpp function.hpp expression.hpp

expression.obj:    	expression.cpp expression.hpp math.hpp function.hpp

function.obj:   	function.cpp function.hpp expression.hpp

user-function.obj:   	user-function.cpp user-function.hpp config.hpp expression.hpp

exceptions.obj:   	exceptions.cpp exceptions.hpp

file-lexer.obj:  	file-lexer.cpp file-lexer.hpp math.hpp exceptions.hpp

functions.obj:   	functions.hpp functions.hpp math.hpp exceptions.hpp

parser.obj:     	parser.hpp parser.hpp math.hpp exceptions.hpp lexer.hpp

clean:
		del $(calc_obj)

