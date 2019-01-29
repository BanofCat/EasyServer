#include <arpa/inet.h>
#include "EasyConnection.h"
#include "ErrorCode.h"
#include "LogAPI.h"

/* public */
EasyConnection:: 
EasyConnection& createEasyConnection(
    int connection_fd, 
    const std::string server_ip, 
    const std::string client_ip, 
    int client_port)
{
    // ip format check
    if (INADDR_NONE == inet_addr(server_ip.c_str()) || INADDR_NONE == inet_addr(client_ip.c_str()) {
        LOG_ERROR_FMT("ip format is invalid, server ip: %s, client ip: %s", server_ip.c_str(), client_ip.c_str());
        return NULL;
    }
    // port range check
    if (client_port > MAX_PORT_NUM || client_port < MIN_PORT_NUM) {
        LOG_ERROR_FMT("port %d is not in the range[%d, %d]", client_port, MIN_PORT_NUM, MAX_PORT_NUM);
        return NULL;
    }
    // fd range check
    if (connection_fd < 0) {
        LOG_ERROR_FMT("connection fd %d is invalid", connection_fd);
        return NULL;
    }
    return EasyConnection(connection_fd, server_ip, client_ip, client_port);
}


EasyConnection::    
EasyConnection(const EasyConnection& target_conn)
{
    this->deepCopy(target_conn);
}
    

EasyConnection::
EasyConnection& operator=(const EasyConnection& target_conn)
{
    if (this != &target_conn) {
        this->deepCopy(target_conn);
    }
    return *this;
}

int EasyConnection::
connectionFD()
{
    return this->connection_fd;
}

std::string EasyConnection::
serverIP()
{
    return this->server_ip;
}

std::string EasyConnection::
clientIP()
{
    return this->client_ip;
}

int EasyConnection::
clientPort()
{
    return this->client_port;
}

void EasyConnection::
close()
{
    if (this->connection_fd >= 0) {
        close(this->connection_fd);
    }
}

/* private */

EasyConnection::
EasyConnection(
    int connection_fd, 
    const std::string server_ip, 
    const std::string client_ip, 
    int client_port): connection_fd(-1), client_port(-1)
{
    this->connection_fd = connection_fd;
    this->server_ip = server_ip;
    this->client_ip = client_ip;
    this->client_port = client_port;
}

EasyConnection::
~EasyConnection()
{
    this->close();
}

int EasyConnection::
deepCopy(const EasyConnection& target_conn)
{
    this->connection_fd = target_conn.connectionFD();
    this->server_ip = target_conn.serverIP();
    this->client_ip = target_conn.clientIP();
    this->client_port = target_conn.clientPort();
}