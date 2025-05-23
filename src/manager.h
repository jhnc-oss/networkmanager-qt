/*
    SPDX-FileCopyrightText: 2008, 2010, 2011 Will Stephenson <wstephenson@kde.org>
    SPDX-FileCopyrightText: 2011-2013 Lamarque Souza <lamarque@kde.org>
    SPDX-FileCopyrightText: 2013 Jan Grulich <jgrulich@redhat.com>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef NETWORKMANAGERQT_NETWORKMANAGER_H
#define NETWORKMANAGERQT_NETWORKMANAGER_H

#include <networkmanagerqt/networkmanagerqt_export.h>

#include "activeconnection.h"
#include "device.h"
#include "dnsconfiguration.h"

/*!
 * \namespace NetworkManager
 * \inmodule NetworkManagerQt
 *
 * This class allows querying the underlying system to discover the available
 * network interfaces and reachable networks. It has also the
 * responsibility to notify when a network interface appears or disappears.
 *
 * It is the unique entry point for network management. Applications should use
 * it to find network interfaces, or to be notified about network related changes.
 *
 * Note that it is implemented as a singleton
 */
namespace NetworkManager
{
Q_NAMESPACE_EXPORT(NETWORKMANAGERQT_EXPORT)

/*!
 *
 * Possible device interfaceflags
 *
 * \value Unknown
 *        the networking system is not active or unable to report its status - proceed with caution
 * \value Asleep
 *        networking is inactive and all devices are disabled
 * \value Disconnected
 *        the system is not connected to any network
 * \value Disconnecting
 *        the system is breaking the connection
 * \value Connecting
 *        the system is not connected to any network
 * \value ConnectedLinkLocal
 *        a network device is connected, but there is only link-local connectivity
 * \value ConnectedSiteOnly
 *        a network device is connected, but there is only site-local connectivity
 * \value Connected
 *        the system is currently connected to a network
 */
enum Status {
    Unknown,
    Asleep,
    Disconnected,
    Disconnecting,
    Connecting,
    ConnectedLinkLocal,
    ConnectedSiteOnly,
    Connected,
};
Q_ENUM_NS(Status)

/*!
 *
 * \value Error
 * \value Warning
 * \value Info
 * \value Debug
 * \value Trace
 *        = Debug in runtime NM < 0.9.10
 */
enum LogLevel {
    Error,
    Warning,
    Info,
    Debug,
    Trace,
};

/*!
 *
 * \value NoChange
 * \value None
 * \value Hardware
 * \value RFKill
 * \value Ethernet
 * \value WiFi
 * \value Bluetooth
 * \value MobileBroadBand
 * \value DHCP4
 * \value DHCP6
 * \value PPP
 * \value WiFiScan
 * \value IPv4
 * \value IPv6
 * \value AutoIPv4
 * \value DNS
 * \value VPN
 * \value Sharing
 * \value Supplicant
 * \value UserSet
 * \value SysSet
 * \value Suspend
 * \value Core
 * \value Devices
 * \value OLPC
 * \value Wimax
 *        TODO: mark it deprecated somehow?
 * \value Infiniband
 * \value Firewall
 * \value Adsl
 * \value Bond
 * \value Vlan
 * \value Agents
 * \value Settings
 * \value Bridge
 * \value DbusProps
 * \value Team
 * \value ConCheck
 * \value Dcb
 * \value Dispatch
 */
enum LogDomain {
    NoChange,
    None,
    Hardware,
    RFKill,
    Ethernet,
    WiFi,
    Bluetooth,
    MobileBroadBand,
    DHCP4,
    DHCP6,
    PPP,
    WiFiScan,
    IPv4,
    IPv6,
    AutoIPv4,
    DNS,
    VPN,
    Sharing,
    Supplicant,
    UserSet,
    SysSet,
    Suspend,
    Core,
    Devices,
    OLPC,
    Wimax /*TODO: mark it deprecated somehow?*/,
    Infiniband,
    Firewall,
    Adsl,
    Bond,
    Vlan,
    Agents,
    Settings,
    Bridge,
    DbusProps,
    Team,
    ConCheck,
    Dcb,
    Dispatch,
};
Q_DECLARE_FLAGS(LogDomains, LogDomain)
Q_FLAGS(LogDomain)

/*!
 *
 * Describes the network connectivity state.
 *
 * \since 0.9.9.0
 *
 * \value UnknownConnectivity
 *        Network connectivity is unknown.
 * \value NoConnectivity
 *        The host is not connected to any network.
 * \value Portal
 *        The host is behind a captive portal and cannot reach the full Internet.
 * \value Limited
 *        The host is connected to a network, but does not appear to be able to reach the full Internet.
 * \value Full
 *        The host is connected to a network, and appears to be able to reach the full Internet.
 */
enum Connectivity {
    UnknownConnectivity = 0,
    NoConnectivity = 1,
    Portal = 2,
    Limited = 3,
    Full = 4,
};
Q_ENUM_NS(Connectivity)

/*!
 * \class NetworkManager::Notifier
 *
 * \inmodule NetworkManagerQt
 */
class NETWORKMANAGERQT_EXPORT Notifier : public QObject
{
    Q_OBJECT
Q_SIGNALS:
    /*!
     * This signal is emitted when the system's connection state changes
     */
    void statusChanged(NetworkManager::Status status);
    /*!
     * This signal is emitted when a new network interface is available.
     *
     * \a uni the network interface identifier
     */
    void deviceAdded(const QString &uni);
    /*!
     * This signal is emitted when a network interface is not available anymore.
     *
     * \a uni the network interface identifier
     */
    void deviceRemoved(const QString &uni);
    /*!
     * This signal is emitted when the status of the wireless changed
     */
    void wirelessEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of the wireless changed
     */
    void wwanEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of the wimax changed
     *
     * \deprecated Wimax support was removed from NetworkManager 1.2
     * (never emitted in runtime NM >= 1.2.0).
     */
    void wimaxEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of the wireless changed
     */
    void wirelessHardwareEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of the wireless changed
     */
    void wwanHardwareEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of the wimax hardware changed
     *
     * \deprecated Wimax support was removed from NetworkManager 1.2
     * (never emitted in runtime NM >= 1.2.0).
     */
    void wimaxHardwareEnabledChanged(bool);
    /*!
     * This signal is emitted when the status of overall networking changed
     */
    void networkingEnabledChanged(bool);
    /*!
     * This signal is emitted when a new connection was made active
     *
     * \a path the path of the new connection
     */
    void activeConnectionAdded(const QString &path);
    /*!
     * This signal is emitted when an active connection is no longer active
     *
     * \a path the path of the removed connection
     */
    void activeConnectionRemoved(const QString &path);
    /*!
     * This signal is emitted when the set of active connections changes
     */
    void activeConnectionsChanged();
    /*!
     * This signal is emitted when the NetworkManager DBus service goes away
     */
    void serviceDisappeared();
    /*!
     * This signal is emitted when the NetworkManager DBus service appears
     */
    void serviceAppeared();
    /*!
     * Emitted when the global connectivity changes.
     * \since 0.9.9.0
     */
    void connectivityChanged(NetworkManager::Connectivity connectivity);
    /*!
     * Emitted when the primary connection changes.
     * \a uni path of the new primary connection
     * \since 0.9.9.0
     */
    void primaryConnectionChanged(const QString &uni);
    /*!
     * Emitted when the activating connection changes.
     * \a uni path of the new activating connection
     * \since 0.9.9.0
     */
    void activatingConnectionChanged(const QString &uni);
    /*!
     * Emitted when the primary connection type changes.
     * \a connection type of the new primary connection
     * \since 5.8.0
     */
    void primaryConnectionTypeChanged(NetworkManager::ConnectionSettings::ConnectionType type);

    /*!
     * Emitted when NM has started/finished its startup sequence
     * \since 0.9.9.0
     */
    void isStartingUpChanged();

    /*!
     * Emitted when metered property has changed
     * \since 5.14.0
     * \sa metered
     */
    void meteredChanged(NetworkManager::Device::MeteredStatus metered);

    /*!
     * Emitted when the global DNS configuration has changed
     * \since 5.45.0
     * \sa globalDnsConfiguration
     */
    void globalDnsConfigurationChanged(const NetworkManager::DnsConfiguration &configuration);

    /*!
     * Emitted when the connectivity check availability has changed
     * @since 6.10.0
     */
    void isConnectivityCheckAvailableChanged(bool);

    /*!
     * Emitted when the connectivity check statu has changed
     * @since 6.10.0
     */
    void isConnectivityCheckEnabledChanged(bool);

    /*!
     * Emitted when the connectivity check URI has changed
     * @since 6.10.0
     */
    void connectivityCheckUriChanged(QString);
};

/*!
 * Get the NetworkManager version
 */
NETWORKMANAGERQT_EXPORT QString version();
/*!
 * Compares NetworkManager's version to the parameter version.
 * returns 1, -1 or 0 if NetworkManager's version is greater, less or equal to parameter.
 */
NETWORKMANAGERQT_EXPORT int compareVersion(const QString &version);
/*!
 * Compares NetworkManager version to x.y.z.
 * returns 1, -1 or 0 if NetworkManager's version is greater, less or equal to x.y.z.
 */
NETWORKMANAGERQT_EXPORT int compareVersion(const int x, const int y, const int z);
/*!
 * Checks if NetworkManager version is at least x.y.z
 * Returns true if NetworkManager's version is greater or equal, false otherwise
 **/
NETWORKMANAGERQT_EXPORT bool checkVersion(const int x, const int y, const int z);
/*!
 * Get the manager connection state
 */
NETWORKMANAGERQT_EXPORT NetworkManager::Status status();
/*!
 * Retrieves the list of all the network interfaces in the system.
 * It includes both hardware and virtual devices.
 *
 * Returns the list of network interfaces available in this system
 */
NETWORKMANAGERQT_EXPORT Device::List networkInterfaces();
/*!
 * Find a new NetworkInterface object given its UNI.  This pointer is owned by the Solid
 * infrastructure.
 *
 * \a uni the identifier of the network interface to find
 * Returns a valid NetworkInterface object if there's a device having the given UNI, an invalid one otherwise
 */
NETWORKMANAGERQT_EXPORT Device::Ptr findNetworkInterface(const QString &uni);
/*!
 * Return the network device referenced by its IP interface name.
 * This is not system independent so programs that will use this method will not be portable.
 */
NETWORKMANAGERQT_EXPORT Device::Ptr findDeviceByIpFace(const QString &iface);
/*!
 * Retrieves the status of networking (as a whole) in the system.
 * This is distinct from whether the system's networking is online or offline.
 * To check that, see \ status().
 *
 * Returns true if this networking is enabled, false otherwise
 */
NETWORKMANAGERQT_EXPORT bool isNetworkingEnabled();
/*!
 * Retrieves the activation status of wireless networking in the system.
 *
 * Returns true if this wireless networking is enabled, false otherwise
 */
NETWORKMANAGERQT_EXPORT bool isWirelessEnabled();
/*!
 * Retrieves the status of wireless hardware in the system. This is typically
 * controlled by a physical switch so there is no way to set this in software.
 *
 * Returns true if this wireless networking is enabled, false otherwise
 */
NETWORKMANAGERQT_EXPORT bool isWirelessHardwareEnabled();
/*!
 * Retrieves the status of wireless broadband (Wireless WAN) in the system.
 *
 * Returns true if this type of wireless networking is enabled, false otherwise
 */
NETWORKMANAGERQT_EXPORT bool isWwanEnabled();
/*!
 * Retrieves the status of wireless broadband (Wireless WAN) hardware in the system. This is typically
 * controlled by a physical switch so there is no way to set this in software.
 *
 * Returns true if this broddband hardware is enabled, false otherwise
 */
NETWORKMANAGERQT_EXPORT bool isWwanHardwareEnabled();

/*!
 * Retrieves the activation status of wimax networking in the system.
 *
 * Returns true if this wimax networking is enabled, false otherwise
 *
 * \deprecated Wimax support was removed from NetworkManager 1.2
 * (always returns false in runtime NM >= 1.2.0).
 */
NETWORKMANAGERQT_EXPORT bool isWimaxEnabled();
/*!
 * Retrieves the status of wimax hardware in the system. This is typically
 * controlled by a physical switch so there is no way to set this in software.
 *
 * Returns true if wimax HW networking is enabled, false otherwise
 *
 * \deprecated Wimax support was removed from NetworkManager 1.2
 * (always returns false in runtime NM >= 1.2.0).
 */
NETWORKMANAGERQT_EXPORT bool isWimaxHardwareEnabled();

/*!
 * Activate a connection using the supplied device.
 *
 * \a connectionUni unique identifier for the connection to be activated
 * \a interfaceUni unique identifier of the network interface to be activated
 * \a connectionParameter can be used to specify extra parameters not specific to the NetworkInterface or the connection, eg which AP to use when several
 * present with same ESSID in range (because ESSID does not guarantee that the AP is part of the network you want to join!)
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<QDBusObjectPath>
activateConnection(const QString &connectionUni, const QString &interfaceUni, const QString &connectionParameter);
/*!
 * Adds a new connection using the given details (if any) as a template (automatically filling in missing settings with the capabilities of the given device and
 * specific object), then activate the new connection. Cannot be used for VPN connections at this time.
 *
 * \a connection connection definition to be added and activated
 * \a interfaceUni unique identifier of the network interface to be activated
 * \a connectionParameter can be used to specify extra parameters not specific to the NetworkInterface or the connection, eg which AP to use when several
 * present with same ESSID in range (because ESSID does not guarantee that the AP is part of the network you want to join!)
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<QDBusObjectPath, QDBusObjectPath>
addAndActivateConnection(const NMVariantMapMap &connection, const QString &interfaceUni, const QString &connectionParameter);
/*!
 * Adds a new connection using the given details (if any) as a template (automatically filling in missing settings with the capabilities of the given device and
 * specific object), then activate the new connection. Cannot be used for VPN connections at this time.
 *
 * \a connection connection definition to be added and activated
 * \a interfaceUni unique identifier of the network interface to be activated
 * \a connectionParameter can be used to specify extra parameters not specific to the NetworkInterface or the connection, eg which AP to use when several
 * present with same ESSID in range (because ESSID does not guarantee that the AP is part of the network you want to join!)
 * \a options further options for the method call.
 *
 * This method extends AddAndActivateConnection to allow passing further
 * parameters. At this time the following options are supported:
 *
 *        * persist: A string value of either "disk" (default), "memory" or "volatile". If "memory" is passed, the connection will not be saved to disk. If
 * "volatile" is passed, the connection will not be saved to disk and will be destroyed when disconnected.
 *        * bind-activation: Bind the activation lifetime. Set to "dbus-name" to automatically disconnect when the requesting process disappears from the bus.
 * The default of "none" means the connection is kept activated normally.
 *
 * \
ote will call AddAndActivateConnection(connection, interfaceUni, connectionParameter) instead when NetworkManager is older than 1.16, which means that the
 * options property is ignored
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<QDBusObjectPath, QDBusObjectPath, QVariantMap>
addAndActivateConnection2(const NMVariantMapMap &connection, const QString &interfaceUni, const QString &connectionParameter, const QVariantMap &options);
/*!
 * Deactivate this network interface, if active
 *
 * \a activeConnection identifier of the connection to deactivate
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<> deactivateConnection(const QString &activeConnection);
/*!
 * Access the list of any active connections
 *
 * Returns a list of valid ActiveConnection objects
 */
NETWORKMANAGERQT_EXPORT ActiveConnection::List activeConnections();
/*!
 * Access the list of any active connections paths
 *
 * Returns a list of valid ActiveConnection paths
 */
NETWORKMANAGERQT_EXPORT QStringList activeConnectionsPaths();
/*!
 * Get current logging verbosity level and operations domains
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<QString, QString> getLogging();

/*!
 * Returns the network connectivity state
 * \since 0.9.9.0
 */
NETWORKMANAGERQT_EXPORT Connectivity connectivity();

/*!
 * Re-check the network connectivity state.
 * \sa connectivity()
 * \since 0.9.9.0
 */
NETWORKMANAGERQT_EXPORT QDBusPendingReply<uint> checkConnectivity();

/*!
 * Returns the "primary" active connection being used
 * to access the network. In particular, if there is no VPN
 * active, or the VPN does not have the default route, then this
 * indicates the connection that has the default route. If there
 * is a VPN active with the default route, then this indicates
 * the connection that contains the route to the VPN endpoint.
 * \since 0.9.9.0
 */
NETWORKMANAGERQT_EXPORT ActiveConnection::Ptr primaryConnection();

/*!
 * Returns an active connection that is currently
 * being activated and which is expected to become the new
 * primaryConnection() when it finishes activating.
 * \since 0.9.9.0
 */
NETWORKMANAGERQT_EXPORT ActiveConnection::Ptr activatingConnection();

/*!
 * Returns The connection type of the "primary" active connection being
 * used to access the network. This is the same as the Type
 * property on the object indicated by PrimaryConnection.
 * \since 5.8.0
 */
NETWORKMANAGERQT_EXPORT NetworkManager::ConnectionSettings::ConnectionType primaryConnectionType();

/*!
 * Indicates whether NM is still starting up; this becomes \a false
 * when NM has finished attempting to activate every connection
 * that it might be able to activate at startup.
 * \since 0.9.9.0
 */
NETWORKMANAGERQT_EXPORT bool isStartingUp();

/*!
 * Returns Indicates whether the connectivity is metered.
 * \since 5.14.0
 */
NETWORKMANAGERQT_EXPORT NetworkManager::Device::MeteredStatus metered();

/*!
 * Returns Gets the global DNS configuration.
 * \since 5.45.0
 */
NETWORKMANAGERQT_EXPORT NetworkManager::DnsConfiguration globalDnsConfiguration();

/*!
 * Returns Sets the global DNS configuration.
 * \since 5.45.0
 */
NETWORKMANAGERQT_EXPORT void setGlobalDnsConfiguration(const NetworkManager::DnsConfiguration &configuration);

/*!
 * Returns whether the connectivity check is available
 * \since 6.10.0
 */
NETWORKMANAGERQT_EXPORT bool isConnectivityCheckAvailable();

/*!
 * Returns whether the connectivity check is enabled
 * \since 6.10.0
 */
NETWORKMANAGERQT_EXPORT bool isConnectivityCheckEnabled();

/*!
 * Returns the URI used for connectivity check
 * \since 6.10.0
 */
NETWORKMANAGERQT_EXPORT QString connectivityCheckUri();

/*!
 * Find an ActiveConnection object for an active connection id
 *
 * \a uni the id of the ActiveConnection
 * Returns a valid ActiveConnection object
 */
NETWORKMANAGERQT_EXPORT ActiveConnection::Ptr findActiveConnection(const QString &uni);
/*!
 * Retrieves the interface types supported by this network manager.
 *
 * Returns the interface types supported by the network manager
 */
NETWORKMANAGERQT_EXPORT Device::Types supportedInterfaceTypes();
/*!
 */
NETWORKMANAGERQT_EXPORT void setNetworkingEnabled(bool enabled);
// implemented in Notifier
/*!
 */
NETWORKMANAGERQT_EXPORT void setWirelessEnabled(bool enabled);
/*!
 */
NETWORKMANAGERQT_EXPORT void setWwanEnabled(bool enabled);
/*!
 * \deprecated Wimax support was removed from NetworkManager 1.2
 * (it is a noop in runtime NM >= 1.2.0).
 */
NETWORKMANAGERQT_EXPORT void setWimaxEnabled(bool enabled);
/*!
 */
NETWORKMANAGERQT_EXPORT void sleep(bool sleep);
/*!
 */
NETWORKMANAGERQT_EXPORT void setLogging(LogLevel, LogDomains);
/*!
 */
NETWORKMANAGERQT_EXPORT NMStringMap permissions();
/*!
 */
NETWORKMANAGERQT_EXPORT Notifier *notifier();

}

#endif
