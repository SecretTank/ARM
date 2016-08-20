#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QDebug>
//! [0]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Points, Ellipse };

    RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void addPoint(int x, int y);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    //QPainter painter;
    int i;
    QPixmap *boom;
    QPainter img_painter;
};
#endif // RENDERAREA_H
