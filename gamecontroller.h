#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QtCore/QTimer>
#include <QtGui/QGraphicsScene>

const qreal kTileSize = 10;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QGraphicsScene &scene, QObject *parent = 0);
    
signals:
    
public slots:
    void pause();
    void resume();

private:
    QTimer m_timer;
    QGraphicsScene & m_scene;
};

#endif // GAMECONTROLLER_H
