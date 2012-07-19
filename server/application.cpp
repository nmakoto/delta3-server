// application.cpp
// Delta3 project -- Universal remote control system

#include <iostream>
#include <QStringList>
#include "config.h"
#include "server.h"
#include "application.h"

using namespace delta3;

//------------------------------------------------------------------------------
Application::Application( int& argc, char* argv[] ):
    QCoreApplication( argc, argv ),
    server_( new Server(this) ),
    config_( new Config(this) ),
    forceQuit_( false )
{
    //QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    connect( this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()) );
    loadConfig();
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
    if( !parseCmdLine() || forceQuit_ )
    {
        printHelp();
        return false;
    }

    if( !server_->start() )
        return false;

    qDebug(
        "Spawning server at %s:%d",
        qPrintable(server_->address().toString()), server_->port()
    );
    return true;
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
void Application::printHelp()
{
    std::cout
        << "Delta3 project -- Universal remote control system [server]\n"
        << "Usage:\n"
        << "    -h, --help           -- show this help\n"
        << "    -a, --addr [ADDRESS] -- server address to spawn to"
        << "(default '127.0.0.1')\n"
        << "    -p, --port [PORT]    -- server port (default 1235)\n"
    ;
}
//------------------------------------------------------------------------------
bool Application::parseCmdLine()
{
    const QStringList& args = arguments();
    for( int i = 0; i < args.count(); i++ )
    {
        if( parseOptions(args.at(i)) )
            continue;

        if( i < args.count() - 1 )
            parseOptionsWithParam( args.at(i), args.at(i + 1) );
    }
    return true;
}
//------------------------------------------------------------------------------
bool Application::isOption( const QString& arg, const QString& option )
{
    return arg.compare( option ) == 0;
}
//------------------------------------------------------------------------------
bool Application::isOption(
    const QString& arg,
    const QString& option1,
    const QString& option2
)
{
    return isOption( arg, option1 ) || isOption( arg, option2 );
}
//------------------------------------------------------------------------------
bool Application::parseOptions( const QString& arg )
{
    if( isOption(arg, "-h", "--help") )
    {
        forceQuit_ = true;
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
bool Application::parseOptionsWithParam(
    const QString& arg,
    const QString& param
)
{
    if( isOption(arg, "-a", "--addr") )
    {
        server_->setAddress( param );
        return true;
    }

    if( isOption(arg, "-p", "--port") )
    {
        server_->setPort( param.toUInt() );
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
