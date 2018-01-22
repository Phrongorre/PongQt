#include "enemypaddle.h"
#include <QTimer>

EnemyPaddle::EnemyPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent) {
    m_pong = pong;
    m_indent = indent;
    connect(t, SIGNAL(timeout()), this, SLOT(track()));
    setBrush(QBrush(QColor(255, 255, 255, 255)));

    s->addItem(this);

    reset();
}

void EnemyPaddle::track() {
    //Attempt to follow the pong's vertical location
    if      (m_pong->y()                         < y()                ) slideVelocity = m_pong->y()-y();
    else if (m_pong->y()+m_pong->rect().height() > y()+rect().height())
        slideVelocity = m_pong->y()+m_pong->rect().height() - (y()+rect().height());
    else slideVelocity = 0;

    //Limit slideVelocity to a maximum distance
    if (slideVelocity >  20) slideVelocity =  20;
    if (slideVelocity < -20) slideVelocity = -20;

    //Prevent paddle from moving off of the screen
    if (slideVelocity > scene()->height()-(y()+rect().height()))
        slideVelocity = scene()->height()-(y()+rect().height());
    else if (slideVelocity < -y())
        slideVelocity = -y();

    //Move paddle
    setPos(x(), y()+slideVelocity);

    //Check for pong collision, and deflect if found
    if (m_pong->x()                         < x()+rect().width() &&
        m_pong->x()                         > x()                &&
        m_pong->y()+m_pong->rect().height() > y()                &&
        m_pong->y()                         < y()+rect().height()) {
        m_pong->deflect(slideVelocity);
    }
}

void EnemyPaddle::reset() {
    slideVelocity = 0;
    setRect(0, 0, 20, 200);
    setPos(m_indent - rect().width() /2, scene()->height()/2 - rect().height()/2);
}
