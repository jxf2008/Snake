#include "FoodItem.h"

FoodItem::FoodItem(int nu , QGraphicsItem* parent) : QGraphicsItem(parent)
{
    number_int = nu;
}

void FoodItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(QBrush(Qt::yellow));
    painter->drawRect(1,1,MAP_SIZE_SNAKE-2,MAP_SIZE_SNAKE-2);

    painter->setPen(QPen(QColor(Qt::red)));
    QFont ft;
    ft.setPointSize(15);
    painter->setFont(ft);
    painter->drawText(QRect(1,1,MAP_SIZE_SNAKE-2,MAP_SIZE_SNAKE-2),Qt::AlignCenter,QString::number(number_int));
}

QRectF FoodItem::boundingRect()const
{
    return QRectF(0,0,MAP_SIZE_SNAKE,MAP_SIZE_SNAKE);
}

QPainterPath FoodItem::shape()const
{
    QPainterPath p;
    p.addRect(1,1,MAP_SIZE_SNAKE-2,MAP_SIZE_SNAKE-2);
    return p;
}

void FoodItem::updateNumber(int nu)
{
    number_int = nu;
}
