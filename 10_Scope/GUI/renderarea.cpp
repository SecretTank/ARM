#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(oscope_data *data, QWidget *parent)
    : QWidget(parent)
{
    adc_data = data;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //painter = QPainter(this);
    boom = new QPixmap (1200, 400);
    img_painter.begin(boom);
    boom->fill(Qt::transparent);
    background = new QPixmap("/home/bijan/Project/ARM/ARM/10_Scope/GUI/Resources/path4522.png");
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(1200, 400);
}

void RenderArea::renderPoint()
{
    //palette().base().setColor(QColor(0,0,0,0));
    //img_painter.eraseRect(10*x, 0, 10, this->height());
    //img_painter.setBrush(palette().dark().color());
    //img_painter.drawEllipse(QPoint(10*x+5,y),5,5);
}

void RenderArea::paint(QPainter *painter)
{
    painter.drawPixmap(0,0,*background);
    painter.drawPixmap(0,0,*boom);
    //qDebug() << "Hi";
}
