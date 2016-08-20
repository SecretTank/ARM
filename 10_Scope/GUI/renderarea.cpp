#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //painter = QPainter(this);
    boom = new QPixmap (1200, 400);
    img_painter.begin(boom);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(1200, 400);
}

void RenderArea::addPoint(int x , int y )
{
    img_painter.fillRect(10*x, 0, 10, this->height(),palette().base());
    img_painter.setBrush(palette().dark().color());
    img_painter.drawEllipse(QPoint(10*x+5,y),5,5);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter wid_painter;
    wid_painter.begin(this);
    wid_painter.drawPixmap(0,0,*boom);
    //qDebug() << "Hi";
}
