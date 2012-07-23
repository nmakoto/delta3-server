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
/**
 * Класс отвечающий за запуск приложения.
 *
 * На данный момент в нём нет практически никакой функциональности,
 * однако в нём планируется организовать парсинг аргументов командной
 * строки, а так же функциональность, которая не относится
 * непосредственно к серверной части. Внутри этого класса создаётся
 * объект класса Server - большая часть функциональности приложения
 * сосредаточена в нём.
 */
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
