#ifndef ENEMYPADDLE_H
#define ENEMYPADDLE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include "pong.h"

class EnemyPaddle : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    EnemyPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent);
public slots:
    void track();
private:
    void reset();
    Pong *m_pong;
    int m_indent;
    double slideVelocity;
};

#endif // ENEMYPADDLE_H
