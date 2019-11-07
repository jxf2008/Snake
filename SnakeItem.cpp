#include "SnakeItem.h"

#include <QDebug>

SnakeItem::SnakeItem(QGraphicsItem* parent) : QGraphicsItem(parent)
{

}

void SnakeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    int colors = 1;
    for(auto A :snakePaths_List)
    {
        QRect rc(A.x*MAP_SIZE_SNAKE,A.y*MAP_SIZE_SNAKE,MAP_SIZE_SNAKE,MAP_SIZE_SNAKE);
        painter->setBrush(QBrush(QColor(colors*10,colors*2,colors*15)));
        painter->drawRect(rc);
        ++colors;
    }
}

QRectF SnakeItem::boundingRect()const
{
    int maxX = snakePaths_List.first().x;
    int maxY = snakePaths_List.first().y;
    int minX = maxX;
    int minY = maxY;
    for(auto A : snakePaths_List)
    {
        if(maxX < A.x)
            maxX = A.x;
        if(maxY < A.y)
            maxY = A.y;
        if(minX > A.x)
            minX = A.x;
        if(minY > A.y)
            minY = A.y;
    }
    int X = minX*MAP_SIZE_SNAKE;
    int Y = minY*MAP_SIZE_SNAKE;
    int W = (maxX-minX+1) * MAP_SIZE_SNAKE;
    int H = (maxY-minY+1) * MAP_SIZE_SNAKE;
    return QRectF(X,Y,W,H);
}

QPainterPath SnakeItem::shape()const
{
    QPainterPath p;
    for(auto A : snakePaths_List)
        p.addRect(QRectF(A.x*MAP_SIZE_SNAKE,A.y*MAP_SIZE_SNAKE,MAP_SIZE_SNAKE,MAP_SIZE_SNAKE));
    return p;
}

void SnakeItem::setPath(const QList<GridPoint>& newPath)
{
    snakePaths_List.clear();
    snakePaths_List = newPath;
}
