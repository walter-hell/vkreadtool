#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDateTime>
#include <QMetaType>

#define MAX_CULTUREDATA_COUNT 2000

const QString g_data_time_format = "yyyy-MM-dd HH:mm:ss";

enum USER_TYPE
{
    USER_ADMIN  = 0,    //管理员
    USER_NORMAL  = 1,   //一般用户
};

struct User
{
    int _id;            //id,序号
    QString _name;      //用户名称
    QString _passwd;    //用户密码
    USER_TYPE _type;    //用户类型
    QString _company;   //单位名称
    QString _part;      //单位部门名称
    QString _address;    //单位地址
    User()
    {
        _id = 0;
        _type = USER_NORMAL;
    }
};


struct CultureData
{
    int _id;                //序号 0
    int _channel;           //通道号 1
    QString _readNo;        //阅读器编号 2
    QString _indicatorNo;   //指示剂批次号 3
    QDateTime _cultureDate;     //培养日期 4
    QDateTime _cultureBeginTime;     //培养开始时间 5
    QDateTime _cultureEndTime;     //培养结束时间 6
    QString _actor;             //操作员 7
    QString _sterilizerType;    //灭菌器种类 8
    QString _sterilizeProgram;  //灭菌程序 9
    QString _cultureResult;     //培养结果 10
    QString _compareChannel;    //对照通道 11
    QString _compareChannelCultureResult;    //对照通道培养结果 12
    QString _cultureTemp;       //培养温度 13

    CultureData()
    {
        _id = 0;
        _channel = 0;
    }
};

Q_DECLARE_METATYPE(CultureData);


#endif // COMMON_H
