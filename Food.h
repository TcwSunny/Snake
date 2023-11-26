#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Food: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Food();
};

#endif // FOOD_H
