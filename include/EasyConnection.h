#ifndef __BAN_20190129_EASY_CONNECTION_H__
#define __BAN_20190129_EASY_CONNECTION_H__
#include <string>

#define MAX_PORT_NUM 65535
#define MIN_PORT_NUM 0

class EasyConnection
{
 public:
   

 private:
   std::string server_ip;
   std::string client_ip;
   int client_port;
   int server_port;
   int connection_fd;

 public:
   static EasyConnection& createEasyConnection(
        int connection_fd, 
        const std::string& server_ip, 
        int server_port, 
        const std::string& client_ip, 
        int client_port
    );
   EasyConnection(const EasyConnection& target_conn);
   EasyConnection& operator=(const EasyConnection& target_conn);

   int connectionFD();
   std::string serverIP() const;
   std::string clientIP() const;
   int clientPort() const;
   int serverPort() const;

   int send(char* buf, int buf_size);
   int recv(char* ret_bug, int buf_size);



   void close();

 private:
   EasyConnection(int connection_fd, const std::string& server_ip, const std::string& client_ip, int client_port);
   ~EasyConnection();
   int deepCopy(const EasyConnection& target_conn);

};

#endif // !__BAN_20190129_EASY_CONNECTION_H__
