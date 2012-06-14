#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QtCore/QTimer>
#include <QtGui/QGraphicsScene>

const qreal kTileSize = 10;

class Snake;
class Apple;
class Wall;

class GameController : public QObject
{
    Q_OBJECT
public:
    enum TGameObjectsData
    {
        GD_Type
    };

    enum TGameObjectTypes
    {
        GO_Apple,
        GO_Wall
    };

public:
    explicit GameController(QGraphicsScene &scene, QObject *parent = 0);

    void snakeAteAnApple(Snake *snake, Apple *apple);
    void snakeHitTheWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);



signals:

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    void handleKeypress( QKeyEvent *keyEvent );
    void addNewApple();

public slots:
    void pause();
    void resume();
    void gameOver();

private:
    QTimer m_timer;
    QGraphicsScene & m_scene;

    Snake *m_snake;
};

#endif // GAMECONTROLLER_H
