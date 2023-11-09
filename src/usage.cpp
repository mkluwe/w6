#include <cstdlib>
#include <iostream>

#include "usage.h"

int usage() {
    std::cout << "Usage:\n\n    w6 {WORDS}" << std::endl <<
        "(WORDS matching SOMESTRING[4-6].txt)" << std::endl;
    return EXIT_FAILURE;
}