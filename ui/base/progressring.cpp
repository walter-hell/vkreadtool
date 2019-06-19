#include "progressring.h"

#include <QTimer>
#include <QPainter>

ProgressRing::ProgressRing(QWidget *parent):
    QWidget (parent)
{
    minValue = 0;                //最小值
    maxValue = 100;                //最大值
    value = 50;                   //目标值
    precision = 0;                  //精确度,小数点后几位

    clockWise = true;                 //顺时针逆时针
    showPercent = true;               //显示百分比
    alarmMode = 1;                  //警戒报警模式,进度为不同的颜色
    startAngle = 90;                 //起始角度
    ringPadding = 0;                //圆环间距
    ringWidth = 10;                  //圆环宽度

    animation = true;                 //是否启用动画显示
    animationStep = 100;           //动画显示时步长

    bgColor = QColor(Qt::white);                 //背景颜色
    textColor = QColor(Qt::darkGreen);               //文字颜色
    ringColor = QColor(Qt::darkGreen);               //圆环颜色
    ringBgColor = QColor(Qt::darkGreen);             //圆环进度背景
    circleColor = QColor(Qt::white);             //中心圆颜色

    ringValue1 = 0;                 //环形值1
    ringValue2 = 50;                 //环形值2
    ringValue3 = 100;                 //环形值3

    ringColor1 = QColor(Qt::darkGreen);              //环形颜色1
    ringColor2 = QColor(Qt::darkGreen);              //环形颜色2
    ringColor3 = QColor(Qt::darkRed);              //环形颜色3

    reverse = false;                   //是否往回走
    currentValue = 0;            //当前值
    timer = new QTimer();                  //定时器绘制动画
}

ProgressRing::~ProgressRing()
{

}

void ProgressRing::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制进度
    drawRing(&painter);

    //绘制间隔,重新绘制一个圆遮住,产生间距效果
    if (ringPadding > 0) {
        drawPadding(&painter);
    }

    //绘制中间圆
    drawCircle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void ProgressRing::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    //这里有个技巧,如果没有间距则设置成圆环的背景色
    painter->setBrush(ringPadding == 0 ? ringBgColor : bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawRing(QPainter *painter)
{
    int radius = 99 - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(ringColor);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //如果逆时针
    if (!clockWise) {
        angleCurrent = -angleCurrent;
        angleOther = -angleOther;
    }

    //动态设置当前进度颜色
    QColor color = ringColor;
    if (alarmMode == 1) {
        if (currentValue >= ringValue3) {
            color = ringColor3;
        } else if (currentValue >= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor1;
        }
    } else if (alarmMode == 2) {
        if (currentValue <= ringValue1) {
            color = ringColor1;
        } else if (currentValue <= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor3;
        }
    }

    //绘制当前值饼圆
    painter->setBrush(color);
    painter->drawPie(rect, (startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(ringBgColor);
    painter->drawPie(rect, (startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void ProgressRing::drawPadding(QPainter *painter)
{
    int radius = 99 - ringWidth - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawCircle(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawValue(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(textColor);

    QFont font;
    int fontSize = radius - (showPercent ? 20 : 6);
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue;
    if (showPercent) {
        double percent = (currentValue * 100) / (maxValue - minValue);
        strValue = QString("%1%").arg(percent, 0, 'f', precision);
    } else {
        strValue = QString("%1").arg(currentValue, 0, 'f', precision);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void ProgressRing::updateValue()
{

}

double ProgressRing::getMinValue() const
{
    return minValue;
}

double ProgressRing::getMaxValue() const
{
    return maxValue;
}

double ProgressRing::getValue() const
{
    return value;
}

int ProgressRing::getPrecision() const
{
    return precision;
}

bool ProgressRing::getClockWise() const
{
    return clockWise;
}

bool ProgressRing::getShowPercent() const
{
    return showPercent;
}

int ProgressRing::getAlarmMode() const
{
    return alarmMode;
}

int ProgressRing::getStartAngle() const
{
    return startAngle;
}

int ProgressRing::getRingPadding() const
{
    return ringPadding;
}

int ProgressRing::getRingWidth() const
{
    return ringWidth;
}

bool ProgressRing::getAnimation() const
{
    return animation;
}

double ProgressRing::getAnimationStep() const
{
    return animationStep;
}

QColor ProgressRing::getBgColor() const
{
    return bgColor;
}

QColor ProgressRing::getTextColor() const
{
    return textColor;
}

QColor ProgressRing::getRingColor() const
{
    return ringColor;
}

QColor ProgressRing::getRingBgColor() const
{
    return  ringBgColor;
}

QColor ProgressRing::getCircleColor() const
{
    return circleColor;
}

int ProgressRing::getRingValue1() const
{
    return ringValue1;
}

int ProgressRing::getRingValue2() const
{
    return  ringValue2;
}

int ProgressRing::getRingValue3() const
{
    return ringValue3;
}

QColor ProgressRing::getRingColor1() const
{
    return  ringColor1;
}

QColor ProgressRing::getRingColor2() const
{
    return ringColor2;
}

QColor ProgressRing::getRingColor3() const
{
    return ringColor3;
}

QSize ProgressRing::sizeHint() const
{
    return  this->size();
}

QSize ProgressRing::minimumSizeHint() const
{
    return this->minimumSize();
}

void ProgressRing::setRange(double _minValue, double _maxValue)
{
    this->minValue = _minValue;
    this->maxValue = _maxValue;
    update();
}

void ProgressRing::setRange(int _minValue, int _maxValue)
{
    this->minValue = _minValue;
    this->maxValue = _maxValue;
    update();
}

void ProgressRing::setMinValue(double _minValue)
{
    this->minValue = _minValue;
    update();
}

void ProgressRing::setMaxValue(double _maxValue)
{
    this->maxValue = _maxValue;
    update();
}

void ProgressRing::setValue(double _value)
{
    this->value = _value;
    update();
}

void ProgressRing::setValue(int _value)
{
    this->value = _value;
    update();
}

void ProgressRing::setPrecision(int _precision)
{
    this->precision = _precision;
    update();
}

void ProgressRing::setClockWise(bool _clockWise)
{
    this->clockWise = _clockWise;
    update();
}

void ProgressRing::setShowPercent(bool _showPercent)
{
    this->showPercent = _showPercent;
    update();
}

void ProgressRing::setAlarmMode(int _alarmMode)
{
    this->alarmMode = _alarmMode;
    update();
}

void ProgressRing::setStartAngle(int _startAngle)
{
    this->startAngle = _startAngle;
    update();
}

void ProgressRing::setRingPadding(int _ringPadding)
{
    this->ringPadding = _ringPadding;
    update();
}

void ProgressRing::setRingWidth(int _ringWidth)
{
    this->ringWidth = _ringWidth;
    update();
}

void ProgressRing::setAnimation(bool _animation)
{
    this->animation = _animation;
    update();
}

void ProgressRing::setAnimationStep(double _animationStep)
{
    this->animationStep = _animationStep;
    update();
}

void ProgressRing::setBgColor(const QColor &_bgColor)
{
    this->bgColor = _bgColor;
    update();
}

void ProgressRing::setTextColor(const QColor &_textColor)
{
    this->textColor = _textColor;
    update();
}

void ProgressRing::setRingColor(const QColor &_ringColor)
{
    this->ringColor = _ringColor;
    update();
}

void ProgressRing::setRingBgColor(const QColor &_ringBgColor)
{
    this->ringBgColor = _ringBgColor;
    update();
}

void ProgressRing::setCircleColor(const QColor &_circleColor)
{
    this->circleColor = _circleColor;
    update();
}

void ProgressRing::setRingValue1(int _ringValue1)
{
    this->ringValue1 = _ringValue1;
    update();
}

void ProgressRing::setRingValue2(int _ringValue2)
{
    this->ringValue2 = _ringValue2;
    update();
}

void ProgressRing::setRingValue3(int _ringValue3)
{
    this->ringValue3 = _ringValue3;
    update();
}

void ProgressRing::setRingColor1(const QColor &_ringColor1)
{
    this->ringColor1 = _ringColor1;
    update();
}

void ProgressRing::setRingColor2(const QColor &_ringColor2)
{
    this->ringColor2 = _ringColor2;
    update();
}

void ProgressRing::setRingColor3(const QColor &_ringColor3)
{
    this->ringColor3 = _ringColor3;
    update();
}

void ProgressRing::setCurrentValue(double curV)
{
    currentValue = curV;
    update();
}

