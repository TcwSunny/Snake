#include "SnakeNode.h"
#include "Food.h"
#include <QDebug>

SnakeNode::SnakeNode():prev(nullptr), next(nullptr)
{
    QPixmap pixmap(":/images/Player.png");
    pixmap = pixmap.scaled(QSize(30, 30));
    setPixmap(pixmap);
}

void SnakeNode::moveForward()
{
    if (prev != nullptr) {
        qreal Distance = 50;
        qreal angleInRadians = qDegreesToRadians(Rotation());
        qreal dx = qCos(angleInRadians);
        qreal dy = qSin(angleInRadians);
        qreal currentDistance = qSqrt(qPow(prev->pos().x() - pos().x(), 2) + qPow(prev->pos().y() - pos().y(), 2));
        qreal speed = currentDistance - Distance;
        setPos(pos().x() + speed * dx, pos().y() + speed * dy);
        QPointF vector = prev->mapToScene(0,0) - mapToScene(0,0);
        angleInRadians = qAtan2(vector.y(), vector.x());
        setRotation(qRadiansToDegrees(angleInRadians));
        if (next != nullptr) {
            next->moveForward();
        }
    }
}

qreal SnakeNode::Rotation() const
{
    return m_Rotation;
}

void SnakeNode::setRotation(qreal newRotation)
{
    if (qFuzzyCompare(m_Rotation, newRotation))
        return;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(newRotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
    m_Rotation = newRotation;
    emit RotationChanged();
}

SnakeNode *SnakeNode::getPrev() const
{
    return prev;
}

void SnakeNode::setPrev(SnakeNode *newPrev)
{
    prev = newPrev;
}

SnakeNode *SnakeNode::getNext() const
{
    return next;
}

void SnakeNode::setNext(SnakeNode *newNext)
{
    next = newNext;
}
