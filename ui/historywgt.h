#ifndef HISTORYWGT_H
#define HISTORYWGT_H

#include <QWidget>

class QStandardItemModel;

namespace Ui {
class HistoryWgt;
}

class HistoryWgt : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWgt(QWidget *parent = nullptr);
    ~HistoryWgt();

public:
    void refresh();

private slots:
    void slotCheckBoxBegin();
    void slotCheckBoxEnd();

private:
    void init(); //界面初始化


private:
    Ui::HistoryWgt *ui;
    QStandardItemModel * _model;
};

#endif // HISTORYWGT_H
