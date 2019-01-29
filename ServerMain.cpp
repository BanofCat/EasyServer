#include "EasyServer.h"


int main(int argc, char **argv) 
{
    EasyServer es = EasyServer(std::string ip, int port);

    es.run();


}