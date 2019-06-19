#ifndef REALTIMESTATEWGT_H
#define REALTIMESTATEWGT_H

#include <QWidget>
#include "common/common.h"

class ChannalWgt;

namespace Ui {
class RealTimeStateWgt;
}

class RealTimeStateWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeStateWgt(QWidget *parent = nullptr);
    ~RealTimeStateWgt();

public slots:
    void slotRefresh(const CultureData & data);

private:
    void init();

private:
    Ui::RealTimeStateWgt *ui;

    QList<ChannalWgt*> _wgts; //
};

#endif // REALTIMESTATEWGT_H
