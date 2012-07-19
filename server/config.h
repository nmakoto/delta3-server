// config.h
// Delta3 project -- Universal remote control system

#pragma once

#include <QObject>

//------------------------------------------------------------------------------
class QSettings;
//------------------------------------------------------------------------------
namespace delta3
{
//------------------------------------------------------------------------------
class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config( QObject *parent = 0 );

    bool save();
    bool save( const QString& fileName );
    bool load();
    bool load( const QString& fileName );

    void set( const QString& variable, const QVariant& value );
    QVariant get( const QString& variable );
    bool has( const QString& variable );

private:
    QSettings* settings_;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
