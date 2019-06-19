#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include "common/common.h"

class UserManager : public QObject
{
    Q_OBJECT
private:
    explicit UserManager(QObject *parent = nullptr);

public:
    static UserManager * getIns();

    bool isLogin() const;
    QString getCurUserName() const;
    USER_TYPE getCurUserType() const;

    //检测用户名密码是否匹配，若匹配，则设置该用户为当前用户并返回true
    bool login(const QString & name, const QString & passwd);
    //登出
    bool logout();

signals:

public slots:

private:
    void getUsers();

private:
    bool _isLogin;      //当前是否已经有用户登录
    User _curUser;      //当前用户
    QList<User> _users; //所有已创建的用户
};

#endif // USERMANAGER_H
