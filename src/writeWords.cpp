#include "writeWords.h"

#include <algorithm>
#include <fstream>

void writeWords( const char *filename, std::vector< Word > &words ) {
    std::sort( words.begin(), words.end() );
    auto file = std::ofstream( filename, std::ios::binary );
    for ( auto &w : words ) {
        file.write( w.data(), std::tuple_size_v< Word > );
        file << '\n';
    }
}