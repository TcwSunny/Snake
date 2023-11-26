#include "Food.h"
#include "SnakeHead.h"

SnakeHead::SnakeHead()
{
    QPixmap pixmap(":/images/Player.png");
    pixmap = pixmap.scaled(QSize(30, 30));
    setPixmap(pixmap);

    setRotation(45);
}

void SnakeHead::moveForward()
{
    qreal angle = Rotation();
    qreal dx = qCos(qDegreesToRadians(angle));
    qreal dy = qSin(qDegreesToRadians(angle));
    qreal Speed = 10;
    setPos(pos().x()+Speed*dx,pos().y()+Speed*dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
        Food * food = dynamic_cast<Food*>(item);
        if (food) {
            emit SnakeEatFood();
            return;
        }
        SnakeNode * snakenode = dynamic_cast<SnakeNode*>(item);
        if (snakenode) {
            emit HeadHitBody();
            return;
        }
    }
    if(getNext()!=nullptr){
        getNext()->moveForward();
    }

}



