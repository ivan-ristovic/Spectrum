#include "include/ladder.h"


Ladder::Ladder(qreal x, qreal y, qreal w, qreal h, const QColor color) :
    Entity(x, y, w, h, color, true)
{
    setZValue(0.95);
}

void Ladder::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);

    // Drawing steps
    painter->setBrush(_color);
    for (int i = 10; i < _h; i += 20)
        painter->drawRect(0, i, _w, 5);

    // Drawing sides
    painter->drawRect(0, 0, 5, _h);
    painter->drawRect(_w - 5, 0, 5, _h);
}
