#include "datahandle.h"
#include <QDebug>

DataHandle::DataHandle(QObject *parent) : QThread(parent)
{

}

DataHandle *DataHandle::getIns()
{
    static DataHandle  handle;
    return &handle;
}

void DataHandle::slotReciveData(const QByteArray &data)
{
    _mutex.lock();
    _buff.append(data);
    _mutex.unlock();
}

void DataHandle::run()
{
    while(1)
    {
        _mutex.lock();

        msleep(1000);

        analysisData();

        _mutex.unlock();
    }
}

void DataHandle::analysisData()
{
    //处理数据_buff



    //test
    CultureData data;
    data._channel = 1;
    static int id = 0;
    data._id = id;
    id += 1;
    //发送解析出来的数据
    signalCultureDataComming(data);
    qDebug() << "DataHandle::analysisData()  --->" << id;

    //添加数据到历史数据记录中，超过上限时，删除老数据
    if(_datas.count() >= MAX_CULTUREDATA_COUNT)
    {
        _datas.removeFirst();
    }
    _datas.append(data);
    //test end
}
