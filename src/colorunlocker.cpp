#include "include/colorunlocker.h"


ColorUnlocker::ColorUnlocker(qreal x, qreal y, const QColor color) :
    Entity(x, y, 60, 20, color, true),
    _opacity(225),
    _step(5),
    _raiseH(0),
    _opacityTicker(new QTimer()),
    _raiseTicker(new QTimer())
{
    connect(&(*_opacityTicker), SIGNAL(timeout()), this, SLOT(incrementOpacity()));
    connect(&(*_raiseTicker), SIGNAL(timeout()), this, SLOT(raise()));
    _opacityTicker->start(25);
}

void ColorUnlocker::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    _color.setAlpha(_opacity);
    painter->setBrush(QBrush(_color));
    QPoint points[] = {
        QPoint(0, 0),
        QPoint(_w, 0),
        QPoint(3*_w/4, _h),
        QPoint(_w/4, _h),
        QPoint(0, 0)
    };
    painter->drawPolygon(points, 5);
}

void ColorUnlocker::collect()
{
    _raiseTicker->start(50);
    _collidable = false;
    emit colorUnlocked(SpectrumColors::toEnum(_color));
}

void ColorUnlocker::incrementOpacity()
{
    _opacity += _step;
    if (_opacity > MAX_OPACITY || _opacity < MIN_OPACITY)
        _step = -_step;
}

void ColorUnlocker::raise()
{
    if (_raiseH < MAX_RAISE_H) {
        _raiseH += 5;
        moveBy(0, -5);
    } else {
        _raiseTicker->stop();
        hide();
        _raiseH = 0;
    }
}
