#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeNode.h"

class SnakeHead : public SnakeNode
{
    Q_OBJECT
public:
    SnakeHead();
    void moveForward();

signals:
    void SnakeEatFood();
    void HeadHitBody();

private:

protected:

protected:
};

#endif // SNAKEHEAD_H
