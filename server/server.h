// server.h
// Delta3 project -- Universal remote control system

#pragma once

#include <QObject>
#include <QHostAddress>
#include <QtNetwork/QTcpServer>
#include <QMap>
#include <QTimerEvent>
#include "defines.h"
#include "clientinfostorage.h"

//------------------------------------------------------------------------------
namespace delta3
{
//------------------------------------------------------------------------------
class Client;
//------------------------------------------------------------------------------

typedef QMap<qint32, Client*> Clients;

//------------------------------------------------------------------------------
class Server: public QObject
{
    Q_OBJECT
public:
    Server( QObject* parent = 0 );
    ~Server();

    bool start();

    QByteArray listConnectedClients();
    Clients::iterator searchClient( qint32 clientId );
    Clients::iterator clientEnd();
    void resendListToAdmins();
    void setClientCaption( qint16 clientId, const QString& caption );

    void setAddress( const QHostAddress& address );
    void setAddress( const QString& address );
    void setPort( quint16 port );

    const QHostAddress& address() const;
    quint16 port() const;

private slots:
    void onNewConnection();

private:
    void timerEvent( QTimerEvent* event );

private:
    QTcpServer* tcpServer_;
    Clients clients_;
    ClientInfoStorage* storage_;
    QHostAddress address_;
    quint16 port_;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
