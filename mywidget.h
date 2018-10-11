#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimerEvent>
#include  <QPaintEvent>
#include "snake.h"
#include <QKeyEvent>
#include "snake_food.h"

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    //~MyWidget() ;
protected:
    //void timerEvent(QTimerEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
private:
    Snake *m_snake;
    snake_food* m_food;
};

#endif // MYWIDGET_H
