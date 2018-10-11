#ifndef SNAKE_H
#define SNAKE_H
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
enum direction
{
    parr = 0,
    m_left,
    m_right
};

struct snake_body
{
    snake_body *next = nullptr;
    direction di = parr;
};//only save the relative direction between two neighbor parts of the Snake
  //thus,a Unidirectional linked list will do the work

class Snake :public QWidget
{
    Q_OBJECT
public:
    Snake(QWidget *parent);
    void Plot();
    snake_body * get_tail();
    bool is_OnMe(QPointF *);//determine if a given point is on the snake body
    void keyPressEvent(QKeyEvent *) override;
private:
    int time_step = 200;
    QWidget * parent;
    double v = 0.05;
    QPointF hea_pos = QPointF(200,200);
    snake_body *head;
    QPointF head_direction = QPointF(0,-1); // unit vector
    int wall_x;
    int wall_y;
    double side_length = 10.0;
    QPainter *p;
    QTimer *timer;
    void eat();
//protected:
public slots:
    void turn_direction(direction );
    //void dead_wall();
    //void dead_self();
    void update();
    void get_food(QPointF *);
signals:
    void query();
    void food_eaten();
};

#endif // SNAKE_H
