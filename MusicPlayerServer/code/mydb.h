#ifndef MYDB_H
#define MYDB_H

#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <map>

class MyDB
{

public:
    MyDB();
    ~MyDB();

    std::string DB_server = "localhost";
    std::string DB_username = "root";
    std::string DB_password = "root";
    std::string DB_name = "mysql";

    bool initDB(){
        return connectDB(DB_server, DB_username, DB_password, DB_name);
    }

    bool connectDB(std::string host, std::string user, std::string pwd, std::string db_name);

    bool createDatabase(std::string dbname);
    bool useDatabase(std::string dbname);

    bool createPassworddbTable();//创建帐号密码表
    bool createMusicTable();//创建系统歌单列表
    bool createsongListLabTable(std::string songListLab_name);//创建歌单列表（songListLab_name等同于user_id）
    bool createsongListTable(std::string songListLab_name, std::string songList_name);//创建歌曲列表

    bool addsongList(std::string songListLab_name, std::string songList_name);//添加歌曲列表
    bool addMusic(std::string songList_name, std::string music_path);//添加歌曲信息(通过歌曲路径的形式查询歌曲信息)

    bool deletesongListTable(std::string songListLab_name, std::string songList_name);//删除歌曲列表
    bool delectMusic(std::string songList_name, std::string music_path);//删除歌曲信息(通过歌曲路径的形式查询歌曲信息)

    bool queryUserInfo(std::string user_id, std::string password);//查询、判断帐号密码表中的信息
    bool saveUserInfo(std::string user_id, std::string password);//添加 帐号密码信息到列表
    std::vector<std::string>  querysongListLab(std::string songListLab_name);//获取歌单列表池（songListLab_name等同于user_id）
    std::vector<std::string>  querysongList(std::string songList_name);//获取歌曲列表
    bool queryMusic(std::string music_path);//获取歌曲信息(通过歌曲路径的形式查询歌曲信息)
    bool search(std::string music);//搜索 获取系统歌曲列表中的相关歌曲信息

private:
    //    std::string music(std::string data);
    MYSQL *mysql;//连接mysql句柄指针
    //    MYSQL_RES *result;//指向查询结果的指针
    //    MYSQL_ROW row;//返回行信息

    bool deletesongListLabRecord(std::string songListLab_name, std::string table_name);//删除歌曲列表记录
    std::vector<std::string> queryList(std::string queryStr);
};

#endif // MYDB_H
