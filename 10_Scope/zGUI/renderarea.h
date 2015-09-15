#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QDebug>
#include <pthread.h>
//! [0]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Points, Ellipse };

    RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void setCoordinate(int X, int ny, int ly);

public:
    //QPainter painter;
    int x;
    int i;
    int new_y;
    int last_y;
    QPixmap *boom;
    QPainter img_painter;
    pthread_t *thread_painter;
};
#endif // RENDERAREA_H

void osil_paint(void *ptr);
