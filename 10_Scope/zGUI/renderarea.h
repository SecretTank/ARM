#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QVector>
#include <QPainter>
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
protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    //QPainter painter;
    int x;
    int new_y;
    int last_y;
};
#endif // RENDERAREA_H
