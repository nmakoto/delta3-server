// server.cpp
// Delta3 project -- Universal remote control system

#include "server.h"
#include "client.h"
#include "utils.h"

//------------------------------------------------------------------------------
namespace
{
//------------------------------------------------------------------------------
const QHostAddress& DEFAULT_HOST_ADDRESS = QHostAddress::Any;
const quint16 DEFAULT_HOST_PORT = 1235;

const quint16 MAX_UNACTIVE_TIME = 15;
const quint16 TIME_TO_PING = 5;
}
//------------------------------------------------------------------------------

using namespace delta3;

//------------------------------------------------------------------------------
Server::Server( QObject* parent ):
    QObject( parent ),
    tcpServer_( new QTcpServer(this) ),
    address_( DEFAULT_HOST_ADDRESS ),
    port_( DEFAULT_HOST_PORT )
{
    connect(
        tcpServer_,
        SIGNAL(newConnection()),
        this,
        SLOT(onNewConnection())
    );
    //qDebug() << "Server started";
}
//------------------------------------------------------------------------------
Server::~Server()
{
}
//------------------------------------------------------------------------------
bool Server::start()
{
    startTimer( DEFAULT_TIMER_INTERVAL );
    qDebug(
        "Spawning server at %s:%d",
        qPrintable(address_.toString()), port()
    );
    //return tcpServer_->listen( QHostAddress("0.0.0.0"), DEFAULT_PORT );
    return tcpServer_->listen( address_, port_ );
}
//------------------------------------------------------------------------------
void Server::onNewConnection()
{
    qDebug() << "Server::onNewConnection(): new anonymous user connected";
    Client* client = new Client(
        tcpServer_->nextPendingConnection(),
        this
    );
    clients_.insert( client->getId(), client );
}
//------------------------------------------------------------------------------
QByteArray Server::listConnectedClients()
{
    QByteArray result;
    qint16 clientNum = 0;

    for( auto i = clients_.begin(); i != clients_.end(); i++ )
    {
        if( i.value()->getStatus() == ST_CLIENT )
        {
            QByteArray clientInfo;
            clientInfo.append( toBytes((qint16)i.key()) );
            clientInfo.append( i.value()->getIdHash() );
            clientInfo.append( toBytes(i.value()->getOs(), 20), 20 );
            clientInfo.append( toBytes(i.value()->getDevice(), 24), 24 );
            clientInfo.append( toBytes(i.value()->getCaption(), 30), 30 );
            result.append( clientInfo );
            clientNum++;
        }
    }

    result = toBytes( clientNum ) + result;
    return result;
}
//------------------------------------------------------------------------------
Clients::iterator Server::searchClient( qint32 clientId )
{
    return clients_.find( clientId );
}
//------------------------------------------------------------------------------
Clients::iterator Server::clientEnd()
{
    return clients_.end();
}
//------------------------------------------------------------------------------
void Server::timerEvent( QTimerEvent* event )
{
    Q_UNUSED( event );

    for( auto i = clients_.begin(); i != clients_.end(); i++ )
    {
        if( i.value()->getStatus() == ST_DISCONNECTED )
            continue;

        if( i.value()->getLastSeen() > MAX_UNACTIVE_TIME )
        {
            qDebug() << "Client inactive!";
            i.value()->disconnectFromHost();
            continue;
        }

        if( i.value()->getLastSeen() > TIME_TO_PING )
        {
            i.value()->ping();
        }
    }
}
//------------------------------------------------------------------------------
void Server::resendListToAdmins()
{
    qDebug() << "Sending list!";
    QByteArray clientList = listConnectedClients();

    for( auto i = clients_.begin(); i != clients_.end(); i++ )
        if( i.value()->getStatus() == ST_ADMIN )
            i.value()->sendList( clientList );
}
//------------------------------------------------------------------------------
void Server::setAddress( const QHostAddress& address )
{
    address_ = address;
}
//------------------------------------------------------------------------------
void Server::setAddress( const QString& address )
{
    address_ = QHostAddress( address );
    if( address_ == QHostAddress::Null )
        address_ = DEFAULT_HOST_ADDRESS;
}
//------------------------------------------------------------------------------
void Server::setPort( quint16 port )
{
    port_ = port;
}
//------------------------------------------------------------------------------
const QHostAddress& Server::address() const
{
    return address_;
}
//------------------------------------------------------------------------------
quint16 Server::port() const
{
    return port_;
}
//------------------------------------------------------------------------------
