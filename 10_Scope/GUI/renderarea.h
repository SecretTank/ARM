#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "define.h"
//! [0]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Points, Ellipse };

    RenderArea(oscope_data *data, QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void renderPoint(QPainter *painter);

private slots:
    void calc_fps();


protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    oscope_data *adc_data;
    int i,frameNumber,fps;
    QPixmap *boom;
    QPainter img_painter;
    QPixmap *background;
    QTimer *fps_timer;
};
#endif // RENDERAREA_H
