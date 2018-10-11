#include "snake.h"
#include <QDebug>
#include <cmath>
void rotate(direction d,QPointF * vec)
{
    double x = vec->x();
    double y = vec->y();
    if(d == m_left)
    {
        vec->setX(y);
        vec->setY(-x);
    }
    else if(d == m_right)
    {
        vec->setX(-y);
        vec->setY(x);
    }
}//rotate a vector by Pi/2 or 3Pi/2
double distance(QPointF f1,QPointF f2)
{
    QPointF delta = f1 - f2;
    return sqrt((delta.x())*(delta.x())+delta.y()*delta.y());
}

//--------------------------------------------------------

Snake::Snake(QWidget *_parent)
{
    parent = _parent;
    head =new snake_body();
    timer = new QTimer(this);
    timer->start(time_step);

    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(timer,SIGNAL(timeout()),parent,SLOT(update()));
}

void Snake::eat()
{
    snake_body * newbody = new snake_body();
    snake_body * nowtail = get_tail();
    nowtail->next = newbody;
}

snake_body* Snake::get_tail()
{
    snake_body* now = head;
    while(now->next != nullptr)
    {
        now = now->next;
    }
    return now;
}

void Snake::turn_direction(direction dir)
{
    rotate(dir,&head_direction);
    if(head->next!=nullptr)
    {
        if(dir == m_left)
            head->next->di = m_left;
        else
            head->next->di = m_right;
    }
    //hea_pos += 2*head_direction*side_length;
}

void Snake::update() //each part of the body moves 1 unit forward
{
    QPointF now_vel = head_direction;
    hea_pos += side_length * now_vel;
    direction pre_di1 = parr,pre_di2 =parr;
    for(snake_body * now = head;now!=nullptr;now = now->next)
    {
        pre_di2 = now->di;
        now->di = pre_di1;
        pre_di1 = pre_di2;
    }
    emit query();
}

void Snake::Plot() // when update() is done,call this function
{                             //to draw the whole snake with current position
    p = new QPainter(parent);
    p->setPen(Qt::red);
    p->setBrush(Qt::yellow);
    QRectF rect;
    QPointF now_body = hea_pos;
    QPointF now_direction = head_direction;
    for(snake_body *now = head; now != nullptr ; now = now->next)
    {
        rect.setRect(now_body.x() - side_length/2,now_body.y() - side_length/2,side_length,side_length);
        p->drawRect(rect);
        if(now->next != nullptr)
        {
            if(now->next->di == m_right)
                rotate(m_left,&now_direction);
            else if(now->next->di == m_left)
                rotate(m_right,&now_direction);
        }
        now_body += -side_length*now_direction;
    }
    delete  p;
}
void Snake::keyPressEvent(QKeyEvent *key)
{
    if(key->key() == Qt::Key_Left)
    {
        turn_direction(m_left);
    }
    else if(key->key() == Qt::Key_Right)
    {
        turn_direction(m_right);
    }
}

void Snake::get_food(QPointF* f)
{
    double d = distance(*f,hea_pos);
    if(d<side_length/1.5)    {
        eat();
        time_step -= 15;
        timer->stop();
        timer->start(time_step);
        emit food_eaten();
    }
}
