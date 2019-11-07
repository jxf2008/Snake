#ifndef FOODITEM_H
#define FOODITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "ConstValue.h"

class FoodItem : public QGraphicsItem
{
private:
    int number_int;
public:
    FoodItem(int nu , QGraphicsItem* parent = 0);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void updateNumber(int nu);
};

#endif // FOODITEM_H
