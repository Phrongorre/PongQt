#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

#include "playerpaddle.h"

PlayerPaddle::PlayerPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent) {
    m_pong = pong;
    m_indent = indent;
    m_timer = t;
    m_pauseWindow = NULL;
    paused = true;
    moveSpeed = 20;
    s->addItem(this);
    setBrush(QBrush(QColor(255, 255, 255, 255)));

    reset();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(slide()));
}

void PlayerPaddle::keyPressEvent(QKeyEvent *e) {
    if      (e->key() == Qt::Key_Escape) QApplication::quit();
    else if (e->key() == Qt::Key_Space) {
        if (paused) {
            if (m_pauseWindow != NULL) m_pauseWindow->setVisible(false);
            paused = false;
            m_timer->start(50);
        }
        else {
            if (m_pauseWindow != NULL) m_pauseWindow->setVisible(true);
            paused = true;
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
        m_pong->deflect(slideVelocity);
    }
}

void PlayerPaddle::reset() {
    setRect(0, 0, 20, 200);
    setPos(scene()->width() - m_indent - rect().width()/2, scene()->height()/2 - rect().height()/2);
    slideVelocity = 0;
    moveUp = false;
    moveDown = false;
}

void PlayerPaddle::addPauseWindow(QGraphicsRectItem *window) {
    m_pauseWindow = window;
}
