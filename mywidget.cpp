#include "mywidget.h"
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    m_snake = new Snake(this);
    //m_timerID = startTimer(time_step);
    m_food = new snake_food(this);
    connect(m_snake,SIGNAL(query()),m_food,SLOT(be_asked()));
    connect(m_food,SIGNAL(position_now(QPointF*)),m_snake,SLOT(get_food(QPointF*)));
    connect(m_snake,SIGNAL(food_eaten()),m_food,SLOT(regenerate()));
}

/*MyWidget::~MyWidget()
{

}*/

void MyWidget::paintEvent(QPaintEvent *)
{
    m_snake->Plot();
    m_food->Plot();
}

/*void MyWidget::timerEvent(QTimerEvent *t)
{

}*/
void MyWidget::keyPressEvent(QKeyEvent *event)
{
    m_snake->keyPressEvent(event);
}
