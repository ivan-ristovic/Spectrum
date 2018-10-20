#include "include/colorchanger.h"


ColorChanger::ColorChanger(QGraphicsView *view, qreal x, qreal y, QColor color) :
    Entity(x, y, 50, 50, color, false),
    _view(view),
    _expandTicker(new QTimer())
{
    setZValue(-1);
    connect(_expandTicker.data(), SIGNAL(timeout()), this, SLOT(expand()));
    _expandTicker->start(15);
}

QRectF ColorChanger::boundingRect() const
{
    return QRectF(-_w/2, -_h/2, _w, _h);
}

QPainterPath ColorChanger::shape() const
{
    QPainterPath path;
    path.addRect(-_w/2, -_h/2, _w, _h);
    return path;
}

void ColorChanger::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QBrush(_color));
    painter->drawEllipse(-_w/2, -_h/2, _w, _h);
}

void ColorChanger::expand()
{
    if (_w <= MAX_DIAMETER) {
        _w += STEP;
        _h += STEP;
        update(0, 0, _w, _h);
        _view->update();
    } else {
        _expandTicker->stop();
        emit expandingDone();
    }
}

