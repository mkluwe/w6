#include "writeWords.h"

#include <fstream>

void writeWords( const char *filename, const std::vector< Word > &words ) {
    auto file = std::ofstream( filename, std::ios::binary );
    for ( auto &w : words ) {
        file.write( w.data(), std::tuple_size_v< Word > );
        file << '\n';
    }
}