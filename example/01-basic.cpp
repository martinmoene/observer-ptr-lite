#include "nonstd/observer_ptr.h"

using namespace nonstd;

void use( observer_ptr<int> p )
{
    assert( *p == 42 );
}

int main()
{
    int a = 42;
    observer_ptr<int> p( &a );
    use( p );
}

#if 0
cl -EHsc -I../include 01-basic.cpp && 01-basic.exe
g++ -std=c++03 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
#endif
