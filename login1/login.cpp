#include "login.h"
#include <QDebug>

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

