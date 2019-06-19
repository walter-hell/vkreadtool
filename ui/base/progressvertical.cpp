#include "progressvertical.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#define PI 3.1415

ProgressVertical::ProgressVertical(QWidget *parent) : QWidget(parent)
{
    _max = 100;
    _min = 0;
    _value = 0;
    _step = 6;
    _radius = 20;
    _radius1 = 10;
    _color = QColor(Qt::darkGreen);
    _color.setAlphaF(0.6);
}

void ProgressVertical::setMax(qreal max)
{
    _max = max;
    update();
}

void ProgressVertical::setMin(qreal min)
{
    _min = min;
    update();
}

void ProgressVertical::setValue(qreal value)
{
    _value = value;
    update();
}

void ProgressVertical::setColor(QColor color)
{
    _color = color;
    update();
}

void ProgressVertical::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, 0);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawGraduate(&painter);
    //绘制进度
    drawProgress(&painter);
}

void ProgressVertical::drawGraduate(QPainter *p)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    p->save();
    QPen pen = p->pen();
    pen.setColor(Qt::black);
    pen.setWidthF(2);
    p->setPen(pen);
    p->setBrush(Qt::NoBrush);

    //画量杯
    p->drawLine(QPointF(-_radius * 3, _radius1 ),QPointF(_radius * 3, _radius1 ));
    p->drawLine(QPointF(-_radius * 3, _radius1 *3 ),QPointF(-_radius, _radius1 * 3 ));
    p->drawLine(QPointF(_radius * 3, _radius1 *3 ),QPointF(_radius, _radius1 * 3 ));
    p->drawLine(QPointF(_radius , _radius1 *3),
                QPointF(_radius , side - _radius1 - _radius));
    p->drawLine(QPointF(-_radius , _radius1 *3),
                QPointF(-_radius , side - _radius1 - _radius));
    p->drawArc(_radius * 3 - _radius1  , _radius1  , _radius1*2, _radius1*2, -90*16, 180*16);
    p->drawArc(-_radius * 3 - _radius1  , _radius1  , _radius1*2, _radius1*2, 90*16, 180*16);
    p->drawArc(-_radius , side - _radius1 - _radius*2  , _radius*2, _radius*2, 180*16, 180*16);
    p->restore();

    p->save();
    pen.setWidthF(1.5);
    p->setPen(pen);
    p->setBrush(Qt::NoBrush);

    //画刻度1
    qreal setpLen = (side - _radius1*4 - _radius)/(_step-1);
    for(int i = 0; i < _step-1; i++)
    {
        p->drawLine(QPointF(-_radius , side - _radius1 - _radius - setpLen * i),
                    QPointF(0 , side - _radius1 - _radius - setpLen * i));
    }

    p->restore();
}


void ProgressVertical::drawProgress(QPainter *p)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    p->save();
    p->setPen(Qt::NoPen);
    QBrush brush = p->brush();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_color);
    p->setBrush(brush);

    qreal h = (side - _radius1*4) * _value/(_max - _min);

    if(h >0 )
    {
        p->drawChord(-_radius , side - _radius1 - _radius*2  , _radius*2, _radius*2, 180*16, 180*16);
    }

    if(h > _radius)
    {
        p->drawRect(-_radius , side - _radius1 - _radius - h  , _radius*2, h);
    }

    p->restore();
}
