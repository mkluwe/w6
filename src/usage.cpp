#include <cstdlib>
#include <iostream>

#include "usage.h"

int usage() {
    std::cout << "Usage:\n\n    w6 {WORDS}" << std::endl;
    return EXIT_FAILURE;
}