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

void RenderArea::setCoordinate(int X , int ny )
{
    x = X;
    new_y = ny;
    //repaint();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter wid_painter;
    wid_painter.begin(this);

    img_painter.fillRect(10*x, 0, 10, this->height(),palette().base());
    img_painter.setBrush(palette().dark().color());
    img_painter.drawEllipse(QPoint(10*x+5,new_y),5,5);
    wid_painter.drawPixmap(0,0,*boom);
}
