/*
    Copyright Pranav Gade <pranavgade20@gmail.com>

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

#include "ovsbridgesetting.h"
#include "ovsbridgesetting_p.h"

#include <QDebug>

#if !NM_CHECK_VERSION(1, 10, 0)
#define NM_SETTING_OVS_BRIDGE_SETTING_NAME          "ovs-bridge"
#define NM_SETTING_OVS_BRIDGE_FAIL_MODE             "fail-mode"
#define NM_SETTING_OVS_BRIDGE_MCAST_SNOOPING_ENABLE "mcast-snooping-enable"
#define NM_SETTING_OVS_BRIDGE_RSTP_ENABLE           "rstp-enable"
#define NM_SETTING_OVS_BRIDGE_STP_ENABLE            "stp-enable"
#endif

NetworkManager::OvsBridgeSettingPrivate::OvsBridgeSettingPrivate()
    : name(NM_SETTING_OVS_BRIDGE_SETTING_NAME)
    , mcastSnoopingEnable(false)
    , rstpEnable(false)
    , stpEnable(false)
{ }

NetworkManager::OvsBridgeSetting::OvsBridgeSetting()
    : Setting(Setting::OvsBridge)
    , d_ptr(new OvsBridgeSettingPrivate())
{ }

NetworkManager::OvsBridgeSetting::OvsBridgeSetting(const Ptr &other)
    : Setting(other)
    , d_ptr(new OvsBridgeSettingPrivate())
{
    setFailMode(other->failMode());
    setMcastSnoopingEnable(other->mcastSnoopingEnable());
    setRstpEnable(other->rstpEnable());
    setStpEnable(other->stpEnable());
}

NetworkManager::OvsBridgeSetting::~OvsBridgeSetting()
{
    delete d_ptr;
}

QString NetworkManager::OvsBridgeSetting::name() const
{
    Q_D(const OvsBridgeSetting);

    return d->name;
}

void NetworkManager::OvsBridgeSetting::setMcastSnoopingEnable(bool mcastSnoopingEnable)
{
    Q_D(OvsBridgeSetting);

    d->mcastSnoopingEnable = mcastSnoopingEnable;
}

bool NetworkManager::OvsBridgeSetting::mcastSnoopingEnable() const
{
    Q_D(const OvsBridgeSetting);

    return d->mcastSnoopingEnable;
}

void NetworkManager::OvsBridgeSetting::setRstpEnable(bool rstpEnable)
{
    Q_D(OvsBridgeSetting);

    d->rstpEnable = rstpEnable;
}

bool NetworkManager::OvsBridgeSetting::rstpEnable() const
{
    Q_D(const OvsBridgeSetting);

    return d->rstpEnable;
}

void NetworkManager::OvsBridgeSetting::setStpEnable(bool stpEnable)
{
    Q_D(OvsBridgeSetting);

    d->stpEnable = stpEnable;
}

bool NetworkManager::OvsBridgeSetting::stpEnable() const
{
    Q_D(const OvsBridgeSetting);

    return d->stpEnable;
}

void NetworkManager::OvsBridgeSetting::setFailMode(const QString &mode)
{
    Q_D(OvsBridgeSetting);

    d->failMode = mode;
}

QString NetworkManager::OvsBridgeSetting::failMode() const
{
    Q_D(const OvsBridgeSetting);

    return d->failMode;
}

void NetworkManager::OvsBridgeSetting::fromMap(const QVariantMap &setting)
{
    if (setting.contains(QLatin1String(NM_SETTING_OVS_BRIDGE_MCAST_SNOOPING_ENABLE))) {
        setMcastSnoopingEnable(setting.value(QLatin1String(NM_SETTING_OVS_BRIDGE_MCAST_SNOOPING_ENABLE)).toBool());
    }

    if (setting.contains(QLatin1String(NM_SETTING_OVS_BRIDGE_RSTP_ENABLE))) {
        setRstpEnable(setting.value(QLatin1String(NM_SETTING_OVS_BRIDGE_RSTP_ENABLE)).toBool());
    }

    if (setting.contains(QLatin1String(NM_SETTING_OVS_BRIDGE_STP_ENABLE))) {
        setStpEnable(setting.value(QLatin1String(NM_SETTING_OVS_BRIDGE_STP_ENABLE)).toBool());
    }

    if (setting.contains(QLatin1String(NM_SETTING_OVS_BRIDGE_FAIL_MODE))) {
        setFailMode(setting.value(QLatin1String(NM_SETTING_OVS_BRIDGE_FAIL_MODE)).toString());
    }
}

QVariantMap NetworkManager::OvsBridgeSetting::toMap() const
{
    QVariantMap setting;

    setting.insert(QLatin1String(NM_SETTING_OVS_BRIDGE_MCAST_SNOOPING_ENABLE), mcastSnoopingEnable());
    setting.insert(QLatin1String(NM_SETTING_OVS_BRIDGE_RSTP_ENABLE), rstpEnable());
    setting.insert(QLatin1String(NM_SETTING_OVS_BRIDGE_STP_ENABLE), stpEnable());

    if (!failMode().isEmpty()) {
        setting.insert(QLatin1String(NM_SETTING_OVS_BRIDGE_FAIL_MODE), failMode());
    }

    return setting;
}

QDebug NetworkManager::operator <<(QDebug dbg, const NetworkManager::OvsBridgeSetting &setting)
{
    dbg.nospace() << "type: " << setting.typeAsString(setting.type()) << '\n';
    dbg.nospace() << "initialized: " << !setting.isNull() << '\n';

    dbg.nospace() << NM_SETTING_OVS_BRIDGE_MCAST_SNOOPING_ENABLE << ": " << setting.mcastSnoopingEnable() << '\n';
    dbg.nospace() << NM_SETTING_OVS_BRIDGE_RSTP_ENABLE << ": " << setting.rstpEnable() << '\n';
    dbg.nospace() << NM_SETTING_OVS_BRIDGE_STP_ENABLE << ": " << setting.stpEnable() << '\n';
    dbg.nospace() << NM_SETTING_OVS_BRIDGE_FAIL_MODE << ": " << setting.failMode() << '\n';

    return dbg.maybeSpace();
}
