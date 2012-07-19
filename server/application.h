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

public slots:
    void onAboutToQuit();

private:
    void loadConfig();
    void saveConfig();

private:
    Server* server_;
    Config* config_;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
