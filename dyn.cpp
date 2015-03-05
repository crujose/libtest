#include <iostream>
#include "dyn.hpp"

using namespace std;

class Dyno {
    char m_buf[1024 * 1024 * 512];
public:
    Dyno()
    {
        cout << "dyno!" << endl;
        cout << (void*)m_buf << " has " << sizeof(m_buf) << " bytes." << endl;
    }
    ~Dyno()
    {
        cout << "~dyno" << endl;
    }
};

static Dyno sDyno;


extern "C" {

void init(void)
{
    cout << "dyn initialized" << endl;
}

}
