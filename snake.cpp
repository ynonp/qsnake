#include "snake.h"
#include <QtGui/QtGui>
#include <QDebug>

qreal kChainSize = 10;

Snake::Snake():
    m_head(0, 0),
    m_growing( 7 ),
    m_speed ( 3 )
{
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
    path.addRect(boundingRect());
    return path;
}

void Snake::paint( QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget )
{
    painter->save();
    painter->setBrush(Qt::yellow);
    painter->drawRect(QRectF(0, 0, kChainSize,kChainSize));

    foreach ( QPointF p, m_tail )
    {
        QPointF itemp = mapFromScene(p);
        painter->drawRect(QRectF(itemp.x(), itemp.y(), kChainSize, kChainSize ));
    }

    painter->restore();
}


void Snake::advance(int step)
{
    if ( ! step ) return;
    if ( m_tickCounter++ % m_speed != 0 ) return;

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

    if ( m_head.x() > -100 )
    {
        moveLeft();
    }

    setPos(m_head);

}

void Snake::moveLeft()  { m_head.rx() -= kChainSize; }
void Snake::moveRight() { m_head.rx() += kChainSize; }
void Snake::moveUp()    { m_head.ry() -= kChainSize; }
void Snake::moveDown()  { m_head.ry() += kChainSize; }
