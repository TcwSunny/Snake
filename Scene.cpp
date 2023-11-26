#include "Food.h"
#include "Scene.h"

#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>

Scene::Scene(QObject *parent)
    :QGraphicsScene{parent},gameOn(1)
{
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/images/BackGround.jpg"));
    addItem(pixItem);
    snakeHead = new SnakeHead();
    connect(snakeHead, &SnakeHead::SnakeEatFood, this, &Scene::eatFood);
    connect(snakeHead, &SnakeHead::HeadHitBody, this, &Scene::gameOver);
    snakeTail = snakeHead;
    snakeHead->setPos(0,0);
    addItem(snakeHead);
    for(int i=0;i<5;i++){
        SnakeNode *temp = new SnakeNode();
        temp->setPrev(snakeTail);
        snakeTail->setNext(temp);
        temp->setPos(snakeTail->x()-50,snakeTail->y()-50);
        addItem(temp);
        snakeTail = temp;
    }


    food = new Food();
    QRandomGenerator *randPos = QRandomGenerator::global();
    food->setPos(randPos->bounded(770),randPos->bounded(570));
    addItem(food);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, snakeHead, [=] {
        snakeHead->moveForward();
    });
    timer->start(100);
}

Scene::~Scene()
{
    if(gameOn){
        delete food;
        SnakeNode *target = snakeHead;
        while(target->getNext()!=nullptr){
            SnakeNode *temp = target;
            target = temp->getNext();
            delete temp;
        }
        delete target;
    }else{
        delete gameOverPix;
    }
}

void Scene::eatFood()
{
    QRandomGenerator *randPos = QRandomGenerator::global();
    food->setPos(randPos->bounded(770),randPos->bounded(570));

    SnakeNode *temp = new SnakeNode();
    temp->setPrev(snakeTail);
    snakeTail->setNext(temp);
    qreal angle = snakeTail->Rotation();
    qreal dx = qCos(qDegreesToRadians(angle));
    qreal dy = qSin(qDegreesToRadians(angle));
    temp->setPos(snakeTail->x()-50*dx,snakeTail->y()-50*dy);
    addItem(temp);
    snakeTail = temp;
}

void Scene::gameOver()
{
    delete food;
    SnakeNode *target = snakeHead;
    while(target->getNext()!=nullptr){
        SnakeNode *temp = target;
        target = temp->getNext();
        delete temp;
    }
    delete target;
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameOver.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(400,300) - QPointF(gameOverPix->boundingRect().width()/2,gameOverPix->boundingRect().height()/2));
    gameOn = 0;
}
void Scene::keyPressEvent(QKeyEvent *event){
    if(gameOn){
        if (event->key() == Qt::Key_Left) {
            snakeHead->setRotation(snakeHead->Rotation()-30);
        } else if (event->key() == Qt::Key_Right) {
            snakeHead->setRotation(snakeHead->Rotation()+30);
        }
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(gameOn){
        if (event->button() == Qt::LeftButton) {
            QPointF vector = event->scenePos()-snakeHead->mapToScene(0,0);
            double angleInRadians = qAtan2(vector.y(), vector.x());
            double angleInDegrees = qRadiansToDegrees(angleInRadians);
            snakeHead->setRotation(angleInDegrees);
        }
    }
}
