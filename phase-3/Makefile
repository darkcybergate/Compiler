objects = Parent.o bison.tab.o lex.yy.o 
CXX = g++ 
CXXFLAGS = -std=c++11 -ggdb  `llvm-config --cppflags --libs core jit native` `llvm-config --ldflags`

main:	$(objects) 
	$(CXX) -o astbuilder $(objects) $(CXXFLAGS) 

bison.tab.hpp bison.tab.cpp:	bison.ypp
	bison -d -v bison.ypp

lex.yy.c : flex.l bison.tab.hpp
	flex flex.l



bison.tab.o:	bison.tab.cpp 
Parent.o:	Parent.cc Parent.hh

lex.yy.o:	bison.tab.hpp lex.yy.c
	$(CXX) -c -lfl bison.tab.cpp lex.yy.c $(CXXFLAGS)


clean:
	-rm -f demo $(objects)
	-rm -f bison.tab.cpp bison.tab.hpp
	-rm -f bison.output
	-rm -f lex.yy.c
	-rm -f astbuilder
