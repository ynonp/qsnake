#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QtCore/QRectF>

class Snake : public QGraphicsItem
{
public:
    Snake();

    QRectF boundingRect() const;
    QPainterPath shape () const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget );

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

protected:
    void advance(int step);

private:
    QPointF        m_head;
    int            m_growing;
    int            m_speed;
    QList<QPointF> m_tail;
    int            m_tickCounter;
};

#endif // SNAKE_H
