CXXFLAGS+=-fPIC -g

all: main

libhello.so: hello.o
	$(CXX) $(CXXFLAGS) -shared -o libhello.so hello.o

libdyn.so: dyn.o
	$(CXX) $(CXXFLAGS) -shared -o libdyn.so dyn.o

main: main.o libhello.so libdyn.so
	$(CXX) main.o -lhello -ldl -L. -o main

.PHONY: clean
clean:
	@rm -f *.so *.o main
