#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include <QThread>
#include <QMutex>
#include "common/common.h"

//负责处理接受的数据
class DataHandle : public QThread
{
    Q_OBJECT
private:
    explicit DataHandle(QObject *parent = nullptr);
public:
    static DataHandle * getIns();

signals:
    void signalCultureDataComming(const CultureData & data);

public slots:
    void slotReciveData(const QByteArray & data);

protected:
    virtual void run();

private:
    //解析数据
    void analysisData();

private:
    QByteArray _buff;               //临时数据
    QList<CultureData> _datas;      //已保存到数据
    QMutex _mutex;                  //线程数据锁
};

#endif // DATAHANDLE_H
