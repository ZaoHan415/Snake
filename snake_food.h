#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H
#include "snake.h"

class snake_food : public QWidget
{
    Q_OBJECT
public:
    snake_food(QWidget* );
    //void is_eaten();
    //void timerEvent(QTimerEvent* ) override;
    void Plot();
private:
    QPointF position = QPointF(100,100);
    QTimer * timer;
    QWidget *parent;
    QPainter *p;
public slots:
    void be_asked();
    void regenerate();
signals:
    void position_now(QPointF* );
//I try to implement the whole game by:
//1st:snake emit a signal, query about where the food is
//2nd:food receive that signal and send one back with its location
//3rd:if it's ate,snake send a signal to call the regenerate slot of food

//I know this might sounds silly.Just trying to separate the two Object
//Wondering if there are any better ways.

};

#endif // SNAKE_FOOD_H
