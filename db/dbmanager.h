#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include "common/common.h"

class DBManager : public QObject
{
    Q_OBJECT
private:
    explicit DBManager(QObject *parent = nullptr);

public:
    static DBManager* getIns();

public:
    //user 表
    QList<User> getUsers();
    int getMaxUserID();
    bool isExistUser(const QString & name);
    bool addUser(const User & user);
    bool removeUser(const QString & name);

    //culturedata 表
    QList<CultureData> getCultrueDatas();
    int getMaxCultureDataID();
    bool addCultureData(const CultureData & data);
    bool removeCultureData(const CultureData & data);
    bool removeCultureDataBefore(const QDateTime &datetime);

signals:

public slots:

private:
    //初始化数据库，不存在则创建数据库、数据表
    void init();
};

#endif // DBMANAGER_H
