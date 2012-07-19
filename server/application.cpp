// application.cpp
// Delta3 project -- Universal remote control system

#include "config.h"
#include "server.h"
#include "application.h"

using namespace delta3;

//------------------------------------------------------------------------------
Application::Application( int& argc, char* argv[] ):
    QCoreApplication( argc, argv ),
    server_( new Server(this) ),
    config_( new Config(this) )
{
    //QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    loadConfig();
    connect( this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()) );
}
//------------------------------------------------------------------------------
Application::~Application()
{
}
//------------------------------------------------------------------------------
void Application::onAboutToQuit()
{
    saveConfig();
}
//------------------------------------------------------------------------------
bool Application::start()
{
    return server_->start();
}
//------------------------------------------------------------------------------
void Application::loadConfig()
{
    config_->load();

    if( config_->has("server.address") )
        server_->setAddress( config_->get("server.address").toString() );

    if( config_->has("server.port") )
        server_->setPort( config_->get("server.port").toUInt() );
}
//------------------------------------------------------------------------------
void Application::saveConfig()
{
    config_->set( "server.address", server_->address().toString() );
    config_->set( "server.port", server_->port() );
    config_->save();
}
//------------------------------------------------------------------------------
