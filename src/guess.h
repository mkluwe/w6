#pragma once

#include <format>
#include <iostream>
#include <regex>
#include <set>
#include <vector>

#include "remove_from.h"

template < size_t N >
std::ostream &operator<<( std::ostream &os, const Word< N > &w ) {
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

template < size_t N >
void filter( std::vector< Word< N > > &words, const std::string &mask,
             std::vector< bool > &correct, const Word< N > &current ) {
    for ( unsigned i = 0; i < N; ++i ) {
        if ( mask[ i ] == 'x' && !correct[ i ] ) {
            correct[ i ] = true;
            erase_if( words,
                      [ & ]( Word< N > w ) { return w[ i ] != current[ i ]; } );
        }
    }
    std::set< char > must_contain;
    for ( unsigned i = 0; i < N; ++i ) {
        if ( mask[ i ] == 'o' ) {
            must_contain.insert( current[ i ] );
            erase_if( words,
                      [ & ]( Word< N > w ) { return w[ i ] == current[ i ]; } );
            erase_if( words, [ & ]( Word< N > w ) {
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
                erase_if( words, [ & ]( Word< N > w ) {
                    return w[ i ] == current[ i ];
                } );
            } else {
                erase_if( words, [ & ]( Word< N > w ) {
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

template < size_t N >
void guess( std::vector< Word< N > > &complete_words ) {
    static const auto filter_regex = std::regex( std::format( "[.xo]{{{}}}", N ) );

    std::vector< bool > correct( N, false );
    auto words = complete_words;
    std::cout << '[' << words.size() << "]\n";
    Word current = words[ 0 ];
    std::cout << current << std::endl;
    for ( std::string input; input != "Q"; getline( std::cin, input ) ) {
        if ( input == "" ) {
            continue;
        }
        if ( input == "n" ) {
            remove_from( complete_words, current );
            remove_from( words, current );
            std::cout << '[' << words.size() << "]\n";
            current = words[ 0 ];
            std::cout << current << std::endl;
            continue;
        }
        if ( input == "j" ) {
            continue;
        }
        if ( input.size() == N && std::regex_match( input, filter_regex ) ) {
            filter( words, input, correct, current );
            std::cout << '[' << words.size() << "]\n";
            if ( words.size() == 0 ) {
                return;
            }
            current = words[ 0 ];
            std::cout << current << std::endl;
            continue;
        }
        std::cout << '?' << std::endl;
    }
}