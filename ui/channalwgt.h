#ifndef CHANNALWGT_H
#define CHANNALWGT_H

#include <QWidget>
#include "common/common.h"

namespace Ui {
class ChannalWgt;
}

class ChannalWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChannalWgt(QWidget *parent = nullptr);
    ~ChannalWgt();

    void setCultureData(const CultureData & data);

private:
    void init();

private:
    Ui::ChannalWgt *ui;
};

#endif // CHANNALWGT_H
