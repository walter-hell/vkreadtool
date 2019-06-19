#ifndef PROGRESSVERTICAL_H
#define PROGRESSVERTICAL_H

#include <QWidget>

class QPainter;

class ProgressVertical : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressVertical(QWidget *parent = nullptr);

    void setMax(qreal max);
    void setMin(qreal min);
    void setValue(qreal value);
    void setColor(QColor color);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void drawGraduate(QPainter * p);
    void drawProgress(QPainter * p);

private:
    qreal _max;
    qreal _min;
    qreal _value;
    int _step;
    qreal _radius;
    qreal _radius1;
    QColor _color;
};

#endif // PROGRESSVERTICAL_H
