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
    pthread_create( &thread_painter, NULL, paintEvent, (void*) this);
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
    //repaint();
}

void *paintEvent(void *ptr)
{
    QPainter wid_painter;
    RenderArea *renderarea = (RenderArea *)ptr;
    wid_painter.begin(renderarea);

    renderarea->img_painter.fillRect(10*renderarea->x, 0, 10, renderarea->height(),renderarea->palette().base());
    renderarea->img_painter.setBrush(renderarea->palette().dark().color());
    renderarea->img_painter.drawEllipse(QPoint(10*renderarea->x+5,renderarea->new_y),5,5);
    wid_painter.drawPixmap(0,0,*(renderarea->boom));
}

