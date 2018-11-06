/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was:
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef VPNPLUGININTERFACE_H
#define VPNPLUGININTERFACE_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtDBus>
#include "generictypes.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManager.VPN.Plugin
 */
class OrgFreedesktopNetworkManagerVPNPluginInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
#ifdef NMQT_STATIC
    {
        return "org.kde.fakenetwork.Settings.VPN.Plugin";
    }
#else
    {
        return "org.freedesktop.NetworkManager.VPN.Plugin";
    }
#endif

public:
    OrgFreedesktopNetworkManagerVPNPluginInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~OrgFreedesktopNetworkManagerVPNPluginInterface();

    Q_PROPERTY(uint State READ state)
    inline uint state() const
    {
        return qvariant_cast< uint >(property("State"));
    }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Connect(NMVariantMapMap connection)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(connection);
        return asyncCallWithArgumentList(QStringLiteral("Connect"), argumentList);
    }

    inline QDBusPendingReply<> ConnectInteractive(NMVariantMapMap connection, QVariant details)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(connection) << QVariant::fromValue(details);
        return asyncCallWithArgumentList(QStringLiteral("ConnectInteractive"), argumentList);
    }

    inline QDBusPendingReply<> Disconnect()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Disconnect"), argumentList);
    }

    inline QDBusPendingReply<QString> NeedSecrets(NMVariantMapMap settings)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(settings);
        return asyncCallWithArgumentList(QStringLiteral("NeedSecrets"), argumentList);
    }

    inline QDBusPendingReply<> NewSecrets(NMVariantMapMap connection)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(connection);
        return asyncCallWithArgumentList(QStringLiteral("NewSecrets"), argumentList);
    }

    inline QDBusPendingReply<> SetConfig(QVariant config)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(config);
        return asyncCallWithArgumentList(QStringLiteral("SetConfig"), argumentList);
    }

    inline QDBusPendingReply<> SetFailure(const QString &reason)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(reason);
        return asyncCallWithArgumentList(QStringLiteral("SetFailure"), argumentList);
    }

    inline QDBusPendingReply<> SetIp4Config(QVariant config)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(config);
        return asyncCallWithArgumentList(QStringLiteral("SetIp4Config"), argumentList);
    }

    inline QDBusPendingReply<> SetIp6Config(QVariant config)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(config);
        return asyncCallWithArgumentList(QStringLiteral("SetIp6Config"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void Config(QVariant config);
    void Failure(uint reason);
    void Ip4Config(QVariant ip4config);
    void Ip6Config(QVariant ip6config);
    void LoginBanner(const QString &banner);
    void SecretsRequired(const QString &message, const QStringList &secrets);
    void StateChanged(uint state);
};

#endif
