#include <algorithm>
#include <optional>
#include <regex>
#include <string>

#include "getScoreFn.h"
#include "guess.h"
#include "readWords.h"
#include "usage.h"
#include "writeWords.h"

std::optional< char > getWordLength( const std::string &filename ) {
    static const std::regex r( R"(.*(\d)\.txt)" );
    std::smatch m;
    if ( std::regex_match( filename, m, r ) ) {
        return *m[ 1 ].first;
    }
    return std::nullopt;
}

template < size_t N >
void guessWord( const char *filename ) {
    auto words = readWords< N >( filename );
    auto score = getScoreFn( words );
    std::sort( words.begin(), words.end(),
               [ = ]( const Word< N > &a, const Word< N > &b ) {
                   return score( a ) < score( b );
               } );
    guess( words );
    writeWords( filename, words );
}

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        return usage();
    }
    auto wordLength = getWordLength( argv[ 1 ] );
    if ( !wordLength.has_value() ) {
        return usage();
    }
    switch ( *wordLength ) {
    case '4':
        guessWord< 4u >( argv[ 1 ] );
        break;
    case '5':
        guessWord< 5u >( argv[ 1 ] );
        break;
    case '6':
        guessWord< 6u >( argv[ 1 ] );
        break;
    default:
        break;
    }
}