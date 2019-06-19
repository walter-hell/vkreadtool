#ifndef SPLISTEN_H
#define SPLISTEN_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

//监听串口，并读取串口传过来的数据
class SPListen : public QObject
{
    Q_OBJECT
private:
    explicit SPListen(QObject *parent = nullptr);

public:
    static SPListen * getIns();

    //获取可以连接成功的串口列表信息
    QList<QSerialPortInfo> getAvailableSPInfoLists();

    //设置串口名称
    void setPortName(const QString & portname);
    //设置串口传输波特率
    void setBaudRate(const QString & baudrate);

    //连接串口，连接成功就开始就收串口数据
    void linkSP();

signals:
    //发送串口接收的数据
    void signalReciveData(const QByteArray & data);

public slots:

private slots:
    void slotReciveData();

private:
    QString _portName;
    QSerialPort::BaudRate _baudRate;

    QSerialPort * _sp;
};

#endif // SPLISTEN_H
