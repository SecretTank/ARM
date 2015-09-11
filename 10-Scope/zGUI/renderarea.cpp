#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    shape = Ellipse;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(1200, 400);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void RenderArea::setCoordinate(QVector<int> Y)
{
    y = Y;
    update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    QRect rect(0, 0, 10, 10);
    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    for (int x = 1; x < y.size(); x++) {
            painter.save();
            painter.translate(5*x, 350 - y[x-1]);
            switch (shape) {

            case Points:
                painter.drawPoints(points, 4);
                break;

            case Ellipse:
                painter.drawEllipse(rect);
                break;
            }
            painter.restore();
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

