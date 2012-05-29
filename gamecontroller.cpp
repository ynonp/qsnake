#include "gamecontroller.h"
#include "snake.h"
#include "apple.h"
#include "wall.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    m_scene ( scene )
{
    m_timer.start( 1000/33 );

    Snake *s  = new Snake();
    Apple *a1 = new Apple(0, -50);

    m_scene.addItem( s );
    m_scene.addItem( a1 );

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
