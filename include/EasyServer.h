#ifndef __BAN_20190129_EASY_SERVER_H__  /* create by Ban, 20190129 */
#define __BAN_20190129_EASY_SERVER_H__
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

class EasyServer 
{
 public:

 private:
   std::vector<EasyConnection> conn_vec;
   std::string server_ip;
   int server_port;
   int listen_list_len;

 public:
   static EasyServer& createEasyServer(const std::string& server_ip, int server_port);
   virtual int run();

   std::string serverIP();
   int serverPort();

   void close();

 private:
   EasyServer(const std::string& server_ip, int server_port);
   ~EasyServer();

};



#endif // !__BAN_20190129_EASY_SERVER_H__