#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QDebug>
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

    void renderPoint();

protected:
    void paint(QPainter *) Q_DECL_OVERRIDE;

private:
    oscope_data *adc_data;
    int i;
    QPixmap *boom;
    QPainter img_painter;
    QPixmap *background;
};
#endif // RENDERAREA_H
