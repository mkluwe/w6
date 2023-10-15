#pragma once

#include <array>
#include <ostream>

using Word = std::array< char, 6 >;

std::ostream &operator<<( std::ostream &os, const Word &w );