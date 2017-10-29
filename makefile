all: library compile
library: LinkedList.cpp
	cl /c LinkedList.cpp
	lib LinkedList.obj

compile: test.cpp LinkedList.lib
	cl /c test.cpp
	link test.obj LinkedList.lib

run: test.exe
	test

clean:
	del *.obj *.exe *.lib
