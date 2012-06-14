#ifndef APPLE_H
#define APPLE_H

#include <QGraphicsItem>

class Apple : public QGraphicsItem
{
public:
    Apple(qreal x, qreal y);

    QRectF boundingRect() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget );

    QPainterPath shape () const;
};

#endif // APPLE_H
