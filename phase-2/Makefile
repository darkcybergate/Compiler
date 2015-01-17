objects = Parent.o bison.tab.o lex.yy.o 
CXX = g++
CXXFLAGS = -g -Wno-deprecated -I .

main:	$(objects) 
	$(CXX) $(CXXFLAGS) -o astbuilder $(objects)

bison.tab.hpp bison.tab.cpp:	bison.ypp
	bison -d -v bison.ypp

lex.yy.c : flex.l bison.tab.hpp
	flex flex.l



bison.tab.o:	bison.tab.cpp 
Parent.o:	Parent.cc Parent.hh

lex.yy.o:	bison.tab.hpp lex.yy.c
	$(CXX)  $(CXXFLAGS) -c -lfl bison.tab.cpp lex.yy.c


clean:
	-rm -f demo $(objects)
	-rm -f bison.tab.cpp bison.tab.hpp
	-rm -f bison.output
	-rm -f lex.yy.c
	-rm -f astbuilder