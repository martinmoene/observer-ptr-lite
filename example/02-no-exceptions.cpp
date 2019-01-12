#include "nonstd/observer_ptr.hpp"
#include <iostream>

using namespace nonstd;

int main()
{
    observer_ptr<int> ptr;

    std::cout <<
        "nsop_CONFIG_NO_EXCEPTIONS: '" << nsop_CONFIG_NO_EXCEPTIONS << "'\n" <<
        "nsop_noexcept: '" nsop_noexcept << "'\n";
}

// cl -nologo -I../include 02-no-exceptions.cpp && 02-no-exceptions
// g++ -Wall -fno-exceptions -I../include -o 02-no-exceptions 02-no-exceptions.cpp && 02-no-exceptions
