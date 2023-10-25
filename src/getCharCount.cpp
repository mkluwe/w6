#include "getCharCount.h"

std::array< unsigned, 256 > getCharCount( const std::vector< Word > &words ) {
    std::array< unsigned, 256 > count{};
    for ( auto &w : words ) {
        for ( auto c : w ) {
            count[ reinterpret_cast< unsigned char & >( c ) ]++;
        }
    }
    return count;
}