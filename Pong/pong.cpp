/* pong.cpp
 *
 * Implementation file for Pong class
 *
 * Pong is the ball which moves around the screen. It uses
 * a move method to check for top and bottom collisions, and
 * flips its yVelocity when deflected. This is tied into the
 * global timer to allow for pausing and automated motion.
 *
 * J Karstin Neill       1.22.18
 */

#include "pong.h"
#include <QGraphicsScene>
#include <QTimer>

Pong::Pong(QGraphicsScene *s, QTimer *t) {
    //Connect the global timer
    connect(t, SIGNAL(timeout()), this, SLOT(move()));

    //Set up Pong object data
    setRect(0, 0, 20, 20);
    setBrush(QBrush(QColor(255, 255, 255, 255)));

    //Add to scene
    s->addItem(this);

    //Apply location and movement reset to initial values
    reset();
}

void Pong::move() {
    //Bounce off of top and bottom
    if (y()+rect().height() > scene()->height() || y() < 0) {
        yVelocity *= -1;
    }
    //Deflect (flip xVelocity) when this flag is set by a paddle
    if (isDeflected) {
        xVelocity *= -1;
        yVelocity += paddleYVel;
        isDeflected = false;
        paddleYVel = 0;
    }

    //Move the pong
    setPos(x()+xVelocity, y()+yVelocity);

    //Reset the pong once it goes out of boundaries
    if (x() < 0 || x()+rect().width() > scene()->width()) {
        reset();
    }
}

//Called by a paddle to allow pong deflection on collision
//Adds on yVel to yVelocity to allow for paddles to alter Pong movement
void Pong::deflect(double yVel) {
    isDeflected = true;
    paddleYVel = yVel;
}

//Resets position and velocity to starting default
void Pong::reset() {
    setPos(scene()->width()/2 - rect().width()/2, scene()->height()/2 - rect().height()/2);
    isDeflected = false;
    paddleYVel = 0;
    xVelocity = 10;
    yVelocity = 5;
}
