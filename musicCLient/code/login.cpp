#include "login.h"
#include <QDebug>
#include "mydb.h"
#include <string>
#include "client.h"

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
    std::cout << "login id: " << account.toStdString()
              << "password: " << password.toStdString() << std::endl;


    asio::io_service io;
    try{
        Client::Pointer c = Client::create(io);

        if(c->login(account.toStdString().data(), password.toStdString().data())){
            std::cout << "login successe" << std::endl;
        } else {
            std::cout << "login false" << std::endl;
        }
        io.run();
        return true;
    }
    catch (std::exception& err) {
        std::cerr << err.what() << "\n";
        return false;
    }
    return true;
}

bool Login::saveUserinfo(QString account, QString password)
{
    std::cout << "registe id: " << account.toStdString()
              << "password: " << password.toStdString() << std::endl;

    asio::io_service io;
    try{
        Client::Pointer c = Client::create(io);

        if(c->registe(account.toStdString().data(), password.toStdString().data())){
            std::cout << "registe successe" << std::endl;
        } else {
            std::cout << "registe false" << std::endl;
        }
        io.run();
        return true;
    }
    catch (std::exception& err) {
        std::cerr << err.what() << "\n";
        return false;
    }
    return true;
}

