/*
    Copyright 2012-2013  Jan Grulich <jgrulich@redhat.com>

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

#include "setting.h"

#include <nm-setting-bond.h>
#include <nm-setting-bridge.h>
#include <nm-setting-cdma.h>
#include <nm-setting-connection.h>
#include <nm-setting-wired.h>
#include <nm-setting-ip4-config.h>
#include <nm-setting-ip6-config.h>
#include <nm-setting-8021x.h>
#include <nm-setting-gsm.h>
#include <nm-setting-bluetooth.h>
#include <nm-setting-olpc-mesh.h>
#include <nm-setting-ppp.h>
#include <nm-setting-pppoe.h>
#include <nm-setting-serial.h>
#include <nm-setting-vlan.h>
#include <nm-setting-vpn.h>
#include <nm-setting-wireless.h>
#include <nm-setting-wireless-security.h>
#include <nm-setting-wimax.h>

#include <QtCore/QDebug>

namespace NetworkManager
{
namespace Settings
{
class SettingPrivate
{
public:
    SettingPrivate();

    Setting::SettingType type;
    bool initialized;
};
}
}

NetworkManager::Settings::SettingPrivate::SettingPrivate():
    type(Setting::Wired),
    initialized(false)
{ }

QString NetworkManager::Settings::Setting::typeAsString(NetworkManager::Settings::Setting::SettingType type)
{
    QString typeString;

    switch (type) {
    case Cdma:
        typeString = QLatin1String(NM_SETTING_CDMA_SETTING_NAME);
        break;
    case Gsm:
        typeString = QLatin1String(NM_SETTING_GSM_SETTING_NAME);
        break;
    case Bluetooth:
        typeString = QLatin1String(NM_SETTING_BLUETOOTH_SETTING_NAME);
        break;
    case Ipv4:
        typeString = QLatin1String(NM_SETTING_IP4_CONFIG_SETTING_NAME);
        break;
    case Ipv6:
        typeString = QLatin1String(NM_SETTING_IP6_CONFIG_SETTING_NAME);
        break;
    case Ppp:
        typeString = QLatin1String(NM_SETTING_PPP_SETTING_NAME);
        break;
    case Pppoe:
        typeString = QLatin1String(NM_SETTING_PPPOE_SETTING_NAME);
        break;
    case Security8021x:
        typeString = QLatin1String(NM_SETTING_802_1X_SETTING_NAME);
        break;
    case Serial:
        typeString = QLatin1String(NM_SETTING_SERIAL_SETTING_NAME);
        break;
    case Vpn:
        typeString = QLatin1String(NM_SETTING_VPN_SETTING_NAME);
        break;
    case Wired:
        typeString = QLatin1String(NM_SETTING_WIRED_SETTING_NAME);
        break;
    case Wireless:
        typeString = QLatin1String(NM_SETTING_WIRELESS_SETTING_NAME);
        break;
    case WirelessSecurity:
        typeString = QLatin1String(NM_SETTING_WIRELESS_SECURITY_SETTING_NAME);
        break;
    case OlpcMesh:
        typeString = QLatin1String(NM_SETTING_OLPC_MESH_SETTING_NAME);
        break;
    case Vlan:
        typeString = QLatin1String(NM_SETTING_VLAN_SETTING_NAME);
        break;
    case Wimax:
        typeString = QLatin1String(NM_SETTING_WIMAX_SETTING_NAME);
        break;
    case Bond:
        typeString = QLatin1String(NM_SETTING_BOND_SETTING_NAME);
        break;
    case Bridge:
        typeString = QLatin1String(NM_SETTING_BRIDGE_SETTING_NAME);
        break;
    default:
        break;
    }

    return typeString;
}

NetworkManager::Settings::Setting::SettingType NetworkManager::Settings::Setting::typeFromString(const QString& typeString)
{
    SettingType type = Wired;

    if (typeString == QLatin1String(NM_SETTING_CDMA_SETTING_NAME)) {
        type = Cdma;
    } else if (typeString == QLatin1String(NM_SETTING_GSM_SETTING_NAME)) {
        type = Gsm;
    } else if (typeString == QLatin1String(NM_SETTING_BLUETOOTH_SETTING_NAME)) {
        type = Bluetooth;
    } else if (typeString == QLatin1String(NM_SETTING_IP4_CONFIG_SETTING_NAME)) {
        type = Ipv4;
    } else if (typeString == QLatin1String(NM_SETTING_IP6_CONFIG_SETTING_NAME)) {
        type = Ipv6;
    } else if (typeString == QLatin1String(NM_SETTING_PPP_SETTING_NAME)) {
        type = Ppp;
    } else if (typeString == QLatin1String(NM_SETTING_PPPOE_SETTING_NAME)) {
        type = Pppoe;
    } else if (typeString == QLatin1String(NM_SETTING_SERIAL_SETTING_NAME)) {
        type = Serial;
    } else if (typeString == QLatin1String(NM_SETTING_802_1X_SETTING_NAME)) {
        type = Security8021x;
    } else if (typeString == QLatin1String(NM_SETTING_VPN_SETTING_NAME)) {
        type = Vpn;
    } else if (typeString == QLatin1String(NM_SETTING_WIRED_SETTING_NAME)) {
        type = Wired;
    } else if (typeString == QLatin1String(NM_SETTING_WIRELESS_SETTING_NAME)) {
        type = Wireless;
    } else if (typeString == QLatin1String(NM_SETTING_WIRELESS_SECURITY_SETTING_NAME)) {
        type = WirelessSecurity;
    } else if (typeString == QLatin1String(NM_SETTING_OLPC_MESH_SETTING_NAME)) {
        type = OlpcMesh;
    } else if (typeString == QLatin1String(NM_SETTING_VLAN_SETTING_NAME)) {
        type = Vlan;
    } else if (typeString == QLatin1String(NM_SETTING_WIMAX_SETTING_NAME)) {
        type = Wimax;
    } else if (typeString == QLatin1String(NM_SETTING_BOND_SETTING_NAME)) {
        type = Bond;
    } else if (typeString == QLatin1String(NM_SETTING_BRIDGE_SETTING_NAME)) {
        type = Bridge;
    }

    return type;
}

NetworkManager::Settings::Setting::Setting(SettingType type):
    d_ptr(new SettingPrivate())
{
    setType(type);
}

NetworkManager::Settings::Setting::Setting(const NetworkManager::Settings::Setting::Ptr &setting):
    d_ptr(new SettingPrivate())
{
    setInitialized(!setting->isNull());
    setType(setting->type());
}

NetworkManager::Settings::Setting::~Setting()
{
    delete d_ptr;
}

QStringList NetworkManager::Settings::Setting::needSecrets(bool requestNew) const
{
    Q_UNUSED(requestNew);
    return QStringList();
}

void NetworkManager::Settings::Setting::secretsFromMap(const QVariantMap &map)
{
    Q_UNUSED(map);
}

void NetworkManager::Settings::Setting::secretsFromStringMap(const NMStringMap &map)
{
    QVariantMap secretsMap;
    NMStringMap::ConstIterator i = map.constBegin();
    while (i != map.constEnd()) {
        secretsMap.insert(i.key(), i.value());
        ++i;
    }
    secretsFromMap(secretsMap);
}

QVariantMap NetworkManager::Settings::Setting::secretsToMap() const
{
    return QVariantMap();
}

NMStringMap NetworkManager::Settings::Setting::secretsToStringMap() const
{
    NMStringMap ret;
    QVariantMap secretsMap = secretsToMap();
    QVariantMap::ConstIterator i = secretsMap.constBegin();
    while (i != secretsMap.constEnd()) {
        ret.insert(i.key(), i.value().toString());
        ++i;
    }

    return ret;
}

void NetworkManager::Settings::Setting::setInitialized(bool initialized)
{
    Q_D(Setting);

    d->initialized = initialized;
}

bool NetworkManager::Settings::Setting::isNull() const
{
    Q_D(const Setting);

    return !d->initialized;
}

void NetworkManager::Settings::Setting::setType(NetworkManager::Settings::Setting::SettingType type)
{
    Q_D(Setting);

    d->type = type;
}

NetworkManager::Settings::Setting::SettingType NetworkManager::Settings::Setting::type() const
{
    Q_D(const Setting);

    return d->type;
}

void NetworkManager::Settings::Setting::printSetting()
{
    qDebug() << "type: " << typeAsString(type());
    qDebug() << "initialized: " << !isNull();
}
