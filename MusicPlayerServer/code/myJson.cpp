#include "myJson.h"
#include <fstream>
#include "json/json.h"
#include <string>
#include "mydb.h"
#include "file_info.h"
#include <vector>

std::string path = "./";

MyJson::MyJson()
{

}

//封装json
std::string MyJson::packageSonglistJson(const std::vector<stru_music> data, const std::string file)
{
    Json::Value arrayObj;
    Json::Value new_item;

    stru_music music;

    // 构建对象
    for (int i = 0; i < data.size() ; i++) {
        music = data[i];
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

//解析json
std::vector<stru_music> MyJson::analysisSonglistJson(const std::string file)
{
    std::cout<<"读取json文件"<<std::endl;
    std::ifstream ifs;
    ifs.open(file);

    Json::Value jsonRoot;
    Json::Reader readerinfo;
    Json::Value root;
    
    std::vector<stru_music> songlist;
    stru_music music;
    if(!ifs.is_open()){
        std::cout << "open file error" << std::endl;
    }
    if (readerinfo.parse(ifs, jsonRoot)) {
        if (jsonRoot.isArray()) {
            int nArraySize = jsonRoot.size();
            for (int i=0; i<nArraySize; i++) {
                music.name = jsonRoot[i]["name"].asString();
                music.singer = jsonRoot[i]["singer"].asString();
                music.album = jsonRoot[i]["album"].asString();
                music.duration = jsonRoot[i]["duration"].asString();
                music.size = jsonRoot[i]["size"].asString();
                music.source = jsonRoot[i]["source"].asString();
                music.lyric = jsonRoot[i]["lyric"].asString();

            }
        }
    }
    return songlist;
}

//封装歌单
std::string MyJson::packageSonglistLabJson(std::vector<std::string> &data, const std::string file)
{
    Json::Value arrayObj;
    int n = 5;
    Json::Value new_item;

    n = data.size();

    // 构建对象
    for (int i = 0; i < n; i++) {
        std::string x = std::to_string(i);
        new_item.clear();
        new_item["songlist"] = data[i];
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

//解析歌单
std::vector<std::string> MyJson::analysisSonglistLabJson(const std::string file)
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
                std::string songlist = jsonRoot[i]["songlist"].asString();
                std::cout << songlist << std::endl;
            }
        }
    }
}


