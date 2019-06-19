#include "splisten.h"
#include "data/datahandle.h"

SPListen::SPListen(QObject *parent) : QObject(parent)
{
    _portName = "com1";
    _baudRate = QSerialPort::UnknownBaud;
    _sp = nullptr;
    connect(this, &SPListen::signalReciveData, DataHandle::getIns(), &DataHandle::slotReciveData);
}

SPListen *SPListen::getIns()
{
    static SPListen sp;
    return &sp;
}

QList<QSerialPortInfo> SPListen::getAvailableSPInfoLists()
{
    QList<QSerialPortInfo> spList;
    //查找可用的串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            spList.append(info);
            serial.close();
        }
    }

    return spList;
}

void SPListen::setPortName(const QString &portname)
{
    _portName = portname;
}

void SPListen::setBaudRate(const QString &baudrate)
{
    if(baudrate.contains("1200"))
    {
        _baudRate = QSerialPort::Baud1200;
    }
    else if(baudrate.contains("2400"))
    {
        _baudRate = QSerialPort::Baud2400;
    }
    else if(baudrate.contains("4800"))
    {
        _baudRate = QSerialPort::Baud4800;
    }
    else if(baudrate.contains("19200"))
    {
        _baudRate = QSerialPort::Baud19200;
    }
    else if(baudrate.contains("38400"))
    {
        _baudRate = QSerialPort::Baud38400;
    }
    else if(baudrate.contains("57600"))
    {
        _baudRate = QSerialPort::Baud57600;
    }
    else if(baudrate.contains("115200"))
    {
        _baudRate = QSerialPort::Baud115200;
    }
}

void SPListen::linkSP()
{
    if(_sp == nullptr)
    {
        _sp->clear();
        _sp->close();
        _sp->deleteLater();
    }

    _sp = new QSerialPort(this);
    _sp->setPortName(_portName);
    _sp->setBaudRate(_baudRate);

    if(_sp->open(QIODevice::ReadWrite))
    {
        connect(_sp, &QSerialPort::readyRead, this, &SPListen::slotReciveData);
    }
}

void SPListen::slotReciveData()
{
    if(_sp)
    {
        QByteArray buff;
        buff = _sp->readAll();
        if(buff.isEmpty()) return;
        emit signalReciveData(buff);
    }
}
