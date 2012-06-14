#include "apple.h"
#include "gamecontroller.h"

#include <QtGui/QtGui>

const qreal kAppleRadius = 3;

Apple::Apple(qreal x, qreal y)
{
    setPos( x, y );

    setData( GameController::GD_Type, GameController::GO_Apple );
}

QRectF Apple::boundingRect() const
{
    return QRectF( -kTileSize, -kTileSize,
                   kTileSize * 2, kTileSize * 2 );
}


QPainterPath Apple::shape () const
{
    QPainterPath p;
    p.addEllipse( QPointF(kTileSize / 2, kTileSize / 2), kAppleRadius, kAppleRadius );
    return p;
}

void Apple::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,  QWidget */*widget*/ )
{
    painter->save();

    painter->fillPath( shape(), Qt::red );

    painter->restore();
}
