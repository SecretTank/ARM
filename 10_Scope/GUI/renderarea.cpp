#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(oscope_data *data, QWidget *parent)
    : QWidget(parent)
{
    adc_data = data;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //painter = QPainter(this);
    /*boom = new QPixmap (1200, 400);
    img_painter.begin(boom);
    boom->fill(Qt::transparent);*/
    background = new QPixmap("/home/bijan/Project/ARM/ARM/10_Scope/GUI/Resources/path4522.png");
    fps_timer = new QTimer;
    fps_timer->start(1000);
    connect(fps_timer,SIGNAL(timeout()),this,SLOT(calc_fps()));
    fps = 30;
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(screen_size, 400);
}

void RenderArea::calc_fps()
{
    fps = frameNumber;
    frameNumber = 0;
}

void RenderArea::renderPoint(QPainter *painter)
{
    painter->setBrush(QColor("#50bdd2"));
    painter->setPen(QColor("#50bdd2"));
    int step = screen_size/screen_res + 1;
    int y1,y2;
    for (int x = 1; x < screen_res; x++)
    {
        y2 = adc_data->data[x];
        y1 = adc_data->data[x-1];
        //painter->drawEllipse(QPoint(10*x+5,y),5,5);
        painter->drawLine(step*x-step/2,y1,step*x+step/2,y2);
    }
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter;
    QPixmap image(this->size());
    painter.begin(&image);
    painter.drawPixmap(0,0,*background);
    renderPoint(&painter);
    painter.end();

    QPainter painter_wid;
    painter_wid.begin(this);
    painter_wid.drawPixmap(0,0,image);
    painter_wid.setPen(QColor("#295a83"));
    painter_wid.drawText(10,15,QString::number(fps));
    frameNumber++;
    //qDebug() << "Hi";
}
