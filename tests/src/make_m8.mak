
conlibs = kernel32.lib

DIFF = sdiff
PRE =

.SUFFIXES: .cpp

.cpp.obj:
		cl -c -W3 -Ox  -EHsc $*.cpp

everything:    	comp.exe build.exe 

comp_obj = comp.obj

comp.exe:      	$(comp_obj)
		link -Out:$@ $(conlibs) $(comp_obj)

build_obj = build.obj CalcTest.obj

build.exe:     	$(build_obj)
		link -Out:$@ $(conlibs) $(build_obj)

comp.obj:      	comp.cpp

build.obj:     	build.cpp CalcTest.h

CalcTest.obj:	CalcTest.cpp CalcTest.h

comp.txx:      	comp.exe
		$(PRE)comp > comp.txx
		$(DIFF) comp.txt comp.txx

build.txx:     	build.exe
		$(PRE)build > build.txx
		$(DIFF) build.txt build.txx

