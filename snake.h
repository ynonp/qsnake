#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QtCore/QRectF>

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum TDirection
    {
        MoveNone,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

public:
    Snake( GameController & controller );

    QRectF boundingRect() const;
    QPainterPath shape () const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget );

    void setMovementDirection( TDirection direction );

protected:
    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

private:
    QPointF          m_head;
    int              m_growing;
    int              m_speed;
    QList<QPointF>   m_tail;
    int              m_tickCounter;
    TDirection       m_movementDirection;
    GameController & m_controller;
};

#endif // SNAKE_H
