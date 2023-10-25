#include "readWords.h"

#include <algorithm>
#include <fstream>

namespace {
void toupper( Word &w ) {
    for ( char &c : w ) {
        switch ( c ) {
        case '\xe4':
            c = '\xc4';
            break;
        case '\xf6':
            c = '\xd6';
            break;
        case '\xfc':
            c = '\xdc';
            break;
        case '\xdf':
            break;
        default:
            if ( c >= '\x61' && c <= '\x7a' ) {
                c -= 32;
            }
            break;
        }
    }
}

bool isExpectedWord( const Word &w ) {
    for ( auto &c : w ) {
        if ( c >= 'A' && c <= 'Z' ) {
            continue;
        }
        if ( c == '\xc4' || c == '\xd6' || c == '\xdc' || c == '\xdf' ) {
            continue;
        }
        return false;
    }
    return true;
}
} // namespace

std::vector< Word > readWords( const char *filename ) {
    auto file = std::ifstream( filename, std::ios::binary );
    std::vector< Word > words;
    while ( file.good() ) {
        words.push_back( {} );
        file.read( words.back().data(), std::tuple_size_v< Word > );
        file.ignore( 1 );
    }
    for ( Word &w : words ) {
        toupper( w );
    }
    while ( !isExpectedWord(words.back()) ) {
        words.pop_back();
    }
    std::sort( words.begin(), words.end() );
    words.erase( std::unique( words.begin(), words.end() ), words.end() );
    return words;
}