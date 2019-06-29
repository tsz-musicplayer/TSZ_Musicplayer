#include <iostream>
#include <mysql/mysql.h>
#include "mydb.h"

MyDB::MyDB()
{
    mysql = mysql_init(NULL);//初始化数据库
    if(mysql == NULL)
    {
        std::cout << "Error: 初始化失败" << std::endl;
        exit(1);
    }
}

MyDB::~MyDB()
{
    if(mysql!=NULL)//关闭数据连接
    {
        mysql_close(mysql);
    }
}


bool MyDB::connectDB(std::string host,std::string user,std::string passwd,std::string db_name)
{
    //建立一个数据库连接
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0);
    if(mysql == NULL)
    {
        std::cout << "Error: 连接数据库失败 "/* << mysql_error(mysql)*/;
        exit(1);
    }
    useDatabase("Musicplayer");

    return true;
}

//创建数据库，并打开
bool MyDB::createDatabase(std::string dbname)
{
    std::string queryStr = "create database ";
    queryStr += dbname;
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::string queryStr = "use ";
        queryStr += dbname;
        std::cout << "创建并使用数据库";
        return true;
    }
    std::cout << "数据库已创建";
    return false;
}

//使用数据库
bool MyDB::useDatabase(std::string dbname)
{
    std::string queryStr = "use ";
    queryStr += dbname;
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
//        qDebug() << "使用数据库";
        return true;
    }
    std::cout << "数据库未创建";
    return false;
}

//创建帐号密码表
bool MyDB::createPassworddbTable()
{
    std::string queryStr = "create table Userinfo(user_id varchar(20), password char(20))";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        return true;
    }
    std::cout << "登录信息列表  创建失败";
    return false;
}

//创建系统歌单列表
bool MyDB::createMusicTable()
{
    std::string queryStr = "create table AllMusic(path varchar(20), name char(20), singer char(20), album char(20), duration char(20), lyric varchar(20), size varchar(20))";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        return true;
    }
    std::cout << "系统歌单列表  创建失败";
    return false;
}

//创建歌单列表
bool MyDB::createsongListLabTable(std::string songListLab_name)
{
    std::string queryStr = "create table "+songListLab_name+"_lab(songlist varchar(20))";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        return true;
    }
    std::cout << "歌单列表  创建失败";
    return false;
}

//创建歌曲列表
bool MyDB::createsongListTable(std::string songListLab_name, std::string songList_name)
{
    std::string queryStr = "create table "+songList_name+"_list(path varchar(100))";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        //addsongList(songListLab_name, songList_name);
        return true;
    }
    std::cout << "歌曲列表  创建失败";
    return false;
}

//添加歌单列表
bool MyDB::addsongList(std::string songListLab_name, std::string songList_name)
{
    std::string queryStr = "INSERT INTO "+songListLab_name+"_lab VALUES('"+songList_name+"_list')";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "添加歌单成功";
        return true;
    }
    return false;
}

//添加歌曲列表
bool MyDB::addMusic(std::string songList_name, std::string music_path)
{
    std::string queryStr = "INSERT INTO "+songList_name+"_list VALUES('"+music_path+"')";
    //qDebug()<<QString::fromStdString(user_id)<<QString::fromStdString(password);
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "添加歌曲成功";
        return true;
    }
    return false;
}

//删除歌曲列表
bool MyDB::deletesongListTable(std::string songListLab_name, std::string songList_name)
{
    std::string queryStr = "drop table "+songList_name+"_list";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "删除歌曲列表";
        deletesongListLabRecord(songListLab_name, songList_name);
        return true;
    }
    return false;
}

//删除歌曲列表记录
bool MyDB::deletesongListLabRecord(std::string songListLab_name, std::string songList_name)
{
    std::string queryStr = "delete from "+songListLab_name+"_lab where songlist='"+songList_name+"_list'";
    //qDebug()<<QString::fromStdString(user_id)<<QString::fromStdString(password);
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "列表记录删除成功";
        return true;
    }
    return false;
}

//删除歌曲(通过歌曲路径的形式查询歌曲信息)
bool MyDB::delectMusic(std::string songList_name, std::string music_path)
{
    std::string queryStr = "delete from "+songList_name+"_list where path='"+music_path+"'";
    //qDebug()<<QString::fromStdString(user_id)<<QString::fromStdString(password);
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "列表记录删除成功";
        return true;
    }
    return false;
}

//查询、判断帐号密码表中的信息
bool MyDB::queryUserInfo(std::string user_id, std::string password)
{
    std::string queryStr = "SELECT * FROM Userinfo WHERE user_id = '"+user_id+"' AND password = '"+password+"'";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        auto result = mysql_store_result(mysql);//获取结果集
        if (result){
            int num_rows = mysql_num_rows(result);//获取结果集中总共的行数
            //qDebug()<<num_rows<<QString::fromStdString(user_id)<<QString::fromStdString(password);
            if(num_rows==0){
                return false;
            }
        }
        std::cout << "登录成功";
        return true;
    }
}

//添加 帐号密码信息到列表
bool MyDB::saveUserInfo(std::string user_id, std::string password)
{
    std::string queryStr = "INSERT INTO Userinfo VALUES('"+user_id+"','"+password+"')";
    //qDebug()<<QString::fromStdString(user_id)<<QString::fromStdString(password);
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {

        std::cout << "注册成功";
        return true;
    }
    return false;
}

//查询歌单池列表
std::vector<std::string>  MyDB::querysongListLab(std::string songListLab_name)
{
    std::string queryStr = "SELECT * FROM "+ songListLab_name+"_lab";
    std::cout << "歌单列表:";
    return (queryList(queryStr));
}

//查询歌曲列表
std::vector<std::string>  MyDB::querysongList(std::string songList_name)
{
    std::string queryStr = "SELECT * FROM "+ songList_name+"_list";
    //std::cout << "歌曲列表:";
    return(queryList(queryStr));
}


//查询歌曲信息
bool MyDB::queryMusic(std::string music_path)
{
    std::string queryStr = "SELECT * FROM Music WHERE path='"+ music_path+"'";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        //        qDebug() << "YYYY";
        auto result = mysql_store_result(mysql);//获取结果集
        if (result){
            auto row = mysql_fetch_row(result);//获取结果集中的列
            std::cout << "路径："<<row[0]<<"歌名："<<row[1]<<"歌词"<<row[2]<<"歌曲大小："<<row[3];
        }else {
            std::cout << "Error: 读取列表失败";
            return false;
        }
    }
    return false;
}

//搜索获得系统歌曲列表中的信息
bool MyDB::search(std::string music)
{
    std::string queryStr = "SELECT * FROM Music WHERE name like '%n2%'";
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        std::cout << "tttt";
        auto result = mysql_store_result(mysql);//获取结果集
        if (result){
            int num_rows = mysql_num_rows(result);//获取结果集中总共的行数
            //qDebug()<<num_rows<<QString::fromStdString(user_id)<<QString::fromStdString(password);
            for(int i=0;i<num_rows;i++)
            {
                auto row = mysql_fetch_row(result);//获取结果集中的列
                if(!row) break;
                std::cout << "路径："<<row[0]<<"歌名："<<row[1]<<"歌词"<<row[2]<<"歌曲大小："<<row[3];
            }
        }else {
            std::cout << "Error: 读取列表失败";
            return false;
        }
    }
    std::cout << "没有相关歌曲";
    return true;
}

//查询列表
std::vector<std::string>  MyDB::queryList(std::string queryStr)
{   
     std::vector<std::string> songlistLab;

    if (0 == mysql_query(mysql,queryStr.c_str()))
    {
        auto result = mysql_store_result(mysql);//获取结果集
        if (result){
            int num_rows = mysql_num_rows(result);//获取结果集中总共的行数
            for(int i=0;i<num_rows;i++)
            {
                auto row = mysql_fetch_row(result);//获取结果集中的列
                if(!row) break;
                songlistLab.push_back(row[0]);
            }
        }else {
            std::cout << "Error: 读取列表失败";
//            return false;
        }
    }
    return songlistLab;
}


//bool MyDB::readTableData()//读取数据库中的信息
//{
//    m_rootMusic.run();
//    m_rootList = m_rootMusic.list();// 得到系统音乐歌单

//    //从数据库中读取“最喜爱的音乐”歌单信息
//    m_perferMusicList.clear();
//    m_perferMusicPathList.clear();
//    std::string sql = "select * from musicPath";
//    mysql_query(mysql, sql.c_str());
//    auto sresult = mysql_store_result(mysql);//获取结果集
//    if (sresult){
//        int num_rows = mysql_num_rows(sresult);//获取结果集中总共的行数
//        for(int i=0;i<num_rows;i++)
//        {
//            auto row = mysql_fetch_row(sresult);//获取结果集中的列
//            if(!row) break;
//            m_perferMusicList.append(QString::fromStdString(music(row[0])));
//            m_perferMusicPathList.append(QString::fromStdString(row[0]));
//            //            QDebug() << row[0] /*<< " " << row[1]*/;
//            //            QDebug() << endl;
//        }
//    }else {
//        qDebug() << "Error: perfer读取表";
//        return false;
//    }

//    //从数据库钟读取自定义歌单信息
//    std::string sql1 = "select * from musicListPath";
//    mysql_query(mysql, sql1.c_str());
//    auto sresult1 = mysql_store_result(mysql);//获取结果集
//    if (sresult1){
//        int num_rows = mysql_num_rows(sresult1);//获取结果集中总共的行数
//        for(int i=0;i<num_rows;i++)
//        {
//            auto row = mysql_fetch_row(sresult1);//获取结果集中的列
//            if(!row) break;
//            auto musicPath = QString::fromStdString(row[1]);
//            auto listName = QString::fromStdString(row[0]);
//            //读取歌单
//            if(m_musicList.find(listName) == m_musicList.end()){
//                //如果歌单不存在
//                QStringList list;
//                m_list.append(listName);
//                m_musicList.insert(std::pair<QString, QStringList >(listName, list));
//            } else if(musicPath != ""){
//                //歌单存在且 如果路径有效
//                m_musicList[listName].append(musicPath);//读取歌单中的音乐路径
//            }
//        }
//    }else {
//        qDebug() << "Error: list读取表";
//        return false;
//    }


//    return true;
//}
