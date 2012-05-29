#include "apple.h"
#include "gamecontroller.h"

#include <QtGui/QtGui>

const qreal kAppleRadius = 3;

Apple::Apple(qreal x, qreal y)
{
    setPos( x, y );
}

QRectF Apple::boundingRect() const
{
    return QRectF( -kTileSize, -kTileSize,
                   kTileSize * 2, kTileSize * 2 );
}

void Apple::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,  QWidget */*widget*/ )
{
    painter->save();

    painter->setBrush(Qt::red);
    painter->drawEllipse( QPointF(kTileSize / 2, kTileSize / 2),
                          kAppleRadius, kAppleRadius);

    painter->restore();
}
