/* playerpaddle.cpp
 *
 * Implementation file for PlayerPaddle class
 *
 * PlayerPaddle is the user's paddle which is used to deflect
 * the Pong away from the player's side. Movement is based on
 * press and release key events, and is tied in to the main
 * timer to allow for pausing (like both EnemyPaddle and Pong).
 *
 * J Karstin Neill       1.22.18
 */

#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

#include "playerpaddle.h"

//Constructor
PlayerPaddle::PlayerPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent) {
    m_pong = pong;
    m_indent = indent;
    m_timer = t;
    m_pauseWindow = NULL;
    paused = true;
    moveSpeed = 20;
    s->addItem(this);
    setBrush(QBrush(QColor(255, 255, 255, 255)));
    setRect(0, 0, 20, 200);

    reset();

    //Connect to global timer
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slide()));
}

//Player pressed down a key, update movement info or pause/quit info
void PlayerPaddle::keyPressEvent(QKeyEvent *e) {
    if      (e->key() == Qt::Key_Escape) QApplication::quit();
    //Pause/Resume
    else if (e->key() == Qt::Key_Space) {
        if (paused) {
            //Hide pause window
            if (m_pauseWindow != NULL) m_pauseWindow->setVisible(false);
            //Turn paused off
            paused = false;
            //Restart global timer
            m_timer->start(50);
        }
        else {
            //Show pause window
            if (m_pauseWindow != NULL) m_pauseWindow->setVisible(true);
            //Turn paused on
            paused = true;
            //Stop global timer
            m_timer->stop();
        }
    }
    else if (e->key() == Qt::Key_Up    ) {
        moveDown = false;
        moveUp   = true;
    }
    else if (e->key() == Qt::Key_Down  ) {
        moveDown = true;
        moveUp   = false;
    }

}

//Player released a key, update movement info
void PlayerPaddle::keyReleaseEvent(QKeyEvent *e) {
    if      (e->key() == Qt::Key_Up   && moveUp  ) moveUp   = false;
    else if (e->key() == Qt::Key_Down && moveDown) moveDown = false;
}

void PlayerPaddle::slide() {
    //Adjust vertical movement based on input
    if      (moveUp  ) slideVelocity = -moveSpeed;
    else if (moveDown) slideVelocity =  moveSpeed;
    else slideVelocity = 0;

    //Make sure paddle doesn't move out of screen boundaries
    if (slideVelocity > scene()->height()-(y()+rect().height()))
        slideVelocity = scene()->height()-(y()+rect().height());
    else if (slideVelocity < -y())
        slideVelocity = -y();

    //Move the paddle
    setPos(x(), y()+slideVelocity);

    //Check for pong collision, deflect if found
    if (m_pong->x()+m_pong->rect().width()  > x() &&
        m_pong->x()+m_pong->rect().width()  < x()+rect().width() &&
        m_pong->y()+m_pong->rect().height() > y() &&
        m_pong->y()                         < y()+rect().height()) {
        //Deflect Pong with current slideVelocity
        m_pong->deflect(slideVelocity);
    }
}

//Reset paddle back to starting position
void PlayerPaddle::reset() {
    setPos(scene()->width() - m_indent - rect().width()/2, scene()->height()/2 - rect().height()/2);
    slideVelocity = 0;
    moveUp = false;
    moveDown = false;
}

//Store reference to pause window to allow show/hide capability on pause/resume
void PlayerPaddle::addPauseWindow(QGraphicsRectItem *window) {
    m_pauseWindow = window;
}
