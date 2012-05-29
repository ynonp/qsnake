#include <QtGui/QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snake.h"
#include "apple.h"
#include "gamecontroller.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));

    m_game = new GameController( *m_scene, this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene()
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(-100, -100, 200, 200);

    ui->gameView->setScene( m_scene );
}

void MainWindow::adjustViewSize()
{
    ui->gameView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(kTileSize, kTileSize);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, kTileSize, kTileSize);

    QBrush bgBrush( bg );
    ui->gameView->setBackgroundBrush( bgBrush );
}
