#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QtCore/QTimer>

class GameController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();

private:
    void initScene();
    void initSceneBackground();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    GameController *m_game;
};

#endif // MAINWINDOW_H
