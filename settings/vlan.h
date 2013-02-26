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

#ifndef NMQT_SETTINGS_VLANSETTING_H
#define NMQT_SETTINGS_VLANSETTING_H

#include "../QtNetworkManager-export.h"
#include "setting.h"

#include <QtCore/QString>

namespace NetworkManager
{
namespace Settings
{
class VlanSettingPrivate;

class NMQT_EXPORT VlanSetting : public Setting
{
    Q_DECLARE_PRIVATE(VlanSetting)
public:
    enum Flag {None = 0, ReorderHeaders = 0x1, Gvrp = 0x2, LooseBinding = 0x4};

    VlanSetting();
    VlanSetting(VlanSetting *);
    ~VlanSetting();

    QString name() const;

    void setInterfaceName(const QString & name);
    QString interfaceName() const;

    void setParent(const QString & parent);
    QString parent() const;

    void setId(quint32 id);
    quint32 id() const;

    void setFlags(Flag flags);
    Flag flags() const;

    void setIngressPriorityMap(const QStringList & map);
    QStringList ingressPriorityMap() const;

    void setEgressPriorityMap(const QStringList & map);
    QStringList egressPriorityMap() const;

    bool hasSecrets() const;

    void fromMap(const QVariantMap & setting);

    QVariantMap toMap() const;

    //FOR DEBUG
    void printSetting();

private:
    VlanSettingPrivate * d_ptr;
};
}
}

#endif // NMQT_SETTINGS_VLANSETTING_H