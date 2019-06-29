#include <iostream>
#include <cstdio>
#include <string>

#include "code/server.h"


int main()
{
    //servertest
     
//    MyDB db;
//    db.initDB();
//    db.createsongListTable("123", "MyMusic");
//    db.addMusic("MyMusic", "rtsp://192.168.43.107/a.mp3");
    std::cout << "等待客户端链接.\n";
    asio::io_service io;
    Server receiver(io, 24);
    io.run();
    
    return 0;
    
}
