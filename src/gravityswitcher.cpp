#include "include/gravityswitcher.h"


GravitySwitcher::GravitySwitcher(qreal x, qreal y, const QColor color) :
    Entity(x, y, 10, 50, color, false),
    _angle(20),
    _step(-1),
    _angleTicker(new QTimer())
{
    setZValue(0.95);
    setTransformOriginPoint(_w/2, _h);
    connect(&(*_angleTicker), SIGNAL(timeout()), this, SLOT(changeAngle()));
}

void GravitySwitcher::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(_angle);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(_color));
    painter->drawEllipse(0, _h - 5, _w, 10);
    painter->drawRect(2, 0, 4, _h);
    painter->drawRect(6, 10, 4, 2);
    painter->drawRect(8, 0, 2, 10);
}

void GravitySwitcher::pull()
{
    _angleTicker->start(15);
}

void GravitySwitcher::setAngle(qreal newAngle)
{
    _angle = newAngle;
}

void GravitySwitcher::changeAngle()
{
    _angle += _step;
    if (_angle == 20 || _angle == -20 || _angle == 160 || _angle == 200) {
        _step = -_step;
        _angleTicker->stop();
    }
}
