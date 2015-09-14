#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //painter = QPainter(this);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(1200, 400);
}

void RenderArea::setCoordinate(int X , int ny , int ly )
{
    x = X;
    new_y = ny;
    last_y = ly;
    update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    //QPainterPath path;
    QPainter painter;
    painter.begin(this);
    //QPainter painter(this);
    //painter.setPen(Qt::NoPen);
    //painter.setBrush();
    //painter.save();
    //painter.drawEllipse(rect);
    painter.fillRect(10*x, 0, 10, this->height(),palette().dark());
    painter.setBrush(palette().dark().color());
    //painter.save();
    //painter.translate(5*x,350 - new_y);
    painter.drawEllipse(QPoint(10*x+5,new_y),5,5);
    //painter.restore();
}

