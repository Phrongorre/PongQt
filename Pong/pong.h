#ifndef PONG_H
#define PONG_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

class Pong : public QObject, public QGraphicsRectItem {
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
