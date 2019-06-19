#include "realtimestatewgt.h"
#include "ui_realtimestatewgt.h"
#include <QtWidgets/QLayout>
#include "channalwgt.h"
#include "data/datahandle.h"
#include <QDebug>

RealTimeStateWgt::RealTimeStateWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeStateWgt)
{
    ui->setupUi(this);
    init();
}

RealTimeStateWgt::~RealTimeStateWgt()
{
    delete ui;
}

void RealTimeStateWgt::slotRefresh(const CultureData &data)
{
    if(data._channel <=0 || data._channel > 8)
    {
        return ;
    }
    _wgts.at(data._channel-1)->setCultureData(data);
}

void RealTimeStateWgt::init()
{
    //设置布局
    QHBoxLayout *layout = new QHBoxLayout;
    ui->scrollAreaWidget->setLayout(layout);

    for(int i = 0; i < 8; i++)
    {
        ChannalWgt * wgt = new ChannalWgt(this);
        _wgts.append(wgt);
        layout->addWidget(wgt);
    }

    connect(DataHandle::getIns(), &DataHandle::signalCultureDataComming,
            this, &RealTimeStateWgt::slotRefresh);
}
