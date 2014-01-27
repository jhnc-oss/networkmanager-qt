/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -m -i generic-types.h -p nm-settingsinterface /home/jgrulich/development/projects/libnm-qt/dbus/introspection/nm-settings.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NETWORKMANAGERQT_SETTINGSINTERFACE_H
#define NETWORKMANAGERQT_SETTINGSINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#if WITH_MODEMMANAGERQT
#include <ModemManagerQt/generic-types.h>
#else
#include "generic-types.h"
#endif

/*
 * Proxy class for interface org.freedesktop.NetworkManager.Settings
 */
class OrgFreedesktopNetworkManagerSettingsInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.Settings"; }

public:
    OrgFreedesktopNetworkManagerSettingsInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopNetworkManagerSettingsInterface();

    Q_PROPERTY(bool CanModify READ canModify)
    inline bool canModify() const
    { return qvariant_cast< bool >(property("CanModify")); }

    Q_PROPERTY(QList<QDBusObjectPath> Connections READ connections)
    inline QList<QDBusObjectPath> connections() const
    { return qvariant_cast< QList<QDBusObjectPath> >(property("Connections")); }

    Q_PROPERTY(QString Hostname READ hostname)
    inline QString hostname() const
    { return qvariant_cast< QString >(property("Hostname")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusObjectPath> AddConnection(NMVariantMapMap connection)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(connection);
        return asyncCallWithArgumentList(QLatin1String("AddConnection"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> AddConnectionUnsaved(const QVariantMap &connection)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(connection);
        return asyncCallWithArgumentList(QLatin1String("AddConnectionUnsaved"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> GetConnectionByUuid(const QString &uuid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(uuid);
        return asyncCallWithArgumentList(QLatin1String("GetConnectionByUuid"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> > ListConnections()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ListConnections"), argumentList);
    }

    inline QDBusPendingReply<bool, QStringList> LoadConnections(const QStringList &filenames)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(filenames);
        return asyncCallWithArgumentList(QLatin1String("LoadConnections"), argumentList);
    }
    inline QDBusReply<bool> LoadConnections(const QStringList &filenames, QStringList &failures)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(filenames);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("LoadConnections"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            failures = qdbus_cast<QStringList>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<bool> ReloadConnections()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ReloadConnections"), argumentList);
    }

    inline QDBusPendingReply<> SaveHostname(const QString &hostname)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(hostname);
        return asyncCallWithArgumentList(QLatin1String("SaveHostname"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void ConnectionRemoved(const QDBusObjectPath &connection);
    void NewConnection(const QDBusObjectPath &connection);
    void PropertiesChanged(const QVariantMap &properties);
};

#endif
