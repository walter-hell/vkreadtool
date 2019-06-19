#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QtDebug>

#include "ui/historywgt.h"
#include "ui/realtimestatewgt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //添加菜单栏
    QMenuBar *menuBar = new QMenuBar(this);

    //-设置菜单
    QMenu * settingMenu = menuBar->addMenu(QIcon(""), QString("设置"));
    //--用户管理
    QAction * userMgrAc = settingMenu->addAction(QIcon(""), QString("用户管理"));
    connect(userMgrAc, &QAction::triggered, this, &MainWindow::slotUserMgr);
    //--备份设置
    QAction * backupSetAc = settingMenu->addAction(QIcon(""), QString("备份设置"));
    connect(backupSetAc, &QAction::triggered, this, &MainWindow::slotBackupSet);
    //--退出
    QAction * exitAc = settingMenu->addAction(QIcon(""), QString("退出"));
    connect(exitAc, &QAction::triggered, this, &MainWindow::slotExit);

    //-网络配置菜单
    QMenu * netConfigMenu = menuBar->addMenu(QIcon(""), QString("网络配置"));
    QAction * baseSetAc = netConfigMenu->addAction(QIcon(""), QString("基本设置"));
    connect(baseSetAc, &QAction::triggered, this, &MainWindow::slotBaseSet);
    QAction * netSetAc = netConfigMenu->addAction(QIcon(""), QString("网络设置"));
    connect(netSetAc, &QAction::triggered, this, &MainWindow::slotNetSet);
    QAction * paraSetAc = netConfigMenu->addAction(QIcon(""), QString("参数设置"));
    connect(paraSetAc, &QAction::triggered, this, &MainWindow::slotParaSet);
    QAction * channelSetAc = netConfigMenu->addAction(QIcon(""), QString("通道设置"));
    connect(channelSetAc, &QAction::triggered, this, &MainWindow::slotChannelSet);

    //-查看
    QAction * viewAc = menuBar->addAction(QString("查看"), this, &MainWindow::slotView);

    //-关于
    QAction * aboutAc = menuBar->addAction(QString("关于VK"), this, &MainWindow::slotAbout);

    //添加到界面上
    this->setMenuBar(menuBar);



    QToolBar * toolBar = new QToolBar(QString("工具栏"), this);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setHidden(false);
    toolBar->addAction(QIcon(""), QString("实时状态"), this, &MainWindow::slotRealTimeState);
    toolBar->addAction(QIcon(""), QString("历史数据"), this, &MainWindow::slotHistory);
    toolBar->addAction(QIcon(""), QString("导出文件"), this, &MainWindow::slotExportFile);
    toolBar->addAction(QIcon(""), QString("打印"), this, &MainWindow::slotPrint);
    toolBar->addAction(QIcon(""), QString("截图"), this, &MainWindow::slotScreenShot);
    toolBar->addAction(QIcon(""), QString("导出报表"), this, &MainWindow::slotExportReport);
    toolBar->addAction(QIcon(""), QString("追溯输入"), this, &MainWindow::slotBackToEnter);
    toolBar->addAction(QIcon(""), QString("帮助"), this, &MainWindow::slotHelp);
    this->addToolBar(Qt::TopToolBarArea, toolBar);


    //其他界面初始化
    _realTimeStateWgt = new RealTimeStateWgt(this);
    ui->stackedWidget->addWidget(_realTimeStateWgt);

    _historyWgt = new HistoryWgt(this);
    ui->stackedWidget->addWidget(_historyWgt);
}

void MainWindow::slotUserMgr()
{
    qDebug() << "User Manager clicked";
}

void MainWindow::slotBackupSet()
{

}

void MainWindow::slotExit()
{

}

void MainWindow::slotBaseSet()
{

}

void MainWindow::slotNetSet()
{

}

void MainWindow::slotParaSet()
{

}

void MainWindow::slotChannelSet()
{

}

void MainWindow::slotView()
{
    qDebug() << "View Menu clicked";
}

void MainWindow::slotAbout()
{
    qDebug() << "About Menu clicked";
}

void MainWindow::slotRealTimeState()
{
    ui->stackedWidget->setCurrentWidget(_realTimeStateWgt);
}

void MainWindow::slotHistory()
{
    ui->stackedWidget->setCurrentWidget(_historyWgt);
}

void MainWindow::slotExportFile()
{

}

void MainWindow::slotPrint()
{

}

void MainWindow::slotScreenShot()
{

}

void MainWindow::slotExportReport()
{

}

void MainWindow::slotBackToEnter()
{

}

void MainWindow::slotHelp()
{

}
