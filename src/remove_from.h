#pragma once

#include <algorithm>

void remove_from( auto &v, const auto &elem ) {
    auto p = std::find( v.begin(), v.end(), elem );
    if ( p != v.end() ) {
        v.erase( p );
    }
}