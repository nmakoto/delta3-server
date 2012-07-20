// client.h
// Delta3 project -- Universal remote control system

#pragma once

#include <memory>

#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QObject>
#include <QDebug>
#include <ctime>
#include "defines.h"

class ClientInfoStorage;

//------------------------------------------------------------------------------
namespace delta3
{
//------------------------------------------------------------------------------
class Server;
//------------------------------------------------------------------------------
class Client: public QObject
{
    Q_OBJECT
public:
    Client(
        QTcpSocket* socket,
        ClientInfoStorage* storage,
        QObject* parent = 0
    );

    void send( const QByteArray& cmd ) const;
    void ping() const;
    qint16 getId() const;
    QByteArray getIdHash() const;
    QString getOs() const;
    QString getDevice() const;
    QString getCaption() const;
    ClientStatus getStatus() const;
    quint32 getLastSeen() const;
    qint32 getIp() const;
    void setSeen();
    void setCaption( const QString& caption );
    void disconnectFromHost();
    void sendList( const QByteArray& list );

private slots:
    void onDataReceived();

private:
    struct CommandTableType
    {
        Cspyp1Command command;
        void ( Client::*function )();
    };

    static const CommandTableType CommandTable[];

private:
    void parseClientAuth();
    void parseAdminAuth();
    void parseList();
    void parseTransmit();
    void parseDisconnect();
    void parsePing();
    void parseSetInfo();

private:
    struct BasicInfo
    {
        virtual ~BasicInfo() {}
    };

    struct ClientInfo : BasicInfo
    {
        QByteArray hash;
        QString os;
        QString deviceType;
        QString caption;
    };

    struct AdminInfo : BasicInfo
    {
        QString login;
        QString pass;
    };

private:
    Server* getServer() const;
    ClientInfo* getClientInfo() const;
    AdminInfo* getAdminInfo() const;

private:
    quint32 lastSeen_;   //timestamp
    QTcpSocket* socket_;
    ClientInfoStorage* storage_;
    std::unique_ptr<BasicInfo> clientInfo_;
    ClientStatus status_;
    QByteArray buf_;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
