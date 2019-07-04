#include "myJson.h"
#include <fstream>
#include "json/json.h"
#include <string>
#include "mydb.h"
#include "file_info.h"
#include <vector>

std::string path = "/root/test/";

MyJson::MyJson()
{

}

std::string MyJson::packageSonglistJson(const std::string file)
{
    Json::Value arrayObj;
    int n = 5;
    Json::Value new_item;

    std::vector<stru_music> songlist;
    stru_music music;

    MyDB db;
    db.initDB();
//    db.createsongListTable("123", "MyMusic");
//    db.addMusic("MyMusic", "rtsp://");

    std::vector<std::string> resulte = db.querysongList("MyMusic");

    for(auto &t : resulte){
        std::cout << t << std::endl;
        music.name = "name";
        music.singer = "singer";
        music.album = "album";
        music.duration = "duration";
        music.size = "size";
        music.source = t;
        music.lyric = "lyric";

        songlist.push_back(music);
    }

    // 构建对象
    for (int i = 0; i < songlist.size() ; i++) {
        music = songlist[i];
        std::string x = std::to_string(i);
        new_item.clear();
        new_item["name"] = music.name;
        new_item["singer"] = music.singer;
        new_item["album"] = music.album;
        new_item["duration"] = music.duration;
        new_item["size"] = music.duration;
        new_item["source"] = music.source;
        new_item["lyric"] = music.lyric;
        arrayObj.append(new_item);
        // 插入成员
    }

    std::string filename = ".json";
    filename = path + file + filename;
    std::ofstream ofs;
    ofs.open(filename);
    ofs<< arrayObj.toStyledString();
    ofs.close();

    return filename;
}

void MyJson::analysisSonglistJson(const std::string file)
{
    std::cout<<"读取json文件"<<std::endl;
    std::ifstream ifs;
    ifs.open(file);

    Json::Value jsonRoot;
    Json::Reader readerinfo;
    Json::Value root;
    if(!ifs.is_open()){
        std::cout << "open file error" << std::endl;
    }
    if (readerinfo.parse(ifs, jsonRoot)) {
        if (jsonRoot.isArray()) {
            int nArraySize = jsonRoot.size();
            for (int i=0; i<nArraySize; i++) {
                std::string name = jsonRoot[i]["name"].asString();
                std::string singer = jsonRoot[i]["singer"].asString();
                std::string album = jsonRoot[i]["album"].asString();
                std::string duration = jsonRoot[i]["duration"].asString();
                std::string size = jsonRoot[i]["size"].asString();
                std::string source = jsonRoot[i]["source"].asString();
                std::string lyric = jsonRoot[i]["lyric"].asString();

                std::cout << name << std::endl;
                std::cout << singer << std::endl;
                std::cout << album << std::endl;
                std::cout << duration << std::endl;
                std::cout << size << std::endl;

            }

        }
    }
}

std::string MyJson::packageSonglistLabJson(const std::string file)
{
    Json::Value arrayObj;
    int n = 5;
    Json::Value new_item;

    std::vector<std::string> songlistLab;

    //    MyDB db;
    //    db.initDB();

    //songlistLab = db.querysongListLab(file);
    songlistLab.push_back("Chinese");
    songlistLab.push_back("English");
    songlistLab.push_back("Folk");
    songlistLab.push_back("RockAndRoll");
    songlistLab.push_back("LightMusic");
    songlistLab.push_back("ElectroicMusic");

    n = songlistLab.size();

    // 构建对象
    for (int i = 0; i < n; i++) {
        std::string x = std::to_string(i);
        new_item.clear();
        new_item["songlist"] = songlistLab[i];
        arrayObj.append(new_item);
        // 插入成员
    }

    std::string filename = ".json";
    filename = path + file + filename;
    std::ofstream ofs;
    ofs.open(filename);
    ofs<< arrayObj.toStyledString();
    ofs.close();

    return filename;
}


