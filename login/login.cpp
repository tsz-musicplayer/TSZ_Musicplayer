#include "login.h"
#include <QDebug>
#include "mydb.h"
#include <string>
using namespace std;

Login::Login()
{
    m_user_id = "";
    m_password = "";
}

Login::~Login()
{}

QString Login::user_id()
{
    qDebug() << "Error: 初始化失败";
    return m_user_id;
}

void Login::set_user_id(QString str)
{
    if (m_user_id != str)
    {
        m_user_id = str;
        emit sig_user_id_changed();
    }
}


QString Login::password()
{
    return m_password;
}


void Login::set_password(QString str)
{
    if (m_password != str)
    {
        m_password = str;
        emit sig_password_changed();
    }
}

bool Login::checkUserinfo(QString account, QString password)
{
    string DB_server = "localhost";
    string DB_username = "root";
    string DB_password = "root";
    string DB_name = "mysql";
    MyDB db;
    db.initDB(DB_server, DB_username, DB_password, DB_name);
    db.createPassworddbTable();
    db.queryUserInfo(account.toStdString(),password.toStdString());

}

bool Login::saveUserinfo(QString account, QString password)
{
    string DB_server = "localhost";
    string DB_username = "root";
    string DB_password = "root";
    string DB_name = "mysql";
    MyDB db;
    db.initDB(DB_server, DB_username, DB_password, DB_name);
    db.createPassworddbTable();
    db.saveUserInfo(account.toStdString(),password.toStdString());
}

