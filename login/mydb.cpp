#include <QDebug>
#include <mysql/mysql.h>
#include "mydb.h"

MyDB::MyDB()
{
    mysql = mysql_init(NULL);//初始化数据库
    if(mysql == NULL)
    {
        qDebug() << "Error: 初始化失败";
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


bool MyDB::initDB(std::string host,std::string user,std::string passwd,std::string db_name)
{
    //建立一个数据库连接
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0);
    if(mysql == NULL)
    {
        qDebug() << "Error: 连接数据库失败 "/* << mysql_error(mysql)*/;
        exit(1);
    }
    createDatabase("Musicplayer");
    return true;
}

//判断数据库是否存在，不存在则创建数据库，并打开
bool MyDB::createDatabase(std::string dbname)
{
//    std::string queryStr = "use ";
//    queryStr += dbname;
//    if (0 == mysql_query(mysql,queryStr.c_str()))
//    {

        std::string queryStr = "create database ";
        queryStr += dbname;
        if (0 == mysql_query(mysql,queryStr.c_str()))
        {
            queryStr = "use ";
            queryStr += dbname;
            return true;
        }
        //qDebug() << "创建数据库";
//    }
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
    return false;
}

//查询/判断帐号密码表中的信息
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
        qDebug() << "登录成功";
        return true;
    }
}

bool MyDB::saveUserInfo(std::string user_id, std::string password)
{
    std::string queryStr = "INSERT INTO Userinfo (user_id,password) VALUES('"+user_id+"','"+password+"')";
    //qDebug()<<QString::fromStdString(user_id)<<QString::fromStdString(password);
    if (0 == mysql_query(mysql,queryStr.c_str()))
    {

        qDebug() << "注册成功";
        return true;
    }
    return false;
}
