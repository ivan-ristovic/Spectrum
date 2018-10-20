#include "include/wall.h"


Wall::Wall(qreal x, qreal y, qreal w, qreal h, const QColor color) :
    Entity(x, y, w, h, color, true)
{

}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);

    // Drawing bricks
    painter->setBrush(_color);
    for (int i = 0, row = 0; i < _h; i += _brick_h, row++) {
        int j = 0;
        if (row % 2 == 1) {
            painter->drawRect(1, i + 1, _brick_w / 2 - 1, _brick_h - 1);
            j = _brick_w / 2;
        }
        for (; j <= _w - _brick_w; j += _brick_w)
            painter->drawRect(j + 1, i + 1, _brick_w - 1, _brick_h - 1);
        if (j < _w)
            painter->drawRect(j + 1, i + 1, _brick_w / 2 - 1, _brick_h - 1);
    }
}
