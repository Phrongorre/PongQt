/* pong.h
 *
 * Interface file for Pong class
 *
 * J Karstin Neill       1.22.18
 */

#ifndef PONG_H
#define PONG_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

//Pong class definition
class Pong : public QObject, public QGraphicsRectItem {
    //Uses SIGNALS and SLOTS
    Q_OBJECT
public:
    Pong(QGraphicsScene *s, QTimer *t);
    void setVelocity(double, double);
    void deflect(double);
public slots:
    void move();
private:
    void reset();
    bool isDeflected;
    double paddleYVel;
    double xVelocity;
    double yVelocity;
};

#endif // PONG_H
