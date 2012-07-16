// application.cpp
// Delta3 project -- Universal remote control system

#include "application.h"
#include "server.h"

using namespace delta3;

//------------------------------------------------------------------------------
Application::Application( int& argc, char* argv[] ):
    QCoreApplication( argc, argv ),
    server_( new Server(this) )
{
    //QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
}
//------------------------------------------------------------------------------
Application::~Application()
{
}
//------------------------------------------------------------------------------
bool Application::start()
{
    return server_->start();
}
//------------------------------------------------------------------------------
