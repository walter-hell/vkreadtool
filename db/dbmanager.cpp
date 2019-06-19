#include "dbmanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

const QString user_table_name = "user";
const QString culture_data_table_name = "culture_data";

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    init();
}

DBManager *DBManager::getIns()
{
    static DBManager mgr;
    return &mgr;
}

QList<User> DBManager::getUsers()
{
    QList<User> users;
    //逻辑
    QString sql = tr("select id,name,passwd,type,company,part,address from %1 ")
            .arg(user_table_name);
    QSqlQuery query;
    if(query.exec(sql))
    {
        while(query.next())       //query.next()指向查找到的第一条记录，然后每次后移一条记录
        {
            User user;
            user._id = query.value(0).toInt();
            user._name = query.value(1).toString();
            user._passwd = query.value(2).toString();
            user._type = (USER_TYPE)query.value(3).toInt();
            user._company = query.value(4).toString();
            user._part = query.value(5).toString();
            user._address = query.value(6).toString();
            users.append(user);
        }
    }
    else {
        qDebug() << "查询用户表数据失败" << query.lastError().text();
    }

    return users;
}

int DBManager::getMaxUserID()
{
    int id = 0;
    //SELECT MAX(column_name) FROM table_name
    //sqllite中不能使用MAX函数
    QString sql = tr("select id from %1").arg(user_table_name);
    QSqlQuery query ;
    if(query.exec(sql))
    {
        while(query.next())
        {
            int temp_id = query.value(0).toInt();
            if(temp_id > id ) id = temp_id;
        }
    }
    return id + 1;
}

bool DBManager::isExistUser(const QString &name)
{
    //SELECT COUNT(column_name) FROM table_name
    //sqllite中不能使用COUNT函数
    QString sql = tr("select * from %1 where name='%2'")
            .arg(user_table_name).arg(name);
    QSqlQuery query;
    if(query.exec(sql))
    {
        if(query.next())
        {
            return true;
        }
    }
    return false;
}

bool DBManager::addUser(const User &user)
{
    if(isExistUser(user._name))
    {
        //若存在用户，就更新它
        //UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值
        QString sql_update = tr("update %1 set passwd='%2',"
                                "type=%3,company='%4',"
                                "part='%5',address='%6' where name='%7'")
                .arg(user_table_name)
                .arg(user._passwd)
                .arg((int)user._type)
                .arg(user._company)
                .arg(user._part)
                .arg(user._address)
                .arg(user._name);

        QSqlQuery query_update;
        if(!query_update.exec(sql_update))
        {
            qDebug() << "更新用户信息失败" << query_update.lastError().text();
            return false;
        }
    }
    else
    {
        //若不存在就添加
        //INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
        QString sql_insert = tr("insert into %1 (id,name,passwd,type,company,part,address)"
                                " values (%2,'%3','%4',%5,'%6','%7','%8')")
                .arg(user_table_name)
                .arg(user._id)
                .arg(user._name)
                .arg(user._passwd)
                .arg((int)user._type)
                .arg(user._company)
                .arg(user._part)
                .arg(user._address);

        QSqlQuery query_insert;
        if(!query_insert.exec(sql_insert))
        {
            qDebug() << "添加用户信息失败:" << sql_insert << query_insert.lastError().text();
            return false;
        }
    }
    return true;
}

bool DBManager::removeUser(const QString &name)
{
    //
    if(isExistUser(name))
    {
        //DELETE FROM 表名称 WHERE 列名称 = 值
        QString sql = tr("delete from %1 where name='%2'")
                .arg(user_table_name)
                .arg(name);
        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug() << "删除用户失败" << query.lastError().text();
            return false;
        }
    }
    return true;
}

QList<CultureData> DBManager::getCultrueDatas()
{
    QList<CultureData> datas;
    //逻辑
    QString sql = tr("select id,channel,readNo,indicatorNo,"
                     "cultureDate,cultureBeginTime,cultureEndTime,"
                     "actor,sterilizerType,sterilizeProgram,"
                     "cultureResult,compareChannel,"
                     "compareChannelCultureResult,cultureTemp from %1 ")
            .arg(culture_data_table_name);
    QSqlQuery query;
    if(query.exec(sql))
    {
        while(query.next())       //query.next()指向查找到的第一条记录，然后每次后移一条记录
        {
            CultureData data;
            data._id = query.value(0).toInt();
            data._channel = query.value(1).toInt();
            data._readNo = query.value(2).toString();
            data._indicatorNo = query.value(3).toString();
            data._cultureDate = QDateTime::fromString(query.value(4).toString(), g_data_time_format);
            data._cultureBeginTime = QDateTime::fromString(query.value(5).toString(), g_data_time_format);
            data._cultureEndTime = QDateTime::fromString(query.value(6).toString(), g_data_time_format);
            data._actor = query.value(7).toString();
            data._sterilizerType = query.value(8).toString();
            data._sterilizeProgram = query.value(9).toString();
            data._cultureResult = query.value(10).toString();
            data._compareChannel = query.value(11).toString();
            data._compareChannelCultureResult = query.value(12).toString();
            data._cultureTemp = query.value(13).toString();
            datas.append(data);
        }
    }
    else {
        qDebug() << "查询培养数据表数据失败" << query.lastError().text();
    }

    return datas;
}

int DBManager::getMaxCultureDataID()
{
    int id = 0;
    //SELECT MAX(column_name) FROM table_name
    //MAX函数不可用
    QString sql = tr("select id from %1").arg(culture_data_table_name);
    QSqlQuery query ;
    if(query.exec(sql))
    {
        while(query.next())
        {
            int temp_id = query.value(0).toInt();
            if(temp_id > id) id = temp_id;
        }
    }
    return id + 1;
}

bool DBManager::addCultureData(const CultureData &data)
{
    //INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
    QString sql = tr("insert into %1 (id,channel,readNo,indicatorNo,"
                     "cultureDate,cultureBeginTime,cultureEndTime,"
                     "actor,sterilizerType,sterilizeProgram,"
                     "cultureResult,compareChannel,"
                     "compareChannelCultureResult,cultureTemp) "
                     "values (%2,%3,'%4','%5','%6','%7','%8','%9',"
                     "'%10','%11','%12','%13','%14','%15')  ")
            .arg(culture_data_table_name)
            .arg(data._id)
            .arg(data._channel)
            .arg(data._readNo)
            .arg(data._indicatorNo)
            .arg(data._cultureDate.toString(g_data_time_format))
            .arg(data._cultureBeginTime.toString(g_data_time_format))
            .arg(data._cultureEndTime.toString(g_data_time_format))
            .arg(data._actor)
            .arg(data._sterilizerType)
            .arg(data._sterilizeProgram)
            .arg(data._cultureResult)
            .arg(data._compareChannel)
            .arg(data._compareChannelCultureResult)
            .arg(data._cultureTemp);
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qDebug() << "添加培养数据失败" << query.lastError().text();
        return  false;
    }

    return true;
}

bool DBManager::removeCultureData(const CultureData &data)
{
    //DELETE FROM 表名称 WHERE 列名称 = 值
    QString sql = tr("delete from %1 where id=%2")
            .arg(culture_data_table_name)
            .arg(data._id);
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qDebug() << "删除用户失败" << query.lastError().text();
        return false;
    }
    return true;
}

bool DBManager::removeCultureDataBefore(const QDateTime &datetime)
{
    QList<CultureData> datas = getCultrueDatas();
    foreach(CultureData data , datas)
    {
        if(data._cultureDate < datetime)
        {
            removeCultureData(data);
        }
    }

    return true;
}

void DBManager::init()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    database.setUserName("root");
    database.setPassword("123456");

    //open 会自动创建数据库
    if(database.open())
    {
        qDebug() << "Open database success!";
    }
    else
    {
        qDebug() << "Open database failed:" <<  database.lastError().text();
    }

    QStringList tables = database.tables();

    //创建用户表，如果不存在的话
    if(!tables.contains(user_table_name))
    {
        //CREATE TABLE 表名称 ( 列名称1 数据类型, 列名称2 数据类型, 列名称3 数据类型 )
        QString sql = tr("create table %1 ("
                         "id int primary key, "
                         "name varchar(30), "
                         "passwd varchar(20), "
                         "type int, "
                         "company varchar(40), "
                         "part varchar(100), "
                         "address varchar(100))")
                .arg(user_table_name);
        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug() << "创建用户表失败" << query.lastError().text();;
        }
        else
        {
            qDebug() << "创建用户表成功";
        }
    }
    if(!tables.contains(culture_data_table_name))
    {
        //CREATE TABLE 表名称 ( 列名称1 数据类型, 列名称2 数据类型, 列名称3 数据类型 )
        QString sql = tr("create table %1 ("
                         "id int primary key, "
                         "channel int, "
                         "readNo varchar(50),"
                         "indicatorNo varchar(50),"
                         "cultureDate varchar(20),"
                         "cultureBeginTime varchar(20),"
                         "cultureEndTime varchar(20),"
                         "actor varchar(20),"
                         "sterilizerType varchar(50),"
                         "sterilizeProgram varchar(50),"
                         "cultureResult varchar(200),"
                         "compareChannel varchar(20),"
                         "compareChannelCultureResult varchar(200),"
                         "cultureTemp varchar(20))")
                .arg(culture_data_table_name);

        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug() << "创建培养数据表失败" << query.lastError().text();;
        }
        else
        {
            qDebug() << "创建培养数据表成功";
        }
    }
}
