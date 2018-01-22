/* enemypaddle.cpp
 *
 * Implementation file for EnemyPaddle class
 *
 * EnemyPaddle is the opponent for Pong, and implements a very basic
 * tracking method, which attempts to place the paddle in a position
 * to deflect the Pong away from its goal. It is limited to a maximum
 * speed in both directions to keep the game from being impossible.
 *
 * J Karstin Neill       1.22.18
 */

#include "enemypaddle.h"
#include <QTimer>

//Constructor
EnemyPaddle::EnemyPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent) {
    //Store reference to pong
    m_pong = pong;
    //Save indent value
    m_indent = indent;
    //Connect to global timer
    connect(t, SIGNAL(timeout()), this, SLOT(track()));
    //Set color and size
    setBrush(QBrush(QColor(255, 255, 255, 255)));
    setRect(0, 0, 20, 200);
    //Add this to the scene
    s->addItem(this);
    //Set default starting data
    reset();
}

//Slot used to follow pong ball
void EnemyPaddle::track() {
    //Attempt to follow the pong's vertical location
    if      (m_pong->y()                         < y()                ) slideVelocity = m_pong->y()-y();
    else if (m_pong->y()+m_pong->rect().height() > y()+rect().height())
        slideVelocity = m_pong->y()+m_pong->rect().height() - (y()+rect().height());
    else slideVelocity = 0;

    //Limit slideVelocity to a maximum distance of +/-20
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
        //Deflect Pong with current slideVelocity
        m_pong->deflect(slideVelocity);
    }
}

//Resets paddle to starting position
void EnemyPaddle::reset() {
    slideVelocity = 0;
    setPos(m_indent - rect().width() /2, scene()->height()/2 - rect().height()/2);
}
