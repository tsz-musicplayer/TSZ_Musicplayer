#ifndef MYDB_H
#define MYDB_H

#include <QObject>
#include <mysql/mysql.h>
#include <string>
#include <QStringList>
#include <QFileInfo>
#include <map>

class MyDB : public QObject
{
    Q_OBJECT

public:
    MyDB();
    ~MyDB();

    bool initDB(std::string host, std::string user, std::string pwd, std::string db_name);

    bool createDatabase(std::string dbname);
    bool createPassworddbTable();

    bool queryUserInfo(std::string user_id, std::string password);
    bool saveUserInfo(std::string user_id, std::string password);

signals:
        void perferMusicListChange();

private:
    std::string music(std::string data);
    MYSQL *mysql;//连接mysql句柄指针
    MYSQL_RES *result;//指向查询结果的指针
    MYSQL_ROW row;//返回行信息
};

#endif // MYDB_H
