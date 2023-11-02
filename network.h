#ifndef CUTILE_NETWORK_H
#define CUTILE_NETWORK_H

#include "./num_types.h"

struct net_socket
{
    u32 handle;
};
#ifdef CUTILE_C
typedef struct net_socket net_socket;
#endif // CUTILE_C

enum net_socket_kind
{    
    net_socket_stream,
    net_socket_datagram
};

enum net_address_family
{
    net_af_ipv4,
    net_af_ipv6
};

enum net_protocol
{
    net_tcp_protocol,
    net_udp_protocol
};

enum net_error
{
    net_no_error = 0,

#ifdef _WIN32
    net_win32_wsa_not_ready,
    net_win32_wsa_not_initialized,              // WSAStartup() has not been called yet!
    net_win32_wsa_ver_not_supported,
    net_win32_wsa_busy,
    net_win32_wsa_invalid_data_address,
    net_win32_wsa_overloaded,
    net_win32_wsa_network_down,
    net_win32_wsa_unsupported_address_family,
    net_win32_wsa_unsupported_socket_type,
    net_win32_wsa_unsupported_protocol,
    net_win32_wsa_invalid_protocol,
    net_win32_wsa_too_much_opened_sockets,
    net_win32_wsa_invalid_argument,
    net_win32_wsa_invalid_service_provider,
    net_win32_wsa_invalid_service_provider_table,
    net_win32_wsa_service_provider_init_failed,
    net_win32_wsa_insufficient_buffer_space,
    net_win32_wsa_not_a_sock,
    net_win32_wsa_interrupted_call,
    net_win32_unavailable_resource,
    net_win32_wsa_permission_denied,
    net_win32_wsa_drop_conn_on_network_reset,
    net_win32_wsa_socket_not_connected,
#endif // _WIN32

    net_unknown_err
};

struct net_socket_options
{
    const char*         hostname;
    u16                 port;
    net_socket_kind     kind;
    net_address_family  address_family;
    net_protocol        protocol;
};
#ifdef CUTILE_C
typedef struct net_socket_options net_socket_options;
#endif // CUTILE_C
net_error  open_net_socket(net_socket_options* options, net_socket* out);
net_error  close_net_socket(net_socket socket);

net_error  send_to_net_socket(net_socket dest_socket, u8* data, u64 len);

const char* get_net_error_msg(net_error err);

// Calls WSAStartup and WSACleanup on Windows machines.
#ifdef _WIN32
struct wsa_startup_data { u8 maj; u8 min; };
#ifdef CUTILE_C
typedef struct wsa_startup_data wsa_startup_data;
#endif // CUTILE_C
net_error load_platform_net_library(void* data);
net_error unload_platform_net_library();
#else // !_WIN32
#define load_platform_net_library(data) net_no_error
#define unload_platform_net_library() net_no_error
#endif // _WIN32

#ifdef CUTILE_IMPLEM

#ifdef _WIN32
#include <winsock2.h>
#endif // _WIN32

net_error open_net_socket(net_socket_options* options, net_socket* out)
{
    int af = 0;
    int type = 0;
    int protocol = 0;

#ifdef _WIN32
    switch (options->address_family)
    {
    case net_af_ipv4: af = AF_INET;
    case net_af_ipv6: af = AF_INET6;
    }
    switch (options->kind)
    {
    case net_socket_stream: type = SOCK_STREAM;
    case net_socket_datagram: type = SOCK_DGRAM;
    }
    switch (options->protocol)
    {
    case net_tcp_protocol: protocol = IPPROTO_TCP;
    case net_udp_protocol: protocol = IPPROTO_UDP;
    }
#endif

    out->handle = socket(af, type, protocol);
    
#ifdef _WIN32
    if (out->handle == INVALID_SOCKET)
    {
        int err = WSAGetLastError();
        switch (err)
        {
        case WSANOTINITIALISED: return net_win32_wsa_not_initialized;
        case WSAENETDOWN: return net_win32_wsa_network_down;
        case WSAEAFNOSUPPORT: return net_win32_wsa_unsupported_address_family;
        case WSAEINPROGRESS: return net_win32_wsa_busy;
        case WSAEMFILE: return net_win32_wsa_too_much_opened_sockets;
        case WSAEINVAL: return net_win32_wsa_invalid_argument;
        case WSAEINVALIDPROVIDER: return net_win32_wsa_invalid_service_provider;
        case WSAEINVALIDPROCTABLE: return net_win32_wsa_invalid_service_provider_table;
        case WSAENOBUFS: return net_win32_wsa_insufficient_buffer_space;
        case WSAEPROTONOSUPPORT: return net_win32_wsa_unsupported_protocol;
        case WSAEPROTOTYPE: return net_win32_wsa_invalid_protocol;
        case WSAEPROVIDERFAILEDINIT: return net_win32_wsa_service_provider_init_failed;
        case WSAESOCKTNOSUPPORT: return net_win32_wsa_unsupported_socket_type;
        default: return net_unknown_err;
        }
    }
#endif // _WIN32
    return net_no_error;
}

net_error close_net_socket(net_socket socket)
{
#ifdef _WIN32
    if (closesocket(socket.handle) == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        switch (err)
        {
        case WSANOTINITIALISED: return net_win32_wsa_not_initialized;
        case WSAENETDOWN: return net_win32_wsa_network_down;
        case WSAENOTSOCK: return net_win32_wsa_not_a_sock;
        case WSAEINPROGRESS: return net_win32_wsa_busy;
        case WSAEINTR: return net_win32_wsa_interrupted_call;
        case WSAEWOULDBLOCK: return net_win32_unavailable_resource;
        default: return net_unknown_err;
        }
    }
#endif // _WIN32
    return net_no_error;
}

net_error send_to_net_socket(net_socket dest_socket, u8* data, u64 len)
{
#ifdef _WIN32
    u32 sent;
    u32 total = 0;
    while (total < len)
    {
        sent = send(dest_socket.handle, (char*)data, len, 0);
        if (sent == SOCKET_ERROR)
        {
            int err = WSAGetLastError();
            switch (err)
            {
            case WSANOTINITIALISED: return net_win32_wsa_not_initialized;
            case WSAENETDOWN: return net_win32_wsa_network_down;
            case WSAEACCES: return net_win32_wsa_permission_denied;
            case WSAEINTR: return net_win32_wsa_interrupted_call;
            case WSAEINPROGRESS: return net_win32_wsa_busy;
            case WSAEFAULT: return net_win32_wsa_invalid_data_address;
            case WSAENETRESET: return net_win32_wsa_drop_conn_on_network_reset;
            case WSAENOBUFS: return net_win32_wsa_insufficient_buffer_space;
            case WSAENOTCONN: return net_win32_wsa_socket_not_connected;
            case WSAENOTSOCK: return net_win32_wsa_not_a_sock;
            case WSAEWOULDBLOCK: return net_win32_unavailable_resource;
                // TODO: Handle other errors: https://learn.microsoft.com/fr-fr/windows/win32/api/winsock2/nf-winsock2-send
            default: return net_unknown_err;
            }
        }
        total += sent;
    }
#endif

    return net_no_error;
}

#ifdef _WIN32
net_error load_platform_net_library(void* data)
{
    wsa_startup_data* wsa_st_data = (wsa_startup_data*)data;
    WORD wsaVersion = MAKEWORD(wsa_st_data->maj, wsa_st_data->min);
    WSADATA wsaData;
    int err = WSAStartup(wsaVersion, &wsaData);
    switch (err)
    {
    case 0: return net_no_error;
    case WSASYSNOTREADY:
        return net_win32_wsa_not_ready;
    case WSAVERNOTSUPPORTED:
        return net_win32_wsa_ver_not_supported;
    case WSAEINPROGRESS:
        return net_win32_wsa_busy;
    case WSAEPROCLIM:
        return net_win32_wsa_overloaded;
    case WSAEFAULT:
        return net_win32_wsa_invalid_data_address;
    default: return net_unknown_err;
    }
}
net_error unload_platform_net_library()
{
    int err = WSACleanup();
    switch (err)
    {
    case 0: return net_no_error;
    case WSANOTINITIALISED: return net_win32_wsa_not_initialized;
    case WSAENETDOWN: return net_win32_wsa_network_down;
    case WSAEINPROGRESS: return net_win32_wsa_busy;
    default: return net_unknown_err;
    }
}
#endif // _WIN32

const char* get_net_error_msg(net_error err)
{
    switch (err)
    {
#ifdef _WIN32 // Error messages taken from: https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
    case net_win32_wsa_not_ready: return "The underlying network subsystem is not ready for network communication.";
    case net_win32_wsa_ver_not_supported: return "Winsock.dll version out of range. The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed.";
    case net_win32_wsa_busy: return "Operation now in progress. A blocking operation is currently executing. Windows Sockets only allows a single blocking operation—per- task or thread—to be outstanding, and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error.";
    case net_win32_wsa_invalid_data_address: return "Bad address. The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr).";
    case net_win32_wsa_overloaded: return "Too many processes. A Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously. WSAStartup may fail with this error if the limit has been reached.";
    case net_win32_wsa_network_down: return "Network is down. A socket operation encountered a dead network. This could indicate a serious failure of the network system (that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself."; 
    case net_win32_wsa_unsupported_address_family: return "Address family not supported by protocol family. An address incompatible with the requested protocol was used. All sockets are created with an associated address family (that is, AF_INET for Internet Protocols) and a generic protocol type (that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto.";
    case net_win32_wsa_unsupported_socket_type: return "Socket type not supported. The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all.";
    case net_win32_wsa_unsupported_protocol: return "Protocol not supported. The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol.";
    case net_win32_wsa_invalid_protocol: return "Protocol wrong type for socket. A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM.";
    case net_win32_wsa_too_much_opened_sockets: return "Too many open files. Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread.";
    case net_win32_wsa_invalid_argument: return "Invalid argument. Some invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening.";
    case net_win32_wsa_invalid_service_provider: return "Service provider is invalid. The requested service provider is invalid. This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found. This error is also returned if the service provider returned a version number other than 2.0.";
    case net_win32_wsa_invalid_service_provider_table: return "Procedure call table is invalid. The service provider procedure call table is invalid. A service provider returned a bogus procedure table to Ws2_32.dll. This is usually caused by one or more of the function pointers being NULL.";
    case net_win32_wsa_service_provider_init_failed: return "Service provider failed to initialize. The requested service provider could not be loaded or initialized. This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed.";
    case net_win32_wsa_insufficient_buffer_space: return "No buffer space available. An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";
    case net_win32_wsa_not_a_sock: return "Socket operation on nonsocket. An operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid.";
    case net_win32_wsa_interrupted_call: return "Interrupted function call. A blocking operation was interrupted by a call to WSACancelBlockingCall.";
    case net_win32_unavailable_resource: return "Resource temporarily unavailable. This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.";
    case net_win32_wsa_permission_denied: return "Permission denied. An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST). Another possible reason for the WSAEACCES error is that when the bind function is called (on Windows NT 4.0 with SP4 and later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4.0 with SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option.";
    case net_win32_wsa_drop_conn_on_network_reset: return "Network dropped connection on reset. The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed.";
    case net_win32_wsa_socket_not_connected: return "Socket is not connected. A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset.";
#endif // _WIN32
        
    case net_unknown_err: return "An unknown network error occurred.";
        
    default: return "";
    }
}

#endif // CUTILE_IMPLEM

#endif // !CUTILE_NETWORK_H
