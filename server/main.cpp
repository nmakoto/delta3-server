// main.cpp
// Delta3 project -- Universal remote control system

#include <cstdlib>
#include "application.h"

//------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    delta3::Application app( argc, argv );

    if( !app.start() )
        return EXIT_FAILURE;

    return app.exec();
}
//------------------------------------------------------------------------------
