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

#ifndef NETWORKMANAGERQT_BRIDGEPORT_SETTING_P_H
#define NETWORKMANAGERQT_BRIDGEPORT_SETTING_P_H

#include <QString>

namespace NetworkManager
{

class BridgePortSettingPrivate
{
public:
    BridgePortSettingPrivate();

    QString name;
    quint32 priority;
    quint32 pathCost;
    bool hairpinMode;
};

}

#endif // NETWORKMANAGERQT_BRIDGEPORT_SETTING_P_H
