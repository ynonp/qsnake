#include "gamecontroller.h"
#include "snake.h"
#include "wall.h"
#include "apple.h"

#include <QtCore/QDebug>

#include <QtGui/QtEvents>


GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    m_scene ( scene )
{
    m_timer.start( 1000/33 );

    m_snake   = new Snake( *this );
    Apple *a1 = new Apple(0, -50);

    m_scene.addItem( m_snake );
    m_scene.addItem( a1 );

    m_scene.installEventFilter( this );
    resume();
}

void GameController::pause()
{
    m_timer.disconnect( &m_timer, SIGNAL(timeout()),
                        &m_scene, SLOT(advance()));
}

void GameController::resume()
{
    QObject::connect(&m_timer, SIGNAL(timeout()),
                     &m_scene, SLOT(advance()) );
}

void GameController::handleKeypress( QKeyEvent *keyEvent )
{
    switch ( keyEvent->key() )
    {
        case Qt::Key_Left:
            m_snake->setMovementDirection(Snake::MoveLeft);
        break;

        case Qt::Key_Right:
            m_snake->setMovementDirection(Snake::MoveRight);
        break;

        case Qt::Key_Up:
            m_snake->setMovementDirection(Snake::MoveUp);
        break;

        case Qt::Key_Down:
            m_snake->setMovementDirection(Snake::MoveDown);
        break;
    }
}

bool GameController::eventFilter(QObject *dest, QEvent *evt)
{
    if ( evt->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = (QKeyEvent *)evt;
        handleKeypress( keyEvent );
        return true;
    }
    else
    {
        return QObject::eventFilter( dest, evt );
    }
}

void GameController::addNewApple()
{
    int x, y;

    // Randomize the apple location in a loop
    // until we find a spot outside the snake's body
    do {
        x = (int) ( qrand() % (( 99 + 1 ) + 99 ) - 99 ) / 10;
        y = (int) ( qrand() % (( 99 + 1 ) + 99 ) - 99 ) / 10;

        x *= 10;
        y *= 10;
        // To check if a point is inside the snake's shape,
        // we can use shape() method.
        // Note the coordinate systems though - shape() works
        // in item coordinates, while the point we randomized was
        // in scene's coordinates. That's why the mapping was needed.
    } while ( m_snake->shape().contains( m_snake->mapFromScene( QPointF( x + 5, y + 5 ) ) ) );

    Apple *a = new Apple(x , y );
    m_scene.addItem( a );
}

void GameController::snakeAteAnApple(Snake *snake, Apple *apple)
{
    // When a snake eats an apple, we take the old apple out of
    // the scene, and insert a new one in its place
    m_scene.removeItem( apple );
    delete apple;

    addNewApple();
}


void GameController::snakeAteItself(Snake *snake)
{
    // When a snake hits itself the game is over. Note gameOver()
    // method clears the scene, but clearing the scene in the middle
    // of an update is a bad idea.
    // A QTimer is used to call gameOver() outside the update event
    // handler's context
    QTimer::singleShot( 0, this, SLOT(gameOver()) );
}

void GameController::gameOver()
{
    m_scene.clear();

    m_snake = new Snake( *this );
    m_scene.addItem( m_snake );
    addNewApple();
}

void GameController::snakeHitTheWall(Snake *snake, Wall *wall)
{
    // TODO
}
