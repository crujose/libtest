CXXFLAGS+=-fPIC

all: main

libhello.so: hello.o
	$(CXX) $(CXXFLAGS) -shared -o libhello.so hello.o

main: main.o libhello.so
	$(CXX) main.o -lhello -L. -o main

.PHONY: clean
clean:
	@rm -f *.so *.o
