#include "snake.h"
#include <QtGui/QtGui>
#include <QDebug>

#include "gamecontroller.h"

qreal kChainSize = 10;

Snake::Snake( GameController & controller ):
    m_head(0, 0),
    m_growing( 7 ),
    m_speed ( 3 ),
    m_movementDirection ( MoveNone ),
    m_controller ( controller )
{
}

void Snake::setMovementDirection(TDirection direction)
{
    m_movementDirection = direction;
}

QRectF Snake::boundingRect() const
{
    qreal minX = m_head.x();
    qreal minY = m_head.y();
    qreal maxX = m_head.x();
    qreal maxY = m_head.y();

    foreach ( QPointF p, m_tail )
    {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene( QPointF( minX, minY ) );
    QPointF br = mapFromScene( QPointF( maxX, maxY ) );

    QRectF bound = QRectF( tl.x(),  // x
                           tl.y(),  // y
                           br.x() - tl.x() + kChainSize,      // width
                           br.y() - tl.y() + kChainSize       //height
                           );
    return bound;
}

QPainterPath Snake::shape () const
{
    QPainterPath path;
    path.setFillRule( Qt::WindingFill );

    path.addRect( QRectF(0, 0, kChainSize, kChainSize ) );

    foreach ( QPointF p, m_tail )
    {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), kChainSize, kChainSize ));
    }

    return path;
}

void Snake::paint( QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget )
{
    painter->save();
    painter->fillPath( shape(), Qt::yellow );
    painter->restore();
}


void Snake::advance(int step)
{
    if ( ! step ) return;
    if ( m_tickCounter++ % m_speed != 0 ) return;
    if ( m_movementDirection == Snake::MoveNone ) return;


    if ( m_growing > 0 )
    {
        QPointF tail = m_head;
        m_tail << tail;
        m_growing -= 1;
    }
    else
    {
        m_tail.takeFirst();
        m_tail << m_head;
    }


    switch ( m_movementDirection )
    {
        case Snake::MoveLeft: moveLeft(); break;
        case Snake::MoveRight: moveRight(); break;
        case Snake::MoveUp: moveUp(); break;
        case Snake::MoveDown: moveDown(); break;
    }

    setPos(m_head);

    handleCollisions();
}

void Snake::moveLeft()  { m_head.rx() -= kChainSize; if ( m_head.rx() < -100 ) m_head.rx() = 100;  }
void Snake::moveRight() { m_head.rx() += kChainSize; if ( m_head.rx() > 100  ) m_head.rx() = -100; }
void Snake::moveUp()    { m_head.ry() -= kChainSize; if ( m_head.ry() < -100 ) m_head.ry() = 100;  }
void Snake::moveDown()  { m_head.ry() += kChainSize; if ( m_head.ry() > 100  ) m_head.ry() = -100; }


void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    // Check collisions with other objects on screen
    foreach ( QGraphicsItem *collidingItem, collisions )
    {
        if ( collidingItem->data( GameController::GD_Type ) == GameController::GO_Apple )
        {
            // Let GameController handle the event by putting another apple
            m_controller.snakeAteAnApple( this, ( Apple * )collidingItem );
            m_growing += 1;
        }
    }

    // Check snake eating itself
    if ( m_tail.contains( m_head ) )
    {
        m_controller.snakeAteItself( this );
    }

}

