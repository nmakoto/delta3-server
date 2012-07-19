// application.h
// Delta3 project -- Universal remote control system

#pragma once

#include <QCoreApplication>
#include <QTextCodec>

//------------------------------------------------------------------------------
namespace delta3
{
//------------------------------------------------------------------------------
class Server;
class Config;
//------------------------------------------------------------------------------
class Application: public QCoreApplication
{
    Q_OBJECT
public:
    Application( int& argc, char* argv[] );
    ~Application();
    bool start();
    void printHelp();

public slots:
    void onAboutToQuit();

private:
    void loadConfig();
    void saveConfig();
    bool parseCmdLine();
    bool parseOptions( const QString& arg );
    bool isOption( const QString& arg, const QString& option );
    bool isOption(
        const QString& arg,
        const QString& option1,
        const QString& option2
    );
    bool parseOptionsWithParam( const QString& arg, const QString& param );

private:
    Server* server_;
    Config* config_;
    bool forceQuit_;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
