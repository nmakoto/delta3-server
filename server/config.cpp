// client.cpp
// Delta3 project -- Universal remote control system

#include <QStringList>
#include <QFile>
#include <QSettings>
#include <QVariant>
#include <options.h>
#include "config.h"

const QString DEFAULT_CONFIG_NAME = "server";

using namespace delta3;

//------------------------------------------------------------------------------
Config::Config( QObject* parent ):
    QObject( parent ),
    settings_(
        new QSettings(QSettings::UserScope, DEV_TEAM, DEFAULT_CONFIG_NAME)
    )
{
}
//------------------------------------------------------------------------------
bool Config::load()
{
    settings_->sync();
    return true;
}
//------------------------------------------------------------------------------
bool Config::load( const QString& fileName )
{
    if( !QFile::exists(fileName) )
        return false;

    QSettings* newSettings = new QSettings(
        fileName,
        QSettings::NativeFormat,
        this
    );

    settings_->clear();
    const QStringList list = newSettings->allKeys();
    for( auto it = list.begin(); it != list.end(); ++it )
        settings_->setValue( *it, newSettings->value(*it) );

    return true;
}
//------------------------------------------------------------------------------
bool Config::save()
{
    if( !settings_->isWritable() )
    {
        qWarning( "ERROR: Config::save() :: config is not writeable.");
        return false;
    }

    qDebug(
        "Config::save() :: Saving config to '%s'...",
        qPrintable(settings_->fileName())
    );
    settings_->sync();
    return true;
}
//------------------------------------------------------------------------------
bool Config::save( const QString& fileName )
{
    if( fileName.isEmpty() )
        return false;

    qDebug(
        "Config::save() :: Saving config to '%s'...",
        qPrintable(fileName)
    );
    settings_->sync();

    QSettings* newSettings = new QSettings(
        fileName,
        QSettings::NativeFormat,
        this
    );
    const QStringList& list = settings_->allKeys();
    for( auto it = list.begin(); it != list.end(); ++it )
        newSettings->setValue( *it, settings_->value(*it) );

    newSettings->sync();
    return true;
}
//------------------------------------------------------------------------------
void Config::set( const QString& variable, const QVariant& value )
{
    settings_->setValue( variable, value );
}
//------------------------------------------------------------------------------
QVariant Config::get( const QString& variable )
{
    return settings_->value( variable );
}
//------------------------------------------------------------------------------
bool Config::has( const QString& variable )
{
    return settings_->contains( variable );
}
//------------------------------------------------------------------------------
