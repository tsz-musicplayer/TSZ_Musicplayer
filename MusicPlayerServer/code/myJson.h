#ifndef MYJSON_H
#define MYJSON_H

#include <iostream>

//周敏 json封装和解析
class MyJson
{
public:
    MyJson();

    // json封装歌单
    std::string packageSonglistJson(const std::string file);
    //json解析歌单
    void analysisSonglistJson(const std::string file);

    // json封装歌单池
    std::string packageSonglistLabJson(const std::string file);
    //json解析歌单池
    void analysisSonglistLabJson(const std::string file);
};

#endif // JSON_H
