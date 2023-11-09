#pragma once

#include <array>
#include <ostream>

template < size_t N >
using Word = std::array< char, N >;

template < size_t N >
std::ostream &operator<<( std::ostream &os, const Word< N > &w );