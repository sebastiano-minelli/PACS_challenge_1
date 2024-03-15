CXX      ?= g++
CXXFLAGS ?= -std=c++20
#CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../../../../../../pacs-examples/Examples/include

#LDFLAGS ?= -L../../../../../../pacs-examples/Examples/lib
#LIBS  ?= -lmuparser

EXEC = main
OBJECT = main.cpp
COMP = main.o

.PHONY = clean distclean

EXECUTE: COMPILE
	$(CXX) $(CXXFLAGS) $(COMP) -o $(EXEC)
	
COMPILE:
	$(CXX) $(CXXFLAGS) $(OBJECT) -c $(COMP)
	
clean:
	$(RM) *.o
	
distclean: clean
	$(RM) *~
