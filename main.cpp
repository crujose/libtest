#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "hello.hpp"

void* initlib(const char* libpath)
{
    void* handle = dlopen(libpath, RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return NULL;
    }

    void (*initfn)(void) = (void(*)(void))dlsym(handle, "init");
    if (!initfn) {
        std::cerr << dlerror() << std::endl;
        return NULL;
    }

    initfn();

    return handle;
}

void unloadlib(void* handle)
{
    if (dlclose(handle)) {
        std::cerr << dlerror() << std::endl;
    }
}

void printUsage(void)
{
    long rss = 0L;
    char buf[1024];
    FILE* fp = NULL;
    if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL ) {
        perror("Could not open /proc/self/statm");
        return;
    }
    size_t size, resident, share, text, lib, data, dt;
    if (fscanf(fp, "%zu %zu %zu %zu %zu %zu %zu", &size, &resident, &share, &text, &lib, &data, &dt) != 7) {
        std::cerr << "Did not read expected output" << std::endl;
    }
    fclose( fp );

    const size_t pageSize = (size_t)sysconf( _SC_PAGESIZE);
    std::cout << "size      =" << pageSize * size << std::endl;
    std::cout << "resident  =" << pageSize * resident << std::endl;
    std::cout << "share     =" << pageSize * share << std::endl;
    std::cout << "text      =" << pageSize * text << std::endl;
    std::cout << "lib       =" << pageSize * lib << std::endl;
    std::cout << "data      =" << pageSize * data << std::endl;
    std::cout << "dirty     =" << pageSize * dt << std::endl;
}


int main(void)
{
	std::cout << "Hello world " << getpid() << std::endl;
	hello(4);

	printUsage();

	void* handle = initlib("./libdyn.so");

	printUsage();

	unloadlib(handle);

	printUsage();

	std::cout << "exit" << std::endl;

	return 0;
}
