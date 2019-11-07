#ifndef SNAKEITEM_H
#define SNAKEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "ConstValue.h"

class SnakeItem : public QGraphicsItem
{
private:
    QList<GridPoint> snakePaths_List;
public:
    SnakeItem(QGraphicsItem* parent = 0);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void setPath(const QList<GridPoint>& newPath);
};

#endif // SNAKEITEM_H
