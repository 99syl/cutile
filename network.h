#ifndef CUTILE_NETWORK_H

    #include "cxx.h"

    typedef struct
    {
        s32 handle;
    } cutile_net_socket;

    typedef enum
    {
        cutile_net_socket_stream,
        cutile_net_socket_datagram
    } cutile_net_socket_kind;

    typedef enum
    {
        cutile_net_af_ipv4,
        cutile_net_af_ipv6
    } cutile_net_address_family;

    typedef enum
    {
        cutile_net_tcp_protocol,
        cutile_net_udp_protocol
    } cutile_net_protocol;

    typedef enum
    {
        cutile_net_no_error = 0,
    
        #if WINDOWS
            cutile_net_win32_wsa_not_ready,
            cutile_net_win32_wsa_not_initialized,              // WSAStartup() has not been called yet!
            cutile_net_win32_wsa_ver_not_supported,
            cutile_net_win32_wsa_busy,
            cutile_net_win32_wsa_invalid_data_address,
            cutile_net_win32_wsa_overloaded,
            cutile_net_win32_wsa_network_down,
            cutile_net_win32_wsa_unsupported_address_family,
            cutile_net_win32_wsa_unsupported_socket_type,
            cutile_net_win32_wsa_unsupported_protocol,
            cutile_net_win32_wsa_invalid_protocol,
            cutile_net_win32_wsa_too_much_opened_sockets,
            cutile_net_win32_wsa_invalid_argument,
            cutile_net_win32_wsa_invalid_service_provider,
            cutile_net_win32_wsa_invalid_service_provider_table,
            cutile_net_win32_wsa_service_provider_init_failed,
            cutile_net_win32_wsa_insufficient_buffer_space,
            cutile_net_win32_wsa_not_a_sock,
            cutile_net_win32_wsa_interrupted_call,
            cutile_net_win32_unavailable_resource,
            cutile_net_win32_wsa_permission_denied,
            cutile_net_win32_wsa_drop_conn_on_network_reset,
            cutile_net_win32_wsa_socket_not_connected,
            cutile_net_win32_wsa_address_already_in_use,
            cutile_net_win32_wsa_invalid_address,
            cutile_net_win32_wsa_socket_already_connected,
            cutile_net_win32_wsa_unsupported_operation,

        #elif LINUX
            cutile_net_linux_open_socket_eacces,
            cutile_net_linux_open_socket_eafnosupport,
            cutile_net_linux_open_socket_einval,
            cutile_net_linux_open_socket_emfile,
            cutile_net_linux_open_socket_enfile,
            cutile_net_linux_open_socket_enobufs,
            cutile_net_linux_open_socket_enomem,
            cutile_net_linux_open_socket_eprotonosupport,
            cutile_net_linux_close_socket_ebadf,
            cutile_net_linux_close_socket_eintr,
            cutile_net_linux_close_socket_eio,
            cutile_net_linux_close_socket_enospc,
            cutile_net_linux_close_socket_edquot,
            cutile_net_linux_bind_socket_eacces,
            cutile_net_linux_bind_socket_eaddrinuse,
            cutile_net_linux_bind_socket_ebadf,
            cutile_net_linux_bind_socket_einval,
            cutile_net_linux_bind_socket_enotsock,
            cutile_net_linux_bind_socket_eaddrnotavail,
            cutile_net_linux_bind_socket_efault,
            cutile_net_linux_bind_socket_eloop,
            cutile_net_linux_bind_socket_enametoolong,
            cutile_net_linux_bind_socket_enoent,
            cutile_net_linux_bind_socket_enomem,
            cutile_net_linux_bind_socket_enotdir,
            cutile_net_linux_bind_socket_erofs,
            cutile_net_linux_socket_listen_eaddrinuse,
            cutile_net_linux_socket_listen_ebadf,
            cutile_net_linux_socket_listen_enotsock,
            cutile_net_linux_socket_listen_eopnotsupp,
            cutile_net_linux_send_to_socket_eacces,
            cutile_net_linux_send_to_socket_eagain_ewouldblock,
            cutile_net_linux_send_to_socket_ealready,
            cutile_net_linux_send_to_socket_ebadf,
            cutile_net_linux_send_to_socket_econnreset,
            cutile_net_linux_send_to_socket_edestaddrreq,
            cutile_net_linux_send_to_socket_efault,
            cutile_net_linux_send_to_socket_eintr,
            cutile_net_linux_send_to_socket_einval,
            cutile_net_linux_send_to_socket_eisconn,
            cutile_net_linux_send_to_socket_emsgsize,
            cutile_net_linux_send_to_socket_enobufs,
            cutile_net_linux_send_to_socket_enomem,
            cutile_net_linux_send_to_socket_enotconn,
            cutile_net_linux_send_to_socket_enotsock,
            cutile_net_linux_send_to_socket_eopnotsupp,
            cutile_net_linux_send_to_socket_epipe,
        #endif
        
        cutile_net_unknown_err
    } cutile_net_error;

    CUTILE_C_API cutile_net_error  cutile_open_net_socket(cutile_net_socket_kind kind, cutile_net_address_family family, cutile_net_protocol protocol, cutile_net_socket* out);
    CUTILE_C_API cutile_net_error  cutile_close_net_socket(cutile_net_socket* socket);
    
    // Net endpoints bytes are already ordered for network order if you created them using the helper functions below (e.g. cutile_create_ipv4_endpoint).

    typedef struct
    {
        cutile_net_address_family   family;
        u8                          data[32];
    } cutile_net_endpoint;
    
    typedef struct
    {
        cutile_net_address_family   family;
        u16                         port;
        u8                          bytes[4];
        u8                          zero[26];
    } cutile_ipv4_endpoint;
    
    typedef struct
    {
        cutile_net_address_family   family;
        u16                         port;
        union
        {
            u8                      bytes[16];
            u16                     words[8];        
        };
        u8                          zero[14];
    } cutile_ipv6_endpoint;
    
    CUTILE_C_API b8                     cutile_is_ipv4_cstr_valid(const char* ip);
    CUTILE_C_API cutile_ipv4_endpoint   cutile_create_ipv4_endpoint(const char* ip, u16 port);

    CUTILE_C_API cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_net_endpoint* endpoint);

    #ifdef CUTILE_CPP
        maybe_inline cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_ipv4_endpoint* endpoint);
        maybe_inline cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_ipv6_endpoint* endpoint);
    #endif
    
    CUTILE_C_API cutile_net_error cutile_net_socket_listen(cutile_net_socket* socket, u32 backlog);
    
    CUTILE_C_API cutile_net_error cutile_send_to_net_socket(cutile_net_socket* dest_socket, u8* data, u64 len);

    CUTILE_C_API const char* cutile_get_net_error_msg(cutile_net_error err);

    #ifndef NO_CUTILE_SHORT_INTERFACE_NAMES
        typedef cutile_net_socket net_socket;

        typedef cutile_net_socket_kind net_socket_kind;
        #define net_socket_stream cutile_net_socket_stream
        #define net_socket_datagram cutile_net_socket_datagram

        typedef cutile_net_address_family net_address_family;
        #define net_af_ipv4 = cutile_net_af_ipv4
        #define net_af_ipv6 = cutile_net_af_ipv6

        typedef cutile_net_protocol net_protocol;
        #define net_tcp_protocol cutile_net_tcp_protocol
        #define net_udp_protocol cutile_net_udp_protocol

        typedef cutile_net_error net_error;
        #define net_no_error                                     cutile_net_no_error
        #define net_unknown_err                                  cutile_net_unknown_err
        #if WINDOWS
            #define net_win32_wsa_not_ready                      cutile_net_win32_wsa_not_ready
            #define net_win32_wsa_not_initialized                cutile_net_win32_wsa_not_initialized
            #define net_win32_wsa_ver_not_supported              cutile_net_win32_wsa_ver_not_supported
            #define net_win32_wsa_busy                           cutile_net_win32_wsa_busy
            #define net_win32_wsa_invalid_data_address           cutile_net_win32_wsa_invalid_data_address
            #define net_win32_wsa_overloaded                     cutile_net_win32_wsa_overloaded
            #define net_win32_wsa_network_down                   cutile_net_win32_wsa_network_down
            #define net_win32_wsa_unsupported_address_family     cutile_net_win32_wsa_unsupported_address_family
            #define net_win32_wsa_unsupported_socket_type        cutile_net_win32_wsa_unsupported_socket_type
            #define net_win32_wsa_unsupported_protocol           cutile_net_win32_wsa_unsupported_protocol
            #define net_win32_wsa_invalid_protocol               cutile_net_win32_wsa_invalid_protocol
            #define net_win32_wsa_too_much_opened_sockets        cutile_net_win32_wsa_too_much_opened_sockets
            #define net_win32_wsa_invalid_argument               cutile_net_win32_wsa_invalid_argument
            #define net_win32_wsa_invalid_service_provider       cutile_net_win32_wsa_invalid_service_provider
            #define net_win32_wsa_invalid_service_provider_table cutile_net_win32_wsa_invalid_service_provider_table
            #define net_win32_wsa_service_provider_init_failed   cutile_net_win32_wsa_service_provider_init_failed
            #define net_win32_wsa_insufficient_buffer_space      cutile_net_win32_wsa_insufficient_buffer_space
            #define net_win32_wsa_not_a_sock                     cutile_net_win32_wsa_not_a_sock
            #define net_win32_wsa_interrupted_call               cutile_net_win32_wsa_interrupted_call
            #define net_win32_unavailable_resource               cutile_net_win32_unavailable_resource
            #define net_win32_wsa_permission_denied              cutile_net_win32_wsa_permission_denied
            #define net_win32_wsa_drop_conn_on_network_reset     cutile_net_win32_wsa_drop_conn_on_network_reset
            #define net_win32_wsa_socket_not_connected           cutile_net_win32_wsa_socket_not_connected
            #define net_win32_wsa_address_already_in_use         cutile_net_win32_wsa_address_already_in_use
            #define net_win32_wsa_invalid_address                cutile_net_win32_wsa_invalid_address
            #define net_win32_wsa_socket_already_connected       cutile_net_win32_wsa_socket_already_connected
            #define net_win32_wsa_unsupported_operation          cutile_net_win32_wsa_unsupported_operation
        #elif LINUX
            #define net_linux_open_socket_eacces                cutile_net_linux_open_socket_eacces                 
            #define net_linux_open_socket_eafnosupport          cutile_net_linux_open_socket_eafnosupport         
            #define net_linux_open_socket_einval                cutile_net_linux_open_socket_einval               
            #define net_linux_open_socket_emfile                cutile_net_linux_open_socket_emfile               
            #define net_linux_open_socket_enfile                cutile_net_linux_open_socket_enfile               
            #define net_linux_open_socket_enobufs               cutile_net_linux_open_socket_enobufs              
            #define net_linux_open_socket_enomem                cutile_net_linux_open_socket_enomem               
            #define net_linux_open_socket_eprotonosupport       cutile_net_linux_open_socket_eprotonosupport      
            #define net_linux_close_socket_ebadf                cutile_net_linux_close_socket_ebadf               
            #define net_linux_close_socket_eintr                cutile_net_linux_close_socket_eintr               
            #define net_linux_close_socket_eio                  cutile_net_linux_close_socket_eio                 
            #define net_linux_close_socket_enospc               cutile_net_linux_close_socket_enospc              
            #define net_linux_close_socket_edquot               cutile_net_linux_close_socket_edquot              
            #define net_linux_bind_socket_eacces                cutile_net_linux_bind_socket_eacces               
            #define net_linux_bind_socket_eaddrinuse            cutile_net_linux_bind_socket_eaddrinuse           
            #define net_linux_bind_socket_ebadf                 cutile_net_linux_bind_socket_ebadf                
            #define net_linux_bind_socket_einval                cutile_net_linux_bind_socket_einval               
            #define net_linux_bind_socket_enotsock              cutile_net_linux_bind_socket_enotsock             
            #define net_linux_bind_socket_eaddrnotavail         cutile_net_linux_bind_socket_eaddrnotavail        
            #define net_linux_bind_socket_efault                cutile_net_linux_bind_socket_efault               
            #define net_linux_bind_socket_eloop                 cutile_net_linux_bind_socket_eloop                
            #define net_linux_bind_socket_enametoolong          cutile_net_linux_bind_socket_enametoolong         
            #define net_linux_bind_socket_enoent                cutile_net_linux_bind_socket_enoent               
            #define net_linux_bind_socket_enomem                cutile_net_linux_bind_socket_enomem               
            #define net_linux_bind_socket_enotdir               cutile_net_linux_bind_socket_enotdir              
            #define net_linux_bind_socket_erofs                 cutile_net_linux_bind_socket_erofs                
            #define net_linux_socket_listen_eaddrinuse          cutile_net_linux_socket_listen_eaddrinuse         
            #define net_linux_socket_listen_ebadf               cutile_net_linux_socket_listen_ebadf              
            #define net_linux_socket_listen_enotsock            cutile_net_linux_socket_listen_enotsock           
            #define net_linux_socket_listen_eopnotsupp          cutile_net_linux_socket_listen_eopnotsupp         
            #define net_linux_send_to_socket_eacces             cutile_net_linux_send_to_socket_eacces            
            #define net_linux_send_to_socket_eagain_ewouldblock cutile_net_linux_send_to_socket_eagain_ewouldblock
            #define net_linux_send_to_socket_ealready           cutile_net_linux_send_to_socket_ealready          
            #define net_linux_send_to_socket_ebadf              cutile_net_linux_send_to_socket_ebadf             
            #define net_linux_send_to_socket_econnreset         cutile_net_linux_send_to_socket_econnreset        
            #define net_linux_send_to_socket_edestaddrreq       cutile_net_linux_send_to_socket_edestaddrreq      
            #define net_linux_send_to_socket_efault             cutile_net_linux_send_to_socket_efault            
            #define net_linux_send_to_socket_eintr              cutile_net_linux_send_to_socket_eintr             
            #define net_linux_send_to_socket_einval             cutile_net_linux_send_to_socket_einval            
            #define net_linux_send_to_socket_eisconn            cutile_net_linux_send_to_socket_eisconn           
            #define net_linux_send_to_socket_emsgsize           cutile_net_linux_send_to_socket_emsgsize          
            #define net_linux_send_to_socket_enobufs            cutile_net_linux_send_to_socket_enobufs           
            #define net_linux_send_to_socket_enomem             cutile_net_linux_send_to_socket_enomem            
            #define net_linux_send_to_socket_enotconn           cutile_net_linux_send_to_socket_enotconn          
            #define net_linux_send_to_socket_enotsock           cutile_net_linux_send_to_socket_enotsock          
            #define net_linux_send_to_socket_eopnotsupp         cutile_net_linux_send_to_socket_eopnotsupp        
            #define net_linux_send_to_socket_epipe              cutile_net_linux_send_to_socket_epipe             
        #endif

        #define open_net_socket(kind, family, protocol, out) cutile_open_net_socket(kind, family, protocol, out)
        #define close_net_socket(socket)                     cutile_close_net_socket(socket)

        typedef cutile_net_endpoint  net_endpoint;
        typedef cutile_ipv4_endpoint ipv4_endpoint;
        typedef cutile_ipv6_endpoint ipv6_endpoint;

        #define is_ipv4_cstr_valid(ip)              cutile_is_ipv4_cstr_valid(ip)
        #define create_ipv4_endpoint(ip_cstr, port) cutile_create_ipv4_endpoint(ip_cstr, port)

        #define bind_net_socket(socket, endpoint) cutile_bind_net_socket(socket, endpoint)

        #define net_socket_listen(socket, backlog)      cutile_net_socket_listen(socket, backlog)
        #define send_to_net_socket(socket, data, len)   cutile_send_to_net_socket(socket, data, len)

        #define get_net_error_msg(err)                  cutile_get_net_error_msg(err)
    #endif
    
    #ifdef CUTILE_IMPLEM
    
        #if WINDOWS
            #include <winsock2.h>
            #include <Ws2tcpip.h>
            #ifdef _MSC_VER
                #pragma comment(lib, "Ws2_32.lib")
            #endif
        #elif LINUX
            #include <errno.h>
            #include <sys/socket.h>
            #include <arpa/inet.h>
            #include <unistd.h>
        #else
            #error "socket.h: Unsupported platform."
        #endif

        cutile_net_error cutile_open_net_socket(cutile_net_socket_kind kind, cutile_net_address_family family, cutile_net_protocol protocol, cutile_net_socket* out)
        {
            int af = 0;
            int type = 0;
            int proto = 0;

            #if WINDOWS
                switch (family)
                {
                    case cutile_net_af_ipv4: af = AF_INET; break;
                    case cutile_net_af_ipv6: af = AF_INET6; break;
                }
                switch (kind)
                {
                    case cutile_net_socket_stream: type = SOCK_STREAM; break;
                    case cutile_net_socket_datagram: type = SOCK_DGRAM; break;
                }
                switch (protocol)
                {
                    case cutile_net_tcp_protocol: proto = IPPROTO_TCP; break;
                    case cutile_net_udp_protocol: proto = IPPROTO_UDP; break;
                }
            #elif UNIX_LIKE
                switch (family)
                {
                    case cutile_net_af_ipv4: af = AF_INET; break;
                    case cutile_net_af_ipv6: af = AF_INET6; break;
                }
                switch (kind)
                {
                    case cutile_net_socket_stream: type = SOCK_STREAM; break;
                    case cutile_net_socket_datagram: type = SOCK_DGRAM; break;
                }
                proto = 0;
            #endif

            out->handle = socket(af, type, protocol);

            #if WINDOWS
                if (out->handle == INVALID_SOCKET)
                {
                    int err = WSAGetLastError();
                    switch (err)
                    {
                        case WSANOTINITIALISED: return cutile_net_win32_wsa_not_initialized;
                        case WSAENETDOWN: return cutile_net_win32_wsa_network_down;
                        case WSAEAFNOSUPPORT: return cutile_net_win32_wsa_unsupported_address_family;
                        case WSAEINPROGRESS: return cutile_net_win32_wsa_busy;
                        case WSAEMFILE: return cutile_net_win32_wsa_too_much_opened_sockets;
                        case WSAEINVAL: return cutile_net_win32_wsa_invalid_argument;
                        case WSAEINVALIDPROVIDER: return cutile_net_win32_wsa_invalid_service_provider;
                        case WSAEINVALIDPROCTABLE: return cutile_net_win32_wsa_invalid_service_provider_table;
                        case WSAENOBUFS: return cutile_net_win32_wsa_insufficient_buffer_space;
                        case WSAEPROTONOSUPPORT: return cutile_net_win32_wsa_unsupported_protocol;
                        case WSAEPROTOTYPE: return cutile_net_win32_wsa_invalid_protocol;
                        case WSAEPROVIDERFAILEDINIT: return cutile_net_win32_wsa_service_provider_init_failed;
                        case WSAESOCKTNOSUPPORT: return cutile_net_win32_wsa_unsupported_socket_type;
                        default: return cutile_net_unknown_err;
                    }
                }
            #elif LINUX
                if (out->handle == -1)
                {
                    switch (errno)
                    {
                        case EACCES: return cutile_net_linux_open_socket_eacces;
                        case EAFNOSUPPORT: return cutile_net_linux_open_socket_eafnosupport;
                        case EINVAL: return cutile_net_linux_open_socket_einval;
                        case EMFILE: return cutile_net_linux_open_socket_emfile;
                        case ENFILE: return cutile_net_linux_open_socket_enfile;
                        case ENOBUFS: return cutile_net_linux_open_socket_enobufs;
                        case ENOMEM: return cutile_net_linux_open_socket_enomem;
                        case EPROTONOSUPPORT: return cutile_net_linux_open_socket_eprotonosupport;
                        default: return cutile_net_unknown_err;
                    }
                }
            #endif

            return cutile_net_no_error;
        }

        cutile_net_error cutile_close_net_socket(cutile_net_socket* socket)
        {
            #if WINDOWS
                if (closesocket(socket->handle) == SOCKET_ERROR)
                {
                    int err = WSAGetLastError();
                    switch (err)
                    {
                        case WSANOTINITIALISED: return cutile_net_win32_wsa_not_initialized;
                        case WSAENETDOWN: return cutile_net_win32_wsa_network_down;
                        case WSAENOTSOCK: return cutile_net_win32_wsa_not_a_sock;
                        case WSAEINPROGRESS: return cutile_net_win32_wsa_busy;
                        case WSAEINTR: return cutile_net_win32_wsa_interrupted_call;
                        case WSAEWOULDBLOCK: return cutile_net_win32_unavailable_resource;
                        default: return cutile_net_unknown_err;
                    }
                }
            #elif LINUX
                if (close(socket->handle) == -1)
                {
                    switch (errno)
                    {
                        case EBADF: return cutile_net_linux_close_socket_ebadf;
                        case EINTR: return cutile_net_linux_close_socket_eintr;
                        case EIO: return cutile_net_linux_close_socket_eio;
                        case ENOSPC: return cutile_net_linux_close_socket_enospc;
                        case EDQUOT: return cutile_net_linux_close_socket_edquot;
                        default: return cutile_net_unknown_err;
                    }
                }
            #endif

            return cutile_net_no_error;
        }

        b8 cutile_is_ipv4_cstr_valid(const char* ip)
        {
            u32 byte = 0;
            u8  sep_count = 0;
            for (u32 i = 0; ip[i]; ++i)
            {
                char c = ip[i];
                if (c == '.')
                {
                    ++sep_count;
                    if (sep_count > 3) return b8_false;
                    if (byte > 255) return b8_false;
                    byte = 0;
                }
                else if (c >= '0' && c <= '9')
                {
                    byte *= 10;
                    byte += c - '0';
                }
                else return b8_false;
            }
            if (byte > 255) return b8_false;
            if (sep_count != 3) return b8_false;
            return b8_true;
        }

        cutile_ipv4_endpoint cutile_create_ipv4_endpoint(const char* ip, u16 port)
        {
            cutile_ipv4_endpoint endp;
            endp.family = cutile_net_af_ipv4;
            u8 byte = 0;
            u32 byte_index = 0;
            for (u32 i = 0; ip[i]; ++i)
            {
                char c = ip[i];
                if (c >= '0' && c <= '9')
                {
                    byte *= 10;
                    byte += c - '0';
                }
                else if (c == '.')
                {
                    endp.bytes[byte_index++] = byte;
                    byte = 0;
                }
            }
            endp.bytes[byte_index] = byte;
            endp.port = port;
            return endp;
        }

        cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_net_endpoint* endpoint)
        {
            int res;
            switch (endpoint->family)
            {
                case cutile_net_af_ipv4:
                {
                    struct sockaddr_in addr;
                    ipv4_endpoint* v4_ep = (ipv4_endpoint*)endpoint;
                    addr.sin_family = AF_INET;
                    addr.sin_port = htons(v4_ep->port);
                    #if WINDOWS
                        addr.sin_addr.S_un.S_un_b.s_b1 = v4_ep->bytes[0];
                        addr.sin_addr.S_un.S_un_b.s_b2 = v4_ep->bytes[1];
                        addr.sin_addr.S_un.S_un_b.s_b3 = v4_ep->bytes[2];
                        addr.sin_addr.S_un.S_un_b.s_b4 = v4_ep->bytes[3];
                    #elif LINUX
                        u32 ip_bytes = (u32)*v4_ep->bytes;
                        addr.sin_addr.s_addr = ip_bytes;
                    #endif
                    res = bind(socket->handle, (struct sockaddr*)&addr, sizeof(addr));
                    break;
                }
                case cutile_net_af_ipv6:
                {
                    struct sockaddr_in6 addr;
                    ipv6_endpoint* v6_ep = (ipv6_endpoint*)endpoint;
                    addr.sin6_family = AF_INET6;
                    addr.sin6_scope_id = 0;
                    addr.sin6_port = htons(v6_ep->port);
                    #if WINDOWS
                        addr.sin6_addr.u.Byte[0] = v6_ep->bytes[0];
                        addr.sin6_addr.u.Byte[1] = v6_ep->bytes[1];
                        addr.sin6_addr.u.Byte[2] = v6_ep->bytes[2];
                        addr.sin6_addr.u.Byte[3] = v6_ep->bytes[3];
                        addr.sin6_addr.u.Byte[4] = v6_ep->bytes[4];
                        addr.sin6_addr.u.Byte[5] = v6_ep->bytes[5];
                        addr.sin6_addr.u.Byte[6] = v6_ep->bytes[6];
                        addr.sin6_addr.u.Byte[7] = v6_ep->bytes[7];
                        addr.sin6_addr.u.Byte[8] = v6_ep->bytes[8];
                        addr.sin6_addr.u.Byte[9] = v6_ep->bytes[9];
                        addr.sin6_addr.u.Byte[10] = v6_ep->bytes[10];
                        addr.sin6_addr.u.Byte[11] = v6_ep->bytes[11];
                        addr.sin6_addr.u.Byte[12] = v6_ep->bytes[12];
                        addr.sin6_addr.u.Byte[13] = v6_ep->bytes[13];
                        addr.sin6_addr.u.Byte[14] = v6_ep->bytes[14];
                        addr.sin6_addr.u.Byte[15] = v6_ep->bytes[15];
                    #elif LINUX
                        addr.sin6_addr.s6_addr[0] = v6_ep->bytes[0];
                        addr.sin6_addr.s6_addr[1] = v6_ep->bytes[1];
                        addr.sin6_addr.s6_addr[2] = v6_ep->bytes[2];
                        addr.sin6_addr.s6_addr[3] = v6_ep->bytes[3];
                        addr.sin6_addr.s6_addr[4] = v6_ep->bytes[4];
                        addr.sin6_addr.s6_addr[5] = v6_ep->bytes[5];
                        addr.sin6_addr.s6_addr[6] = v6_ep->bytes[6];
                        addr.sin6_addr.s6_addr[7] = v6_ep->bytes[7];
                        addr.sin6_addr.s6_addr[8] = v6_ep->bytes[8];
                        addr.sin6_addr.s6_addr[9] = v6_ep->bytes[9];
                        addr.sin6_addr.s6_addr[10] = v6_ep->bytes[10];
                        addr.sin6_addr.s6_addr[11] = v6_ep->bytes[11];
                        addr.sin6_addr.s6_addr[12] = v6_ep->bytes[12];
                        addr.sin6_addr.s6_addr[13] = v6_ep->bytes[13];
                        addr.sin6_addr.s6_addr[14] = v6_ep->bytes[14];
                        addr.sin6_addr.s6_addr[15] = v6_ep->bytes[15];
                    #endif
                    res = bind(socket->handle, (struct sockaddr*)&addr, sizeof(addr));
                    break;
                }
            }

            #if WINDOWS
                if (res == SOCKET_ERROR)
                {
                    int err = WSAGetLastError();
                    switch (err)
                    {
                        case WSANOTINITIALISED:
                            return cutile_net_win32_wsa_not_initialized;
                        case WSAENETDOWN:
                            return cutile_net_win32_wsa_network_down;
                        case WSAEACCES:
                            return cutile_net_win32_wsa_permission_denied;
                        case WSAEADDRINUSE:
                            return cutile_net_win32_wsa_address_already_in_use;
                        case WSAEADDRNOTAVAIL:
                            return cutile_net_win32_wsa_invalid_address;
                        case WSAEFAULT:
                            return cutile_net_win32_wsa_invalid_data_address;
                        case WSAEINPROGRESS:
                            return cutile_net_win32_wsa_busy;
                        case WSAEINVAL:
                            return cutile_net_win32_wsa_invalid_argument;
                        case WSAENOBUFS:
                            return cutile_net_win32_wsa_insufficient_buffer_space;
                        case WSAENOTSOCK:
                            return cutile_net_win32_wsa_not_a_sock;
                        default:
                            return cutile_net_unknown_err;
                    }
                }
            #elif LINUX
                if (res == -1)
                {
                    switch (errno)
                    {
                        case EACCES:        return cutile_net_linux_bind_socket_eacces;
                        case EADDRINUSE:    return cutile_net_linux_bind_socket_eaddrinuse;
                        case EBADF:         return cutile_net_linux_bind_socket_ebadf;
                        case EINVAL:        return cutile_net_linux_bind_socket_einval;
                        case ENOTSOCK:      return cutile_net_linux_bind_socket_enotsock;
                        case EADDRNOTAVAIL: return cutile_net_linux_bind_socket_eaddrnotavail;
                        case EFAULT:        return cutile_net_linux_bind_socket_efault;
                        case ELOOP:         return cutile_net_linux_bind_socket_eloop;
                        case ENAMETOOLONG:  return cutile_net_linux_bind_socket_enametoolong;
                        case ENOENT:        return cutile_net_linux_bind_socket_enoent;
                        case ENOMEM:        return cutile_net_linux_bind_socket_enomem;
                        case ENOTDIR:       return cutile_net_linux_bind_socket_enotdir;
                        case EROFS:         return cutile_net_linux_bind_socket_erofs;
                        default:            return cutile_net_unknown_err;
                    }
                }
            #endif
            
            return cutile_net_no_error;
        }

        cutile_net_error cutile_net_socket_listen(cutile_net_socket* socket, u32 backlog)
        {
            int res = listen(socket->handle, backlog);

            #if WINDOWS
                if (res == SOCKET_ERROR)
                {
                    int err = WSAGetLastError();
                    switch (err)
                    {
                        case WSANOTINITIALISED:
                            return cutile_net_win32_wsa_not_initialized;
                        case WSAENETDOWN:
                            return cutile_net_win32_wsa_network_down;
                        case WSAEADDRINUSE:
                            return cutile_net_win32_wsa_address_already_in_use;
                        case WSAEINPROGRESS:
                            return cutile_net_win32_wsa_busy;
                        case WSAEINVAL:
                            return cutile_net_win32_wsa_invalid_argument;
                        case WSAEISCONN:
                            return cutile_net_win32_wsa_socket_already_connected;
                        case WSAEMFILE:
                            return cutile_net_win32_wsa_too_much_opened_sockets;
                        case WSAENOBUFS:
                            return cutile_net_win32_wsa_insufficient_buffer_space;
                        case WSAENOTSOCK:
                            return cutile_net_win32_wsa_not_a_sock;
                        case WSAEOPNOTSUPP:
                            return cutile_net_win32_wsa_unsupported_operation;
                        default:
                            return cutile_net_unknown_err;
                    }
                }
            #elif LINUX
                if (res == -1)
                {
                    switch (errno)
                    {
                        case EADDRINUSE: return cutile_net_linux_socket_listen_eaddrinuse;
                        case EBADF:      return cutile_net_linux_socket_listen_ebadf;     
                        case ENOTSOCK:   return cutile_net_linux_socket_listen_enotsock;  
                        case EOPNOTSUPP: return cutile_net_linux_socket_listen_eopnotsupp;
                        default:         return cutile_net_unknown_err;
                    }
                }
            #endif
            return cutile_net_no_error;
        }

        cutile_net_error cutile_send_to_net_socket(cutile_net_socket* dest_socket, u8* data, u64 len)
        {
            s32 sent;
            s32 total = 0;
            while (total < len)
            {
                sent = send(dest_socket->handle, (char*)data + total, len - total, 0);
                #if WINDOWS
                    if (sent == SOCKET_ERROR)
                    {
                        int err = WSAGetLastError();
                        switch (err)
                        {
                            case WSANOTINITIALISED: return cutile_net_win32_wsa_not_initialized;
                            case WSAENETDOWN: return cutile_net_win32_wsa_network_down;
                            case WSAEACCES: return cutile_net_win32_wsa_permission_denied;
                            case WSAEINTR: return cutile_net_win32_wsa_interrupted_call;
                            case WSAEINPROGRESS: return cutile_net_win32_wsa_busy;
                            case WSAEFAULT: return cutile_net_win32_wsa_invalid_data_address;
                            case WSAENETRESET: return cutile_net_win32_wsa_drop_conn_on_network_reset;
                            case WSAENOBUFS: return cutile_net_win32_wsa_insufficient_buffer_space;
                            case WSAENOTCONN: return cutile_net_win32_wsa_socket_not_connected;
                            case WSAENOTSOCK: return cutile_net_win32_wsa_not_a_sock;
                            case WSAEWOULDBLOCK: return cutile_net_win32_unavailable_resource;
                            // TODO: Handle other errors: https://learn.microsoft.com/fr-fr/windows/win32/api/winsock2/nf-winsock2-send
                            default: return cutile_net_unknown_err;
                        }
                    }
                #elif LINUX
                    if (sent == -1)
                    {
                        switch (errno)
                        {
                            case EACCES:      return cutile_net_linux_send_to_socket_eacces;
     
                            case EAGAIN:      return cutile_net_linux_send_to_socket_eagain_ewouldblock;
                            // same as EAGAIN case EWOULDBLOCK: return cutile_net_linux_send_to_socket_ewouldblock;

                            case EALREADY:    return cutile_net_linux_send_to_socket_ealready;   
                            case EBADF:       return cutile_net_linux_send_to_socket_ebadf;      
                            case ECONNRESET:  return cutile_net_linux_send_to_socket_econnreset; 
                            case EDESTADDRREQ: return cutile_net_linux_send_to_socket_edestaddrreq;
                            case EFAULT:      return cutile_net_linux_send_to_socket_efault;     
                            case EINTR:       return cutile_net_linux_send_to_socket_eintr;      
                            case EINVAL:      return cutile_net_linux_send_to_socket_einval;     
                            case EISCONN:     return cutile_net_linux_send_to_socket_eisconn;    
                            case EMSGSIZE:    return cutile_net_linux_send_to_socket_emsgsize;   
                            case ENOBUFS:     return cutile_net_linux_send_to_socket_enobufs;    
                            case ENOMEM:      return cutile_net_linux_send_to_socket_enomem;     
                            case ENOTCONN:    return cutile_net_linux_send_to_socket_enotconn;   
                            case ENOTSOCK:    return cutile_net_linux_send_to_socket_enotsock;   
                            case EOPNOTSUPP:  return cutile_net_linux_send_to_socket_eopnotsupp; 
                            case EPIPE:       return cutile_net_linux_send_to_socket_epipe;      
                        }
                    }
                #endif
                total += sent;
            }

            return cutile_net_no_error;
        }

        const char* cutile_get_net_error_msg(cutile_net_error err)
        {
            switch (err)
            {
                #if WINDOWS // Error messages taken from: https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
                    case cutile_net_win32_wsa_not_ready: return "The underlying network subsystem is not ready for network communication.";
                    case cutile_net_win32_wsa_ver_not_supported: return "Winsock.dll version out of range. The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed.";
                    case cutile_net_win32_wsa_busy: return "Operation now in progress. A blocking operation is currently executing. Windows Sockets only allows a single blocking operation—per- task or thread—to be outstanding, and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error.";
                    case cutile_net_win32_wsa_invalid_data_address: return "Bad address. The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr).";
                    case cutile_net_win32_wsa_overloaded: return "Too many processes. A Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously. WSAStartup may fail with this error if the limit has been reached.";
                    case cutile_net_win32_wsa_network_down: return "Network is down. A socket operation encountered a dead network. This could indicate a serious failure of the network system (that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself."; 
                    case cutile_net_win32_wsa_unsupported_address_family: return "Address family not supported by protocol family. An address incompatible with the requested protocol was used. All sockets are created with an associated address family (that is, AF_INET for Internet Protocols) and a generic protocol type (that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto.";
                    case cutile_net_win32_wsa_unsupported_socket_type: return "Socket type not supported. The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all.";
                    case cutile_net_win32_wsa_unsupported_protocol: return "Protocol not supported. The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol.";
                    case cutile_net_win32_wsa_invalid_protocol: return "Protocol wrong type for socket. A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM.";
                    case cutile_net_win32_wsa_too_much_opened_sockets: return "Too many open files. Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread.";
                    case cutile_net_win32_wsa_invalid_argument: return "Invalid argument. Some invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening.";
                    case cutile_net_win32_wsa_invalid_service_provider: return "Service provider is invalid. The requested service provider is invalid. This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found. This error is also returned if the service provider returned a version number other than 2.0.";
                    case cutile_net_win32_wsa_invalid_service_provider_table: return "Procedure call table is invalid. The service provider procedure call table is invalid. A service provider returned a bogus procedure table to Ws2_32.dll. This is usually caused by one or more of the function pointers being NULL.";
                    case cutile_net_win32_wsa_service_provider_init_failed: return "Service provider failed to initialize. The requested service provider could not be loaded or initialized. This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed.";
                    case cutile_net_win32_wsa_insufficient_buffer_space: return "No buffer space available. An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";
                    case cutile_net_win32_wsa_not_a_sock: return "Socket operation on nonsocket. An operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid.";
                    case cutile_net_win32_wsa_interrupted_call: return "Interrupted function call. A blocking operation was interrupted by a call to WSACancelBlockingCall.";
                    case cutile_net_win32_unavailable_resource: return "Resource temporarily unavailable. This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.";
                    case cutile_net_win32_wsa_permission_denied: return "Permission denied. An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST). Another possible reason for the WSAEACCES error is that when the bind function is called (on Windows NT 4.0 with SP4 and later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4.0 with SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option.";
                    case cutile_net_win32_wsa_drop_conn_on_network_reset: return "Network dropped connection on reset. The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed.";
                    case cutile_net_win32_wsa_socket_not_connected: return "Socket is not connected. A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset.";
                    case cutile_net_win32_wsa_address_already_in_use: return "Address already in use. Typically, only one usage of each socket address (protocol/IP address/port) is permitted. This error occurs if an application attempts to bind a socket to an IP address/port that has already been used for an existing socket, or a socket that was not closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt (SO_REUSEADDR). Client applications usually need not call bind at all—connect chooses an unused port automatically. When bind is called with a wildcard address (involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is committed. This could happen with a call to another function later, including connect, listen, WSAConnect, or WSAJoinLeaf.";
                    case cutile_net_win32_wsa_invalid_address: return "Cannot assign requested address. The requested address is not valid in its context. This normally results from an attempt to bind to an address that is not valid for the local computer. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote computer (for example, address or port 0).";
                    case cutile_net_win32_wsa_socket_already_connected: return "Socket is already connected. A connect request was made on an already-connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket (for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence.";
                    case cutile_net_win32_wsa_unsupported_operation: return "Operation not supported. The attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation is trying to accept a connection on a datagram socket.";

                #elif LINUX
                    case cutile_net_linux_open_socket_eacces: return "EACCES: Permission to create a socket of the specified type and/or protocol is denied.";
                    case cutile_net_linux_open_socket_eafnosupport: return "EAFNOSUPPORT: The implementation does not support the specified address family.";
                    case cutile_net_linux_open_socket_einval: return "EINVAL: Unknown protocol, or protocol family not available / Invalid flags in type.";
                    case cutile_net_linux_open_socket_emfile: return "EMFILE: The per-process limit on the number of open file descriptors has been reached.";
                    case cutile_net_linux_open_socket_enfile: return "ENFILE: The system-wide limit on the total number of open files has been reached.";
                    case cutile_net_linux_open_socket_enobufs:
                    case cutile_net_linux_open_socket_enomem:
                        return "ENOBUFS or ENOMEM: Insufficient memory is available.  The socket cannot be created until sufficient  resources are freed.";
                    case cutile_net_linux_open_socket_eprotonosupport: return "PROTONOSUPPORT: The protocol type or the specified protocol is not supported within this domain.";
                    case cutile_net_linux_close_socket_ebadf: return "EBADF: fd isn’t a valid open file descriptor.";
                    case cutile_net_linux_close_socket_eintr: return "EINTR: The close() call was interrupted by a signal; see signal(7).";
                    case cutile_net_linux_close_socket_eio: return "EIO: An I/O error occurred.";
                    case cutile_net_linux_close_socket_enospc:
                    case cutile_net_linux_close_socket_edquot: 
                        return "ENOSPC or EDQUOT: On  NFS, these errors are not normally reported against the first write which exceeds the available storage space, but instead against a subsequent write(2), fsync(2), or close().";
                    case cutile_net_linux_bind_socket_eacces: return "EACCES:\n\t- The address is protected, and the user is not the superuser.\n\t- UNIX domain (AF_UNIX) sockets: Search permission is denied on a component of the path prefix.  (See also path_resolution(7).)";
                    case cutile_net_linux_bind_socket_eaddrinuse: return "EADDRINUSE: The given address is already in use. / (Internet domain sockets) The port number was specified as zero in the socket address structure, but, upon attempting to bind to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use. See the discussion of /proc/sys/net/ipv4/ip_local_port_range ip(7).";
                    case cutile_net_linux_bind_socket_ebadf: return "EBADF: sockfd is not a valid file descriptor.";
                    case cutile_net_linux_bind_socket_einval: return "EINVAL: The socket is already bound to an address. / addrlen is wrong, or addr is not a valid address for this socket’s domain.";
                    case cutile_net_linux_bind_socket_enotsock: return "ENOTSOCK: The file descriptor sockfd does not refer to a socket.";
                    case cutile_net_linux_bind_socket_eaddrnotavail: return "EADDRNOTAVAIL: UNIX domain (AF_UNIX) sockets: A nonexistent interface was requested or the requested address was not local.";
                    case cutile_net_linux_bind_socket_efault: return "UNIX domain (AF_UNIX) sockets: EFAULT: addr points outside the user’s accessible address space.";
                    case cutile_net_linux_bind_socket_eloop: return "UNIX domain (AF_UNIX) sockets: ELOOP: Too many symbolic links were encountered in resolving addr.";
                    case cutile_net_linux_bind_socket_enametoolong: return "UNIX domain (AF_UNIX) sockets: ENAMETOOLONG: addr is too long.";
                    case cutile_net_linux_bind_socket_enoent: return "UNIX domain (AF_UNIX) sockets: ENOENT: A component in the directory prefix of the socket pathname does not exist.";
                    case cutile_net_linux_bind_socket_enomem: return "UNIX domain (AF_UNIX) sockets: ENOMEM: Insufficient kernel memory was available.";
                    case cutile_net_linux_bind_socket_enotdir: return "UNIX domain (AF_UNIX) sockets: ENOTDIR: A component of the path prefix is not a directory.";
                    case cutile_net_linux_bind_socket_erofs: return "UNIX domain (AF_UNIX) sockets: EROFS: The socket inode would reside on a read-only filesystem.";
                    case cutile_net_linux_socket_listen_eaddrinuse: return "EADDRINUSE:\n\t- Another socket is already listening on the same port.\n\t- Internet domain sockets) The socket referred to by sockfd had  not  previously  been bound  to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use. See the discussion of /proc/sys/net/ipv4/ip_local_port_range in ip(7).";
                    case cutile_net_linux_socket_listen_ebadf: return "EBADF: The argument sockfd is not a valid file descriptor.";
                    case cutile_net_linux_socket_listen_enotsock: return "ENOTSOCK: The file descriptor sockfd does not refer to a socket.";
                    case cutile_net_linux_socket_listen_eopnotsupp: return "EOPNOTSUPP: The socket is not of a type that supports the listen() operation.";
                    case cutile_net_linux_send_to_socket_eacces: return "(For UNIX domain sockets, which are identified by pathname) Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix. (See path_resolution(7).)\n(For UDP sockets) An attempt was made to send to a network/broadcast address as though it was a unicast address.";     
                    case cutile_net_linux_send_to_socket_eagain_ewouldblock: return "EAGAIN/EWOULDBLOCK:\n\t- The socket is marked nonblocking and the requested operation would block. POSIX.1-2001 allows either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.\n\t- (Internet domain datagram sockets) The socket referred to by sockfd  had  not  previously  been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use. See the discussion of /proc/sys/net/ipv4/ip_local_port_range in ip(7).";     
                    case cutile_net_linux_send_to_socket_ealready: return "EALREADY: Another Fast Open is in progress.";   
                    case cutile_net_linux_send_to_socket_ebadf: return "EBADF: sockfd is not a valid open file descriptor.";      
                    case cutile_net_linux_send_to_socket_econnreset: return "ECONNRESET: Connection reset by peer."; 
                    case cutile_net_linux_send_to_socket_edestaddrreq: return "EDESTADDRREQ: The socket is not connection-mode, and no peer address is set.";
                    case cutile_net_linux_send_to_socket_efault: return "EFAULT: An invalid user space address was specified for an argument.";     
                    case cutile_net_linux_send_to_socket_eintr: return "EINTR: A signal occurred before any data was transmitted; see signal(7).";      
                    case cutile_net_linux_send_to_socket_einval: return "EINVAL: Invalid argument passed.";     
                    case cutile_net_linux_send_to_socket_eisconn: return "EISCONN: The connection-mode socket was connected already but a recipient was specified. (Now either this error is returned, or the recipient specification is ignored.)";    
                    case cutile_net_linux_send_to_socket_emsgsize: return "EMSGSIZE: The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.";
                    case cutile_net_linux_send_to_socket_enobufs: return "ENOBUFS: The output queue for a network interface was full.  This generally indicates that the interface has stopped sending, but may be caused by transient congestion.  (Normally, this does not occur in Linux. Packets are just silently dropped when a device queue overflows.)";    
                    case cutile_net_linux_send_to_socket_enomem: return "ENOMEM: No memory available.";     
                    case cutile_net_linux_send_to_socket_enotconn: return "ENOTCONN: The socket is not connected, and no target has been given.";   
                    case cutile_net_linux_send_to_socket_enotsock: return "ENOTSOCK: The file descriptor sockfd does not refer to a socket.";   
                    case cutile_net_linux_send_to_socket_eopnotsupp: return "EOPNOTSUPP: Some bit in the flags argument is inappropriate for the socket type."; 
                    case cutile_net_linux_send_to_socket_epipe: return "EPIPE: The local end has been shut down on a connection oriented socket. In this case, the process will also receive a SIGPIPE unless MSG_NOSIGNAL is set.";      
                #endif
                
                case cutile_net_unknown_err: return "An unknown network error occurred.";
                
                default: return "";
            }
        }

    #endif // CUTILE_IMPLEM

    #ifdef CUTILE_CPP
        maybe_inline cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_ipv4_endpoint* endpoint)
        {
            return cutile_bind_net_socket(socket, (const cutile_net_endpoint*)endpoint);
        }
        maybe_inline cutile_net_error cutile_bind_net_socket(cutile_net_socket* socket, const cutile_ipv6_endpoint* endpoint)
        {
            return cutile_bind_net_socket(socket, (const cutile_net_endpoint*)endpoint);
        }
    #endif

    #define CUTILE_NETWORK_H
#endif
