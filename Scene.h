#ifndef SCENE_H
#define SCENE_H

#include "Food.h"
#include "SnakeHead.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

signals:

private:
    SnakeHead *snakeHead;
    SnakeNode *snakeTail;
    Food *food;
    QGraphicsPixmapItem *gameOverPix;
    bool gameOn;

public slots:
    void eatFood();
    void gameOver();

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
