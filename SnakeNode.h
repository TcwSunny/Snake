#ifndef SNAKENODE_H
#define SNAKENODE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class SnakeNode: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal Rotation READ Rotation WRITE setRotation NOTIFY RotationChanged FINAL)
public:
    SnakeNode();
    virtual void moveForward();
    virtual qreal Rotation() const;
    virtual void setRotation(qreal newRotation);

    SnakeNode *getPrev() const;
    void setPrev(SnakeNode *newPrev);

    SnakeNode *getNext() const;
    void setNext(SnakeNode *newNext);

signals:
    void RotationChanged();

private:
    SnakeNode *prev;
    SnakeNode *next;
    qreal m_Rotation;
};

#endif // SNAKENODE_H
