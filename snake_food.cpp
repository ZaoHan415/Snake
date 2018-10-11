#include "snake_food.h"
#include <QRandomGenerator>
//#include <QDebug>
#include <QTime>
snake_food::snake_food(QWidget * _parent)
{
    parent = _parent;
}

void snake_food::Plot()
{
    p = new QPainter(parent);
    p->setBrush(Qt::green);
    p->setPen(Qt::red);
    QRectF rect= QRectF(position.x()-2,position.y()-2,4,4);
    p->drawEllipse(rect);
    delete p;
}

void snake_food::be_asked()
{
    emit position_now(&position);
}
void snake_food::regenerate()
{
    QRandomGenerator s(QTime(0,0,0).secsTo(QTime::currentTime()));
    double temp = s.generateDouble()*500;
    position.setX(temp);
    qDebug()<<temp<<" ";
    temp = s.generateDouble()*500;
    position.setY(temp);
    //qDebug()<<temp<<endl;
}
