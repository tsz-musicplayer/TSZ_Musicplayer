#ifndef MYJSON_H
#define MYJSON_H

#include <iostream>
#include "file_info.h"

//周敏 json封装和解析
class MyJson
{
public:
    MyJson();

    // json封装歌单
    //std::string packageSonglistJson(const std::string file);
    std::string packageSonglistJson(const std::vector<stru_music> data, const std::string file);
    //json解析歌单
    std::vector<stru_music> analysisSonglistJson(const std::string file);

    // json封装歌单池
    std::string packageSonglistLabJson(std::vector<std::string> &data,const std::string file);
    //json解析歌单池
    std::vector<std::string> analysisSonglistLabJson(const std::string file);
};

#endif // JSON_H
