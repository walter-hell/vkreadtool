#include "ui/mainwindow.h"
#include <QApplication>

//test
#include "db/dbmanager.h"
#include "data/datahandle.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<CultureData>("CultureData");
    qRegisterMetaType<CultureData>("CultureData&");

    DBManager *db = DBManager::getIns();

    /*
    User user;
    user._id = db->getMaxUserID();
    user._name = "test";
    user._type = USER_NORMAL;
    user._passwd = "123";
    user._company = "company";
    user._part = "part";
    user._address = "chengdu";

    db->addUser(user);
    user._id = db->getMaxUserID();
    user._address = "shuangliu ";
    db->addUser(user);
    user._id = db->getMaxUserID();
    user._name = "test1";
    user._address = "shuangliu1111111 ";
    db->addUser(user);
    db->removeUser("test");

    db->getUsers();
    */

    /*
    CultureData data;
    data._id = db->getMaxCultureDataID();
    data._channel = 10;
    data._cultureDate = QDateTime::currentDateTime() ;
    db->addCultureData(data);

    data._id = db->getMaxCultureDataID();
    data._channel = 1000;
    data._cultureBeginTime = QDateTime::currentDateTime() ;
    db->addCultureData(data);

    db->getCultrueDatas();

    db->removeCultureData(data);
    db->removeCultureDataBefore(QDateTime::fromString("2019-06-16 16:49:23", "yyyy-MM-dd HH:mm:ss"));

    */

    MainWindow w;
    w.show();

    DataHandle::getIns()->start();

    return a.exec();
}
