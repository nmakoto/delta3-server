#pragma once

#include <QObject>
#include <QHostAddress>
#include <QtNetwork/QTcpServer>
#include <QMap>
#include "client.h"

typedef QMap<qint32,Client*> Clients;

class Server: public QObject
{
    Q_OBJECT
public:
    Server(QObject* parent = 0);
    ~Server();
    bool start();
    QString listConnectedClients();
    Clients::iterator searchClient(qint32 clientId);
    Clients::iterator clientEnd();
private slots:
    void onNewConnection();
private:
    QTcpServer* tcpServer_;
    Clients clients_;
};