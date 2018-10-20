#include "include/door.h"


Door::Door(qreal x, qreal y, const QString &nextLevel, const QColor color, bool locked) :
    Entity(x, y, 60, 100, color, false),
    _barH(_h - _w/12),
    _locked(locked),
    _drawBars(locked),
    _barShrinkTicker(new QTimer()),
    _nextLevel(nextLevel),
    _changesDefaultSpawn(false)
{
    setZValue(-0.5);
    connect(&(*_barShrinkTicker), SIGNAL(timeout()), this, SLOT(shrinkBars()));
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);

    // Drawing door
    painter->setBrush(_color);
    painter->drawRect(0, _w/2, _w, _h - _w/2);
    painter->drawChord(0, 0, _w, _w, 0, 180 * 16);

    painter->setBrush(SpectrumColors::gray);

    // Drawing bars
    if (_drawBars) {
        // Left
        painter->drawRoundedRect(_w/4 - 2, _w/12, 4, _barH, 3, 3);
        // Right
        painter->drawRoundedRect(_w/2 - 2, 0, 4, _barH + _w/12, 3, 3);
        // Middle
        painter->drawRoundedRect(3*_w/4 - 2, _w/12, 4, _barH, 3, 3);
    }

    // Drawing door lock
    if (_locked) {
        QPen p(SpectrumColors::gray);
        p.setWidth(2);
        painter->setPen(p);
        painter->drawArc(_w - 10, _h/2, 10, 10, 0, 180 * 16);
        painter->drawRoundedRect(_w - 10, _h/2 + 5, 10, 10, 3, 3);
    }
}

void Door::lock()
{
    _locked = true;
    _drawBars = true;
    _barH = _h - _w/12;
}

void Door::unlock()
{
    _locked = false;
    _barShrinkTicker->start(40);
}

QString Door::nextLevel() const
{
    return _nextLevel;
}

bool Door::isLocked() const
{
    return _locked;
}

bool Door::changesDefaultSpawn() const
{
    return _changesDefaultSpawn;
}

void Door::setChangesDefaultSpawn(bool b)
{
    _changesDefaultSpawn = b;
}

int Door::spawnAtX() const
{
    return _spawnAtX;
}

int Door::spawnAtY() const
{
    return _spawnAtY;
}

void Door::setSpawnAtX(int x)
{
    _spawnAtX = x;
}

void Door::setSpawnAtY(int y)
{
    _spawnAtY = y;
}

void Door::shrinkBars()
{
    if (_barH > 0)
        _barH -= 5;
    else {
        _drawBars = false;
        _barShrinkTicker->stop();
        _barH = 0;
    }
}

