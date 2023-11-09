#pragma once

#include <vector>

#include "types.h"

template < size_t N >
void writeWords( const char *filename, std::vector< Word< N > > &words ) {
    std::sort( words.begin(), words.end() );
    auto file = std::ofstream( filename, std::ios::binary );
    for ( auto &w : words ) {
        file.write( w.data(), N );
        file << '\n';
    }
}