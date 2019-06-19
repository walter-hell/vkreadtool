#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HistoryWgt;
class RealTimeStateWgt;

namespace Ui {
class MainWindow;
}

//主界面
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //界面初始化
    void init();

private slots:
    //菜单栏反馈函数
    void slotUserMgr();     //用户管理
    void slotBackupSet();   //备份设置
    void slotExit();        //退出
    void slotBaseSet();     //基础设置
    void slotNetSet();      //网络设置
    void slotParaSet();     //参数设置
    void slotChannelSet();  //通道设置
    void slotView();        //不知道参看什么
    void slotAbout();       //关于界面

    //工具条反馈函数
    void slotRealTimeState();//展示实时数据
    void slotHistory();     //展示历史数据,表格
    void slotExportFile();   //导出文件，execl、pdf
    void slotPrint();       //导出文件并打印
    void slotScreenShot();  //软件截图
    void slotExportReport();//导出报表
    void slotBackToEnter(); //追溯输入
    void slotHelp();        //帮助说明文档

private:
    Ui::MainWindow *ui;


    HistoryWgt * _historyWgt;
    RealTimeStateWgt * _realTimeStateWgt;
};

#endif // MAINWINDOW_H
