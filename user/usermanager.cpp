#include "usermanager.h"
#include <QDebug>

UserManager::UserManager(QObject *parent) : QObject(parent)
{
    _isLogin = false;
    getUsers();
}

UserManager *UserManager::getIns()
{
    static UserManager userMgr;
    return &userMgr;
}

bool UserManager::isLogin() const
{
    return _isLogin;
}

QString UserManager::getCurUserName() const
{
    return _curUser._name;
}

USER_TYPE UserManager::getCurUserType() const
{
    return _curUser._type;
}

bool UserManager::login(const QString &name, const QString &passwd)
{
    //处理逻辑
    //
    bool isFind = false;
    foreach(User user, _users)
    {
        if(user._name.compare(name) == 0)
        {
            isFind = true;
            if(user._passwd.compare(passwd) == 0)
            {
                //login成功
                _isLogin = true;
                _curUser = user;
            }
            else {
                _isLogin = false;
                qDebug() << "User password is wrong.";
            }
            break;
        }
    }
    if(!isFind)
    {
        qDebug() << "Cann't find the User";
    }
    return _isLogin;
}

bool UserManager::logout()
{
    _curUser = User();
    _isLogin = false;
    return !_isLogin;
}

void UserManager::getUsers()
{
    //从数据库拉取已保存的用户信息
}
