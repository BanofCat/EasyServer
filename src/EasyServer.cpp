#include "EasyServer.h"
#include "EasyConnection.h"


/* public */
EasyServer& createEasyServer(const std::string& server_ip, int server_port)
{
    // ip format check
    if (INADDR_NONE == inet_addr(server_ip.c_str())) {
        LOG_ERROR_FMT("ip format is invalid, server ip: %s", server_ip.c_str());
        return NULL;
    }
    // port range check
    if (server_port > MAX_PORT_NUM || server_port < MIN_PORT_NUM) {
        LOG_ERROR_FMT("port %d is not in the range[%d, %d]", server_port, MIN_PORT_NUM, MAX_PORT_NUM);
        return NULL;
    }

    return EasyServer(server_ip, server_port);
}

void* EasyServer::
connectionThread(void* args)
{
    EasyConnection* conn_ptr = (EasyConnection*)args;
    int ret_val = 0;
    char recv_buf[1024];
    char send_buf[1024];
    memset(recv_buf, 0, sizeof(recv_buf));
    memset(send_buf, 0, sizeof(send_buf));
    while(true) {
        ret_val = conn_ptr->recv(recv_buf, sizeof(recv_buf));
        if (ret_val < 0) {
            break;
        }
        ret_val = conn_ptr->send(send_buf, sizeof(send_buf));
        if (ret_val < 0) {
            break;
        }
    }
    LOG_ERROR_FMT("%d connection thread quit", pthread_self());
}

void EasyServer::
closeConnection()
{
    std::map<ptherad_t, EasyConnection>::iterator iter;
    for(iter = this->conn_map.begin(); iter != this->conn_map.end(); ++iter) {
        ptherad_cancel(iter->first);
        iter->second.close();
    }
}


int EasyServer::
run()
{
    int client_fd;
    int server_fd;
    socklen_t client_addr_len;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    server_fd = socket(AF_INET, SOCK_STREAM);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(this->server_port);
    bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, this->listen_list_len);

    while (true) {
        client_addr_len = sizeof(client_addr);
        client_fd = accept(server_fd, (sockaddr *)&client_addr, &client_addr_len);
        EasyConnection temp =  EasyConnection::createEasyConnection(
            client_fd, 
            string(inet_ntoa(server_addr.sin_addr)), 
            this->server_port,
            string(inet_ntoa(client_addr.sin_addr)),
            client_addr.sin_port
        );
        pthread_t thread_id;
        pthread_create(thread_id, NULL, this->connectionThread, (void*)&temp));
        this->conn_map[thread_id] = temp;
    }
    this->closeConnection();
}


std::string EasyServer::
serverIP()
{
    return this->server_ip;
}

int EasyServer::
serverPort()
{
    return this->server_port;
}


/* private */
EasyServer::
EasyServer(const std::string& server_ip, int server_port): server_port(-1)
{
    this->server_ip = server_ip;
    this->server_port = server_port;
    this->listen_list_len = 10;
    this->conn_map.clear();
}

EasyServer::
~EasyServer()
{
    this->close();
}

