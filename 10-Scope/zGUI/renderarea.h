#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QVector>
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
    void setShape(Shape shape);
    void setBrush(const QBrush &brush);
    void setCoordinate(QVector<int> Y);
protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    QVector<int> y;
};
#endif // RENDERAREA_H
