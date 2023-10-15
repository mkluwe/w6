#include <iostream>
#include <regex>
#include <set>
#include <string>

#include "guess.h"
#include "remove_from.h"
#include "select_random.h"

const auto N = std::tuple_size_v< Word >;

std::ostream &operator<<( std::ostream &os, const Word &w ) {
    for ( unsigned i = 0; i < w.size(); ++i ) {
        switch ( w[ i ] ) {
        case '\xc4':
            os << "Ä";
            break;
        case '\xd6':
            os << "Ö";
            break;
        case '\xdc':
            os << "Ü";
            break;
        case '\xdf':
            os << "ß";
            break;
        default:
            os << w[ i ];
        }
    }
    return os;
}

void filter( std::vector< Word > &words, const std::string &mask,
             std::vector< bool > &correct, const Word &current ) {
    for ( unsigned i = 0; i < N; ++i ) {
        if ( mask[ i ] == 'x' && !correct[ i ] ) {
            correct[ i ] = true;
            erase_if( words,
                      [ & ]( Word w ) { return w[ i ] != current[ i ]; } );
        }
    }
    std::set< char > must_contain;
    for ( unsigned i = 0; i < N; ++i ) {
        if ( mask[ i ] == 'o' ) {
            must_contain.insert( current[ i ] );
            erase_if( words,
                      [ & ]( Word w ) { return w[ i ] == current[ i ]; } );
            erase_if( words, [ & ]( Word w ) {
                for ( unsigned j = 0; j < N; ++j ) {
                    if ( i != j && w[ j ] == current[ i ] && !correct[ i ] ) {
                        return false;
                    }
                }
                return true;
            } );
        }
    }
    for ( unsigned i = 0; i < N; ++i ) {
        if ( mask[ i ] == '.' ) {
            if ( must_contain.contains( current[ i ] ) ) {
                erase_if( words,
                          [ & ]( Word w ) { return w[ i ] == current[ i ]; } );
            } else {
                erase_if( words, [ & ]( Word w ) {
                    for ( unsigned j = 0; j < N; ++j ) {
                        if ( w[ j ] == current[ i ] && !correct[ j ] ) {
                            return true;
                        }
                    }
                    return false;
                } );
            }
        }
    }
}

const auto filter_regex = std::regex( "[.xo]{6}" );

void guess( std::vector< Word > &complete_words ) {
    std::vector< bool > correct( std::tuple_size_v< Word >, false );
    auto words = complete_words;
    std::cout << '[' << words.size() << "]\n";
    Word current = select_random( words );
    std::cout << current << std::endl;
    for ( std::string input; input != "Q"; getline( std::cin, input ) ) {
        if ( input == "" ) {
            continue;
        }
        if ( input == "n" ) {
            remove_from( complete_words, current );
            remove_from( words, current );
            std::cout << '[' << words.size() << "]\n";
            current = select_random( words );
            std::cout << current << std::endl;
            continue;
        }
        if ( input == "j" ) {
            continue;
        }
        if ( input.size() == std::tuple_size_v< Word > &&
             std::regex_match( input, filter_regex ) ) {
            filter( words, input, correct, current );
            std::cout << '[' << words.size() << "]\n";
            if ( words.size() == 0 ) {
                return;
            }
            current = select_random( words );
            std::cout << current << std::endl;
            continue;
        }
        std::cout << '?' << std::endl;
    }
}