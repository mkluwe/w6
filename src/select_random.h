#pragma once

#include <random>

const auto &select_random( const auto &v ) {
    std::uniform_int_distribution<> dis( 0, v.size() - 1 );
    static std::random_device rd;
    static std::mt19937 gen( rd() );
    return v[ dis( gen ) ];
}