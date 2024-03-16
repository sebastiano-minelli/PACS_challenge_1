CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O0 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../../../../pacs-examples/Examples/include/muparserx

#LDFLAGS ?= -L../../../../pacs-examples/Examples/lib
#LIBS  ?= -lmuparserx

EXEC = main
OBJECT = main.cpp
OBJECT2 = StepCoefficientArmijo.cpp
STATIC_LIB = ../../../../pacs-examples/Examples/lib/libmuparserx.a
COMP = main.o StepCoefficientArmijo.o

.PHONY = clean distclean

EXECUTE: COMPILE
	$(CXX) $(CXXFLAGS) $(COMP) $(STATIC_LIB) -o $(EXEC)
	
COMPILE: COMPILE2
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJECT) -c
COMPILE2:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJECT2) -c	
clean:
	$(RM) *.o
	
distclean: clean
	$(RM) *~
