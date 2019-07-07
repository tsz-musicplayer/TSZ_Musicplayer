#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "code/server.h"

//test
void initDB(std::string ip)
{
    MyDB db;

    db.initDB();

    db.createDatabase("Musicplayer");
    db.useDatabase("Musicplayer");
    db.createPassworddbTable();
    db.createMusicTable();

    db.createsongListLabTable("Online");
    db.createsongListTable("Online", "华语");
    db.createsongListTable("Online", "英语");
    db.createsongListTable("Online", "韩语");
    db.createsongListTable("Online", "日语");
    db.createsongListTable("Online", "粤语");

    db.createsongListTable("Online", "古风");
    db.createsongListTable("Online", "电音");
    db.createsongListTable("Online", "民谣");
    db.createsongListTable("Online", "流行");
    db.createsongListTable("Online", "摇滚");

    db.addMusicToSystem("rtsp://"+ ip + "/music/zuimei.mp3", "最美", "羽泉", "羽泉精选", "05：02", "null", "未知");
    db.addMusicToSystem("rtsp://"+ ip + "/music/aidedaijia.mp3", "爱的代价", "张艾嘉", "爱的代价", "05：01", "null", "未知");
    db.addMusicToSystem("rtsp://"+ ip + "/music/PlayWithFire.mp3", "Play With Fire", "Sam Tinnesz", "Sam Tinnesz", "02：59", "null", "未知");
    db.addMusicToSystem("rtsp://"+ ip + "/music/D.T.M.mp3", "D.T.M", "Simon Curtis", "R", "03：17", "null", "未知");

    //插入音乐到歌单

    db.addMusic("华语", "rtsp://"+ ip + "/music/zuimei.mp3");
    db.addMusic("华语", "rtsp://"+ ip + "/music/aidedaijia.mp3");

    db.addMusic("英语", "rtsp://"+ ip + "/music/PlayWithFire.mp3");
    db.addMusic("英语", "rtsp://"+ ip + "/music/D.T.M.mp3");
}

//end test

int main()
{
    //servertest

    std::string ip;
    int port;

    std::ifstream ifs;
    ifs.open("../configIpPort");
    if(ifs.is_open()){
        char buff[64];
        ifs.getline(buff, sizeof (buff));
        ip = buff;
        std::cout << buff << std::endl;
        ifs.getline(buff, sizeof(buff));
        std::string p = buff;
        port = atoi(p.c_str());
        std::cout << port << std::endl;
    } else {
        std::cout << "文件打开失败" << std::endl;
    }

    //只执行一次
    initDB(ip);

    std::cout << "等待客户端链接.\n";
    asio::io_service io;
    Server receiver(io, port);
    io.run();

    return 0;

}
