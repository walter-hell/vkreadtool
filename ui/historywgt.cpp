#include "historywgt.h"
#include "ui_historywgt.h"
#include <QtGui/QStandardItemModel>

#include "db/dbmanager.h"

HistoryWgt::HistoryWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWgt)
{
    ui->setupUi(this);
    init();
}

HistoryWgt::~HistoryWgt()
{
    delete ui;
}

void HistoryWgt::refresh()
{
    DBManager * db = DBManager::getIns();
    QList<CultureData> datas = db->getCultrueDatas();

    //清除数据
    _model->removeRows(0, _model->rowCount());

    int row = 0;
    foreach(CultureData data, datas)
    {
        _model->insertRow(row);
        QStandardItem *item0 = new QStandardItem;
        item0->setData(data._id, Qt::DisplayRole);
        _model->setItem(row,0,item0);
        QStandardItem *item1 = new QStandardItem;
        item1->setData(data._channel, Qt::DisplayRole);
        _model->setItem(row,1,item1);
        QStandardItem *item2 = new QStandardItem;
        item2->setData(data._readNo, Qt::DisplayRole);
        _model->setItem(row,2,item2);
        QStandardItem *item3 = new QStandardItem;
        item3->setData(data._indicatorNo, Qt::DisplayRole);
        _model->setItem(row,3,item3);
        QStandardItem *item4 = new QStandardItem;
        item4->setData(data._cultureDate, Qt::DisplayRole);
        _model->setItem(row,4,item4);
        QStandardItem *item5 = new QStandardItem;
        item5->setData(data._cultureBeginTime, Qt::DisplayRole);
        _model->setItem(row,5,item5);
        QStandardItem *item6 = new QStandardItem;
        item6->setData(data._cultureEndTime, Qt::DisplayRole);
        _model->setItem(row,6,item6);
        QStandardItem *item7 = new QStandardItem;
        item7->setData(data._actor, Qt::DisplayRole);
        _model->setItem(row,7,item7);
        QStandardItem *item8 = new QStandardItem;
        item8->setData(data._sterilizerType, Qt::DisplayRole);
        _model->setItem(row,8,item8);
        QStandardItem *item9 = new QStandardItem;
        item9->setData(data._sterilizeProgram, Qt::DisplayRole);
        _model->setItem(row,9,item9);
        QStandardItem *item10 = new QStandardItem;
        item10->setData(data._cultureResult, Qt::DisplayRole);
        _model->setItem(row,10,item10);
        QStandardItem *item11 = new QStandardItem;
        item11->setData(data._compareChannel, Qt::DisplayRole);
        _model->setItem(row,11,item11);
        QStandardItem *item12 = new QStandardItem;
        item12->setData(data._compareChannelCultureResult, Qt::DisplayRole);
        _model->setItem(row,12,item12);
        QStandardItem *item13 = new QStandardItem;
        item13->setData(data._cultureTemp, Qt::DisplayRole);
        _model->setItem(row,13,item13);
    }
}

void HistoryWgt::slotCheckBoxBegin()
{
    ui->dateTimeEdit_begin->setEnabled(ui->checkBox_begin->isChecked());
}

void HistoryWgt::slotCheckBoxEnd()
{
    ui->dateTimeEdit_end->setEnabled(ui->checkBox_end->isChecked());
}

void HistoryWgt::init()
{
    ui->comboBox_channel->addItem(tr("全部"));
    ui->comboBox_channel->addItem(tr("通道1"));
    ui->comboBox_channel->addItem(tr("通道2"));
    ui->comboBox_channel->addItem(tr("通道3"));
    ui->comboBox_channel->addItem(tr("通道4"));
    ui->comboBox_channel->addItem(tr("通道5"));
    ui->comboBox_channel->addItem(tr("通道6"));
    ui->comboBox_channel->addItem(tr("通道7"));
    ui->comboBox_channel->addItem(tr("通道8"));

    ui->dateTimeEdit_begin->setDate(QDate::currentDate().addDays(-30));
    ui->dateTimeEdit_begin->setTime(QTime(0,0));
    connect(ui->checkBox_begin, &QCheckBox::clicked,this, &HistoryWgt::slotCheckBoxBegin);

    ui->dateTimeEdit_end->setDate(QDate::currentDate());
    ui->dateTimeEdit_end->setTime(QTime(0,0));
    connect(ui->checkBox_end, &QCheckBox::clicked,this, &HistoryWgt::slotCheckBoxEnd);

    ui->comboBox_actor->addItem(tr("全部"));
    //添加已存在的其他操作者

    ui->comboBox_result->addItem(tr("全部"));
    ui->comboBox_result->addItem(tr("阳性+"));
    ui->comboBox_result->addItem(tr("阴性-"));

    _model = new QStandardItemModel(ui->tableView);
    QStringList labels;
    labels << tr("序号") << tr("通道号") << tr("阅读器编号") << tr("指示剂批次号")
           << tr("培养日期") << tr("培养开始时间") << tr("培养结束时间") << tr("操作员")
           << tr("灭菌器种类") << tr("灭菌程序") << tr("培养结果") << tr("对照通道")
           << tr("对照通道培养结果") << tr("培养温度");
    _model->setHorizontalHeaderLabels(labels);
    ui->tableView->setModel(_model);
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    refresh();
}
