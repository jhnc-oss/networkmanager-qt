/*
    Copyright 2008,2009 Will Stephenson <wstephenson@kde.org>
    Copyright 2011 Ilia Kats <ilia-kats@gmx.net>
    Copyright 2011-2013 Lamarque V. Souza <lamarque@kde.org>
    Copyright 2013 Jan Grulich <jgrulich@redhat.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "connection.h"

#include <NetworkManager.h>
#include <nm-setting-cdma.h>
#include <nm-setting-connection.h>
#include <nm-setting-gsm.h>
#include <nm-setting-bluetooth.h>
#include <nm-setting-pppoe.h>
#include <nm-setting-vpn.h>
#include <nm-setting-wired.h>
#include <nm-setting-wireless.h>
#include <nm-setting-wimax.h>
#include <nm-setting-olpc-mesh.h>

#include <QDBusConnection>
#include <QDBusPendingReply>
#include <QDBusPendingCallWatcher>

#include "manager_p.h"
#include "device.h"
#include "nm-settings-connectioninterface.h"
#include "generictypes.h"

#include "nmdebug.h"

class NetworkManager::ConnectionPrivate
{
public:
    ConnectionPrivate(const QString &path)
        : iface(NetworkManagerPrivate::DBUS_SERVICE, path, QDBusConnection::systemBus())
    { }

    void updateSettings(const NMVariantMapMap &newSettings = NMVariantMapMap());
    bool unsaved;
    QString uuid;
    QString id;
    NMVariantMapMap settings;
    ConnectionSettings::Ptr connection;
    QString path;
    OrgFreedesktopNetworkManagerSettingsConnectionInterface iface;
};

NetworkManager::Connection::Connection(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new ConnectionPrivate(path))
{
    Q_D(Connection);

    qDBusRegisterMetaType<NMVariantMapMap>();
    QDBusReply<NMVariantMapMap> reply = d->iface.GetSettings();
    if (reply.isValid()) {
        d->updateSettings(reply.value());
    } else {
        d->updateSettings();
    }
    d->path = path;
    //qCDebug(NMQT) << m_connection;

    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::Updated, this, &Connection::onConnectionUpdated);
    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::Removed, this, &Connection::onConnectionRemoved);
#if NM_CHECK_VERSION(0, 9, 10)
    d->unsaved = d->iface.unsaved();
    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::PropertiesChanged, this, &Connection::onPropertiesChanged);
#endif
}

NetworkManager::Connection::~Connection()
{
    delete d_ptr;
}

bool NetworkManager::Connection::isValid() const
{
    Q_D(const Connection);
    return d->iface.isValid();
}

QString NetworkManager::Connection::uuid() const
{
    Q_D(const Connection);
    return d->uuid;
}

QString NetworkManager::Connection::name() const
{
    Q_D(const Connection);
    return d->id;
}
#if NM_CHECK_VERSION(0, 9, 10)
bool NetworkManager::Connection::isUnsaved() const
{
    Q_D(const Connection);
    return d->unsaved;
}
#endif
NetworkManager::ConnectionSettings::Ptr NetworkManager::Connection::settings()
{
    Q_D(Connection);

    if (d->connection.isNull()) {
        d->connection = ConnectionSettings::Ptr(new ConnectionSettings(d->settings));
    }
    return d->connection;
}

QDBusPendingReply<NMVariantMapMap> NetworkManager::Connection::secrets(const QString &setting)
{
    Q_D(Connection);
    return d->iface.GetSecrets(setting);
}

QDBusPendingReply<> NetworkManager::Connection::update(const NMVariantMapMap &settings)
{
    Q_D(Connection);
    return d->iface.Update(settings);
}
#if NM_CHECK_VERSION(0, 9, 10)
QDBusPendingReply<> NetworkManager::Connection::updateUnsaved(const NMVariantMapMap &settings)
{
    Q_D(Connection);
    return d->iface.UpdateUnsaved(settings);
}

QDBusPendingReply<> NetworkManager::Connection::save()
{
    Q_D(Connection);
    return d->iface.Save();
}
#endif
QDBusPendingReply<> NetworkManager::Connection::remove()
{
    Q_D(Connection);
    return d->iface.Delete();
}

QString NetworkManager::Connection::path() const
{
    Q_D(const Connection);
    return d->path;
}

void NetworkManager::Connection::onConnectionUpdated()
{
    Q_D(Connection);
    QDBusReply<NMVariantMapMap> reply = d->iface.GetSettings();
    if (reply.isValid()) {
        d->updateSettings(reply.value());
    } else {
        d->updateSettings();
    }
    emit updated();
}

void NetworkManager::Connection::onConnectionRemoved()
{
    Q_D(Connection);
    QString path = d->path;
    d->updateSettings();
    emit removed(path);
}
#if NM_CHECK_VERSION(0, 9, 10)
void NetworkManager::Connection::onPropertiesChanged(const QVariantMap& properties)
{
    Q_D(Connection);
    QVariantMap::const_iterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString property = it.key();
        if (property == QLatin1String("Unsaved")) {
            d->unsaved = it->toBool();
            emit unsavedChanged(d->unsaved);
        } else {
            qCWarning(NMQT) << Q_FUNC_INFO << "Unhandled property" << property;
        }
        ++it;
    }
}
#endif
void NetworkManager::ConnectionPrivate::updateSettings(const NMVariantMapMap &newSettings)
{
    settings = newSettings;
    if (settings.contains(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME))) {
        QVariantMap connectionSetting = settings.value(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME));
        if (connectionSetting.contains(QLatin1String(NM_SETTING_CONNECTION_UUID))) {
            uuid = connectionSetting.value(QLatin1String(NM_SETTING_CONNECTION_UUID)).toString();
        }
        if (connectionSetting.contains(QLatin1String(NM_SETTING_CONNECTION_ID))) {
            id = connectionSetting.value(QLatin1String(NM_SETTING_CONNECTION_ID)).toString();
        }
    } else if (newSettings.isEmpty()) {
        uuid.clear();
        id.clear();
    }
    connection.clear();
}