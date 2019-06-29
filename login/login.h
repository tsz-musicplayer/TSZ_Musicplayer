#ifndef LOGIN_H
#define LOGIN_H

#include "QObject"
#include "string"

class Login:public QObject
{
    Q_OBJECT

    //属性:用户名
    Q_PROPERTY(QString user_id READ user_id WRITE set_user_id NOTIFY sig_user_id_changed)
    //属性:密码
    Q_PROPERTY(QString password READ password WRITE set_password NOTIFY sig_password_changed)

public:
    Login();
    ~Login();

    QString user_id();
    void set_user_id(QString str);

    QString password();
    void set_password(QString str);

    Q_INVOKABLE bool checkUserinfo(QString account, QString password);
    Q_INVOKABLE bool saveUserinfo(QString account, QString password);

signals:
    void sig_user_id_changed();
    void sig_password_changed();

private:
    QString m_user_id;
    QString m_password;
};

#endif // LOGIN_H
