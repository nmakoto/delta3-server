// main.cpp
// Delta3 project -- Universal remote control system

#include "application.h"

#ifdef Q_OS_LINUX
#include <signal.h>
#endif

delta3::Application* application = NULL;

//------------------------------------------------------------------------------
#ifdef Q_OS_LINUX
void catchSignal( int signal )
{
    if( signal == SIGINT || signal == SIGTERM )
        if( application )
            application->quit();
}
#endif
//------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    delta3::Application app( argc, argv );
    application = &app;

#ifdef Q_OS_LINUX
    signal( SIGINT, catchSignal );
    signal( SIGTERM, catchSignal );
#endif

    if( !application->start() )
        return EXIT_FAILURE;

    return application->exec();
}
//------------------------------------------------------------------------------
