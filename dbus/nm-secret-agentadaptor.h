/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -a nm-secret-agentadaptor -i secretagent.h -l NetworkManager::SecretAgent /home/jgrulich/development/projects/libnm-qt/dbus/introspection/nm-secret-agent.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef NM_SECRET_AGENTADAPTOR_H
#define NM_SECRET_AGENTADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "secretagent.h"
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface org.freedesktop.NetworkManager.SecretAgent
 */
class SecretAgentAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.NetworkManager.SecretAgent")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.freedesktop.NetworkManager.SecretAgent\">\n"
"    <tp:docstring>\n"
"            Private D-Bus interface used by secret agents that store and provide\n"
"            secrets to NetworkManager.  If an agent provides secrets to\n"
"            NetworkManager as part of connection creation, and the some of those\n"
"            secrets are \"agent owned\" the agent should store those secrets\n"
"            itself and should not expect its SaveSecrets() method to be called.\n"
"            SaveSecrets() will be called eg if some program other than the\n"
"            agent itself (like a connection editor) changes the secrets out of\n"
"            band.  The agent should implement this D-Bus interface on an object\n"
"            with the path /org/freedesktop/NetworkManager/SecretAgent.\n"
"        </tp:docstring>\n"
"    <method name=\"GetSecrets\">\n"
"      <tp:docstring>\n"
"                Retrieve and return stored secrets, if any, or request new\n"
"                secrets from the agent's user.  If user interaction is allowed\n"
"                and the user enters new secrets, the agent is expected to save\n"
"                the new secrets to persistent storage (if the secret's flags\n"
"                include AGENT_OWNED) as NetworkManager will not send these\n"
"                secrets back to the same agent via a SaveSecrets() call.  If\n"
"                the user canceled any interaction, the agent should return the\n"
"                UserCanceled error (see below).\n"
"            </tp:docstring>\n"
"      <annotation value=\"impl_secret_agent_get_secrets\" name=\"org.freedesktop.DBus.GLib.CSymbol\"/>\n"
"      <annotation value=\"\" name=\"org.freedesktop.DBus.GLib.Async\"/>\n"
"      <arg direction=\"in\" tp:type=\"String_String_Variant_Map_Map\" type=\"a{sa{sv}}\" name=\"connection\">\n"
"        <annotation value=\"NMVariantMapMap\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"        <tp:docstring>\n"
"                    Nested settings maps containing the connection for which\n"
"                    secrets are being requested.  This may contain system-owned\n"
"                    secrets if the agent has successfully authenticated to\n"
"                    modify system network settings and the GetSecrets request\n"
"                    flags allow user interaction.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"o\" name=\"connection_path\">\n"
"        <tp:docstring>\n"
"                    Object path of the connection for which secrets are being\n"
"                    requested.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"s\" name=\"setting_name\">\n"
"        <tp:docstring>\n"
"                    Setting name for which secrets are being requested.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"as\" name=\"hints\">\n"
"        <tp:docstring>\n"
"                    Array of strings of key names in the requested setting for\n"
"                    which NetworkManager thinks a secrets may be required,\n"
"                    and/or well-known identifiers and data that may be useful\n"
"                    to the client in processing the secrets request.  Note that\n"
"                    it's not always possible to determine which secret is\n"
"                    required, so in some cases no hints may be given.  The Agent\n"
"                    should return any secrets it has, or that it thinks are\n"
"                    required, regardless of what hints NetworkManager sends\n"
"                    in this request.  Some hints have special prefixes that\n"
"                    provide information to the agent; for example, VPN requests\n"
"                    may send server-specific messages prefixed with\n"
"                    \"x-vpn-message:\".\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" tp:type=\"NM_SECRET_AGENT_GET_SECRETS_FLAGS\" type=\"u\" name=\"flags\">\n"
"        <tp:docstring>\n"
"                    Flags which modify the behavior of the secrets request.\n"
"                    If true, new secrets are assumed to be invalid or incorrect,\n"
"                    and the agent should ask the user for new secrets.  If false,\n"
"                    existing secrets should be retrieved from storage and\n"
"                    returned without interrupting the user.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"out\" tp:type=\"String_String_Variant_Map_Map\" type=\"a{sa{sv}}\" name=\"secrets\">\n"
"        <annotation value=\"NMVariantMapMap\" name=\"org.qtproject.QtDBus.QtTypeName.Out0\"/>\n"
"        <tp:docstring>\n"
"                    Nested settings maps containing secrets.  Each setting MUST\n"
"                    contain at least the 'name' field, containing the name of\n"
"                    the setting, and one or more secrets.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <tp:possible-errors>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.NotAuthorized\">\n"
"          <tp:docstring>\n"
"                      Should be returned when the process requesting secrets is\n"
"                      not authorized to do so (like if the caller is not root\n"
"                      or not NetworkManager).\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.InvalidConnection\">\n"
"          <tp:docstring>\n"
"                      Should be returned if the 'connection' argument is invalid.\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.UserCanceled\">\n"
"          <tp:docstring>\n"
"                      Should be returned when the user has canceled the request.\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.AgentCanceled\">\n"
"          <tp:docstring>\n"
"                      Should be returned when NetworkManager has requested that\n"
"                      the agent cancel the request.\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.InternalError\">\n"
"          <tp:docstring>\n"
"                      Should be returned if the agent has encountered some internal\n"
"                      error processing the request.\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"        <tp:error name=\"org.freedesktop.NetworkManager.SecretAgent.NoSecrets\">\n"
"          <tp:docstring>\n"
"                      Should be returned if there are no available secrets, for\n"
"                      example if user interaction is not allowed and there are\n"
"                      no secrets stored by the agent for this connection.\n"
"                  </tp:docstring>\n"
"        </tp:error>\n"
"      </tp:possible-errors>\n"
"    </method>\n"
"    <tp:flags value-prefix=\"NM_SECRET_AGENT_GET_SECRETS_FLAG\" type=\"u\" name=\"NM_SECRET_AGENT_GET_SECRETS_FLAGS\">\n"
"      <tp:docstring>\n"
"            Flags modifying the behavior of GetSecrets request.\n"
"          </tp:docstring>\n"
"      <tp:flag suffix=\"NONE\" value=\"0x0\">\n"
"        <tp:docstring>\n"
"              No special behavior; by default no user interaction is allowed and\n"
"              requests for secrets are fulfilled from persistent storage, or\n"
"              if no secrets are available an error is returned.\n"
"            </tp:docstring>\n"
"      </tp:flag>\n"
"      <tp:flag suffix=\"ALLOW_INTERACTION\" value=\"0x1\">\n"
"        <tp:docstring>\n"
"              Allows the request to interact with the user, possibly prompting\n"
"              via UI for secrets if any are required, or if none are found in\n"
"              persistent storage.\n"
"            </tp:docstring>\n"
"      </tp:flag>\n"
"      <tp:flag suffix=\"REQUEST_NEW\" value=\"0x2\">\n"
"        <tp:docstring>\n"
"              Explicitly prompt for new secrets from the user.  This flag\n"
"              signals that NetworkManager thinks any existing secrets are\n"
"              invalid or wrong.  This flag implies that interaction is allowed.\n"
"            </tp:docstring>\n"
"      </tp:flag>\n"
"      <tp:flag suffix=\"USER_REQUESTED\" value=\"0x4\">\n"
"        <tp:docstring>\n"
"              Set if the request was initiated by user-requested action via the\n"
"              D-Bus interface, as opposed to automatically initiated by\n"
"              NetworkManager in response to (for example) scan results or\n"
"              carrier changes.\n"
"            </tp:docstring>\n"
"      </tp:flag>\n"
"    </tp:flags>\n"
"    <method name=\"CancelGetSecrets\">\n"
"      <tp:docstring>\n"
"                Cancel a pending GetSecrets request for secrets of the given\n"
"                connection.  Any GetSecrets request with the same\n"
"                'connection_path' and 'setting_name' that are given in a\n"
"                CancelGetSecrets request should be canceled.\n"
"            </tp:docstring>\n"
"      <annotation value=\"impl_secret_agent_cancel_get_secrets\" name=\"org.freedesktop.DBus.GLib.CSymbol\"/>\n"
"      <annotation value=\"\" name=\"org.freedesktop.DBus.GLib.Async\"/>\n"
"      <arg direction=\"in\" type=\"o\" name=\"connection_path\">\n"
"        <tp:docstring>\n"
"                    Object path of the connection for which, if secrets for\n"
"                    the given 'setting_name' are being requested, the request\n"
"                    should be canceled.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"s\" name=\"setting_name\">\n"
"        <tp:docstring>\n"
"                    Setting name for which secrets for this connection were\n"
"                    originally being requested.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"    </method>\n"
"    <method name=\"SaveSecrets\">\n"
"      <tp:docstring>\n"
"                Save given secrets to backing storage.\n"
"            </tp:docstring>\n"
"      <annotation value=\"impl_secret_agent_save_secrets\" name=\"org.freedesktop.DBus.GLib.CSymbol\"/>\n"
"      <annotation value=\"\" name=\"org.freedesktop.DBus.GLib.Async\"/>\n"
"      <arg direction=\"in\" tp:type=\"String_String_Variant_Map_Map\" type=\"a{sa{sv}}\" name=\"connection\">\n"
"        <annotation value=\"NMVariantMapMap\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"        <tp:docstring>\n"
"                    Nested settings maps containing the entire connection\n"
"                    (including secrets), for which the agent should save the\n"
"                    secrets to backing storage.  This method will not be called\n"
"                    when the agent itself is the process creating or updating\n"
"                    a connection; in that case the agent is assumed to have\n"
"                    already saved those secrets since it had them already.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"o\" name=\"connection_path\">\n"
"        <tp:docstring>\n"
"                    Object path of the connection for which the agent should\n"
"                    save secrets to backing storage.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"    </method>\n"
"    <method name=\"DeleteSecrets\">\n"
"      <tp:docstring>\n"
"                Delete secrets from backing storage.\n"
"            </tp:docstring>\n"
"      <annotation value=\"impl_secret_agent_delete_secrets\" name=\"org.freedesktop.DBus.GLib.CSymbol\"/>\n"
"      <annotation value=\"\" name=\"org.freedesktop.DBus.GLib.Async\"/>\n"
"      <arg direction=\"in\" tp:type=\"String_String_Variant_Map_Map\" type=\"a{sa{sv}}\" name=\"connection\">\n"
"        <annotation value=\"NMVariantMapMap\" name=\"org.qtproject.QtDBus.QtTypeName.In0\"/>\n"
"        <tp:docstring>\n"
"                    Nested settings maps containing the connection properties\n"
"                    (sans secrets), for which the agent should delete the\n"
"                    secrets from backing storage.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"      <arg direction=\"in\" type=\"o\" name=\"connection_path\">\n"
"        <tp:docstring>\n"
"                    Object path of the connection for which the agent should\n"
"                    delete secrets from backing storage.\n"
"                </tp:docstring>\n"
"      </arg>\n"
"    </method>\n"
"    <tp:flags value-prefix=\"NM_SECRET_AGENT_CAPABILITY\" type=\"u\" name=\"NM_SECRET_AGENT_CAPABILITIES\">\n"
"      <tp:flag suffix=\"NONE\" value=\"0x0\">\n"
"        <tp:docstring>No special capabilities.</tp:docstring>\n"
"      </tp:flag>\n"
"      <tp:flag suffix=\"VPN_HINTS\" value=\"0x1\">\n"
"        <tp:docstring>\n"
"                    The agent supports passing hints to VPN plugin authentication\n"
"                    dialogs.\n"
"                </tp:docstring>\n"
"      </tp:flag>\n"
"    </tp:flags>\n"
"  </interface>\n"
        "")
public:
    SecretAgentAdaptor(NetworkManager::SecretAgent *parent);
    virtual ~SecretAgentAdaptor();

    inline NetworkManager::SecretAgent *parent() const
    { return static_cast<NetworkManager::SecretAgent *>(QObject::parent()); }

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void CancelGetSecrets(const QDBusObjectPath &connection_path, const QString &setting_name);
    void DeleteSecrets(const NMVariantMapMap &connection, const QDBusObjectPath &connection_path);
    NMVariantMapMap GetSecrets(const NMVariantMapMap &connection, const QDBusObjectPath &connection_path, const QString &setting_name, const QStringList &hints, uint flags);
    void SaveSecrets(const NMVariantMapMap &connection, const QDBusObjectPath &connection_path);
Q_SIGNALS: // SIGNALS
};

#endif
