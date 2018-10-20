#include "include/key.h"


Key::Key(qreal x, qreal y, Door *door, const QColor color) :
    Entity(x, y, 40, 30, color, true),
    _door(door),
    _sparkTicker(new QTimer())
{
    connect(&(*_sparkTicker), SIGNAL(timeout()), this, SLOT(updateSparklesPos()));
    _sparkTicker->start(150);
}

void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(_color);
    pen.setWidth(4);
    painter->setPen(pen);

    // Drawing key
    painter->drawArc(0, _h/3, _h/2, _h/2, 0, 360 * 16);
    painter->fillRect(_h/2, _h/2, _w - _h/2, 4, _color);
    painter->fillRect(3*_w/4, _h/2, 4, 7, _color);
    painter->fillRect(_w - 3, _h/2, 4, 10, _color);

    // Sparkles
    pen.setWidth(2);
    painter->setPen(pen);
    for (unsigned i = 0; i < _sparkNum; i++)
        painter->drawEllipse(_sx[i], _sy[i], 1, 1);
}

void Key::collect()
{
    unlockDoor();
    _door->update();
    emit collected();
}

void Key::unlockDoor()
{
    _door->unlock();
}

void Key::lockDoor()
{
    _door->lock();
}

void Key::updateSparklesPos()
{
    for (unsigned i = 0; i < _sparkNum; i++)
        _sx[i] = qrand() % (int)_w;
    for (unsigned i = 0; i < _sparkNum; i++)
        _sy[i] = qrand() % (int)_h;
}
