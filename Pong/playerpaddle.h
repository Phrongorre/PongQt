/* playerpaddle.h
 *
 * Interface file for PlayerPaddle class
 *
 * J Karstin Neill       1.22.18
 */

#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include "pong.h"

//PlayerPaddle class definition
class PlayerPaddle : public QObject, public QGraphicsRectItem {
    //Uses SIGNALS and SLOTS
    Q_OBJECT
public:
    PlayerPaddle(Pong *pong, QGraphicsScene *s, QTimer *t, int indent);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void addPauseWindow(QGraphicsRectItem *window);
public slots:
    void slide();
private:
    void reset();
    Pong *m_pong;
    int m_indent;
    QTimer *m_timer;
    QGraphicsRectItem *m_pauseWindow;
    bool paused;
    double slideVelocity;
    bool moveUp;
    bool moveDown;
    double moveSpeed;
};

#endif // PLAYERPADDLE_H
