all: comp build

comp: comp.o
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o comp comp.o

build: build.o CalcTest.o
	exec $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o build build.o CalcTest.o

