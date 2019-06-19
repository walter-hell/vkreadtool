#include "channalwgt.h"
#include "ui_channalwgt.h"

ChannalWgt::ChannalWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannalWgt)
{
    ui->setupUi(this);
    init();
}

ChannalWgt::~ChannalWgt()
{
    delete ui;
}

void ChannalWgt::setCultureData(const CultureData &data)
{
    //设置展示数据

    ui->label_num->setNum(data._channel);

    ui->widget_graduate->setValue(rand()%100);

    ui->widget_progress->setCurrentValue(rand()%100);

    ui->lineEdit_workremaintime->setText(QDateTime::currentDateTime().toString(g_data_time_format));

    ui->lineEdit_temp->setText(data._cultureTemp);

    ui->lineEdit_result->setText(data._cultureResult);

    ui->lineEdit_error->setText(tr(""));
}

void ChannalWgt::init()
{
    ui->widget_graduate->setMax(100);
    ui->widget_graduate->setMin(0);
    ui->widget_progress->setMaxValue(100);
    ui->widget_progress->setMinValue(0);
}
