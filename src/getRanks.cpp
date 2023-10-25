#include <algorithm>

#include "getRanks.h"

namespace {
struct R {
    unsigned index;
    unsigned count;
};
} // namespace

std::array< unsigned, 256 >
getRanks( const std::array< unsigned, 256 > &count ) {
    std::array< R, 256 > values;
    for ( unsigned i = 0; i < 256; ++i ) {
        values[ i ] = { i, count[ i ] };
    }
    std::sort( values.begin(), values.end(),
               []( R a, R b ) { return a.count > b.count; } );
    std::array< unsigned, 256 > ranks{};
    for ( unsigned i = 0; i < 29; ++i ) {
        ranks[ values[ i ].index ] = i + 1;
    }
    return ranks;
}