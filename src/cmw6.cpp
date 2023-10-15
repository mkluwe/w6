#include "guess.h"
#include "readWords.h"
#include "usage.h"
#include "writeWords.h"

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        return usage();
    }
    auto words = readWords( argv[ 1 ] );
    guess( words );
    writeWords( argv[ 1 ], words );
}