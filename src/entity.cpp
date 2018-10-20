#include "include/entity.h"


Entity::Entity(qreal x, qreal y, qreal w, qreal h,
               const QColor color, bool collidable) :
    _w(w),
    _h(h),
    _color(color),
    _collidable(collidable)
{
    setPos(x, y);
}

QRectF Entity::boundingRect() const
{
    return QRectF(0, 0, _w, _h);
}

QPainterPath Entity::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _w, _h);
    return path;
}

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(0, 0, _w, _h);
}

void Entity::hide()
{
    QGraphicsObject::hide();
}

void Entity::show()
{
    QGraphicsObject::show();
}

qreal Entity::h() const
{
    return _h;
}

qreal Entity::w() const
{
    return _w;
}

QColor Entity::color() const
{
    return _color;
}

void Entity::setColor(const QColor newColor)
{
    _color = newColor;
}

qreal Entity::centerX() const
{
    return x();
}

qreal Entity::centerY() const
{
    return y();
}

bool Entity::collidable() const
{
    return _collidable;
}
