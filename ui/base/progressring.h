#ifndef PROGRESSRING_H
#define PROGRESSRING_H

/**
 * 环形进度条控件 作者:feiyangqingyun(QQ:517216493) 2019-5-1
 * 1:可设置范围值,支持负数值
 * 2:可设置精确度,最大支持小数点后3位
 * 3:可设置起始角度
 * 4:可设置三种值+三种颜色,启用自动检测值后绘制不同的颜色
 * 5:可设置是否启用动画效果以及动画效果每次移动的步长
 * 6:可设置背景颜色/文字颜色/进度颜色/中间圆颜色
 * 7:可设置值警戒报警比较模式 0-不比较 1-最大值报警 2-最小值报警
 * 8:可设置显示的值是百分比
 * 9:可设置圆环与背景之间的距离即间距
 * 10:可设置圆环的宽度
 * 11:可设置圆环背景颜色,形成两种颜色差
 * 12:可设置顺时针逆时针转
 * 13:自适应窗体拉伸,刻度尺和文字自动缩放
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ProgressRing : public QWidget
#else

class QTimer;

class ProgressRing : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)
    Q_PROPERTY(int alarmMode READ getAlarmMode WRITE setAlarmMode)
    Q_PROPERTY(int startAngle READ getStartAngle WRITE setStartAngle)
    Q_PROPERTY(int ringPadding READ getRingPadding WRITE setRingPadding)
    Q_PROPERTY(int ringWidth READ getRingWidth WRITE setRingWidth)

    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ getAnimationStep WRITE setAnimationStep)

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor ringColor READ getRingColor WRITE setRingColor)
    Q_PROPERTY(QColor ringBgColor READ getRingBgColor WRITE setRingBgColor)
    Q_PROPERTY(QColor circleColor READ getCircleColor WRITE setCircleColor)

    Q_PROPERTY(int ringValue1 READ getRingValue1 WRITE setRingValue1)
    Q_PROPERTY(int ringValue2 READ getRingValue2 WRITE setRingValue2)
    Q_PROPERTY(int ringValue3 READ getRingValue3 WRITE setRingValue3)

    Q_PROPERTY(QColor ringColor1 READ getRingColor1 WRITE setRingColor1)
    Q_PROPERTY(QColor ringColor2 READ getRingColor2 WRITE setRingColor2)
    Q_PROPERTY(QColor ringColor3 READ getRingColor3 WRITE setRingColor3)

public:
    explicit ProgressRing(QWidget *parent = 0);
    ~ProgressRing();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawRing(QPainter *painter);
    void drawPadding(QPainter *painter);
    void drawCircle(QPainter *painter);
    void drawValue(QPainter *painter);

private slots:
    void updateValue();

private:
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标值
    int precision;                  //精确度,小数点后几位

    bool clockWise;                 //顺时针逆时针
    bool showPercent;               //显示百分比
    int alarmMode;                  //警戒报警模式,进度为不同的颜色
    int startAngle;                 //起始角度
    int ringPadding;                //圆环间距
    int ringWidth;                  //圆环宽度

    bool animation;                 //是否启用动画显示
    double animationStep;           //动画显示时步长

    QColor bgColor;                 //背景颜色
    QColor textColor;               //文字颜色
    QColor ringColor;               //圆环颜色
    QColor ringBgColor;             //圆环进度背景
    QColor circleColor;             //中心圆颜色

    int ringValue1;                 //环形值1
    int ringValue2;                 //环形值2
    int ringValue3;                 //环形值3

    QColor ringColor1;              //环形颜色1
    QColor ringColor2;              //环形颜色2
    QColor ringColor3;              //环形颜色3

    bool reverse;                   //是否往回走
    double currentValue;            //当前值
    QTimer *timer;                  //定时器绘制动画

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    int getPrecision()              const;

    bool getClockWise()             const;
    bool getShowPercent()           const;
    int getAlarmMode()              const;
    int getStartAngle()             const;
    int getRingPadding()            const;
    int getRingWidth()              const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    QColor getBgColor()             const;
    QColor getTextColor()           const;
    QColor getRingColor()           const;
    QColor getRingBgColor()         const;
    QColor getCircleColor()         const;

    int getRingValue1()             const;
    int getRingValue2()             const;
    int getRingValue3()             const;

    QColor getRingColor1()          const;
    QColor getRingColor2()          const;
    QColor getRingColor3()          const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置范围值
    void setRange(double _minValue, double _maxValue);
    void setRange(int _minValue, int _maxValue);

    //设置最大最小值
    void setMinValue(double _minValue);
    void setMaxValue(double _maxValue);

    //设置目标值
    void setValue(double _value);
    void setValue(int _value);

    //设置精确度
    void setPrecision(int _precision);

    //设置顺时针逆时针转
    void setClockWise(bool _clockWise);
    //设置显示百分比
    void setShowPercent(bool _showPercent);
    //设置启动自动检验
    void setAlarmMode(int _alarmMode);
    //设置起始角度
    void setStartAngle(int _startAngle);
    //设置圆环间距
    void setRingPadding(int _ringPadding);
    //设置圆环宽度
    void setRingWidth(int _ringWidth);

    //设置是否启用动画显示
    void setAnimation(bool _animation);
    //设置动画显示的步长
    void setAnimationStep(double _animationStep);

    //设置背景颜色
    void setBgColor(const QColor &_bgColor);
    //设置文本颜色
    void setTextColor(const QColor &_textColor);
    //设置圆环进度颜色
    void setRingColor(const QColor &_ringColor);
    //设置圆环背景颜色
    void setRingBgColor(const QColor &_ringBgColor);
    //设置中心圆颜色
    void setCircleColor(const QColor &_circleColor);

    //设置三种值
    void setRingValue1(int _ringValue1);
    void setRingValue2(int _ringValue2);
    void setRingValue3(int _ringValue3);

    //设置三种颜色
    void setRingColor1(const QColor &_ringColor1);
    void setRingColor2(const QColor &_ringColor2);
    void setRingColor3(const QColor &_ringColor3);

    void setCurrentValue(double curV);

Q_SIGNALS:
    void valueChanged(int value);
};

#endif // PROGRESSRING_H


