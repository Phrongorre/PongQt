/* main.cpp
 *
 * Main program file. Sets up and execute the game.
 *
 * J Karstin Neill       1.22.18
 */

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>

#include "pong.h"
#include "enemypaddle.h"
#include "playerpaddle.h"

//main function
int main(int argc, char **argv) {
    //Create application
    QApplication a (argc, argv);

    //Create basic elements of game
    QTimer *timer = new QTimer();
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0, 255)));
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Set up the Pong, EnemyPaddle, and PlayerPaddle
    int paddleIndent = 100;
    Pong *p = new Pong(scene, timer);
    EnemyPaddle *ep = new EnemyPaddle(p, scene, timer, paddleIndent);
    PlayerPaddle *pp = new PlayerPaddle(p, scene, timer, paddleIndent);

    //Set up the pause window
    QGraphicsRectItem *pauseRect = new QGraphicsRectItem();
    scene->addItem(pauseRect);
    pauseRect->setRect(0, 0, 650, 200);
    pauseRect->setPos(75, 200);
    pauseRect->setBrush(QBrush(QColor(255, 255, 255, 255)));
    QGraphicsTextItem *text = new QGraphicsTextItem(pauseRect);
    text->setFont(QFont("Courier", 16));
    text->setPlainText("\nPress [SPACE] to Pause/Resume Pong\n\n"
                       "Use [UP] and [DOWN] arrow keys to move your paddle\n"
                       "(positioned on the right side of the screen)\n\n"
                       "Press [ESC] to quit Pong.");
    //Add pause window to PlayerPaddle
    pp->addPauseWindow(pauseRect);

    //Put PlayerPaddle in focus for input control
    pp->setFlag(QGraphicsItem::ItemIsFocusable);
    pp->setFocus();

    //Set view's scene and show view
    view->setScene(scene);
    view->show();

    //Run program
    return a.exec();
}
