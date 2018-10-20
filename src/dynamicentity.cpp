#include "include/dynamicentity.h"
#include "include/player.h"
#include "include/cube.h"


DynamicEntity::DynamicEntity(qreal x, qreal y, qreal w, qreal h,
                             qreal mass,
                             const QColor color, bool collidable) :
    Entity::Entity(x, y, w, h, color, collidable),
    _inAir(true),
    _mass(mass),
    _vx(0),
    _vy(0),
    _ch(0)
{

}

void DynamicEntity::setVx(qreal vx)
{
    _vx = vx;
}

void DynamicEntity::setVy(qreal vy)
{
    _vy = vy;
}

void DynamicEntity::setCh(double c)
{
    _ch = c;
}

double DynamicEntity::getCh() const
{
    return _ch;
}
double DynamicEntity::getMass() const
{
    return _mass;
}

void DynamicEntity::applyForce(qreal ix, qreal iy)
{
    _vx += (ix / _mass);
    if (_vx > 4)
        _vx = 4;
    if (_vx < -4)
        _vx =- 4;
    _vy += (iy / _mass);
}

void DynamicEntity::applyGravity(qreal g)
{
    applyForce(0, g);    
}

void DynamicEntity::move(int id)
{
    if (_vy < 0.2 && _vy > 0)
        _vy = -_vy;

    int c1 = _vx > 0 ? 1 : -1;
    int c2 = _vy > 0 ? 1 : -1;
    double ch1 = 2;
    if (_vx * c1 >= 1)
        ch1 = 1 / (_vx * c1);
    double ch2 = 2;
    if (_vy * c2 >= 1)
        ch2 = 1 / (_vy * c2);

    if (_ch == 0) {
        _ch = ch1 < ch2 ? ch1 : ch2;
        return;
    }

    if (_ch >= 1)
        return;

    double trych1 = 0;
    double trych2 = 0;
    while (trych1 < _ch)
        trych1 += ch1;
    while (trych2 < _ch)
        trych2 += ch2;

    if (trych1 == _ch) {
        moveBy(c1, 0);
        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();

        foreach (QGraphicsItem *item, collidingObjects) {
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;
            if (typeid(*item) == typeid(Cube))
                ((DynamicEntity*)item)->applyForce(_vx*_mass/3, 0);
        }

        if (!id && collidingObjects.size() == ignoredCollisions && ((Player*)this)->getPull()) {
            moveBy(-2*c1, 0);
            auto collidingObjects = collidingItems();
            foreach (QGraphicsItem *item, collidingObjects) {
                if (!((Entity*)item)->collidable())
                    ignoredCollisions++;
                if (typeid(*item) == typeid(Cube)) {
                    double force = 2*c1 / (((DynamicEntity*)item)->getMass() + _mass);
                    ((DynamicEntity*)item)->applyForce(force * ((DynamicEntity*)item)->getMass()*10, 0);
                    applyForce(-force * _mass, 0);
                    ((DynamicEntity*)item)->setCh(this->getCh());
                }
            }
            moveBy(2*c1, 0);
        }
        if (collidingObjects.size() > ignoredCollisions) {
            if (id || !((Player*)this)->go()) {
                moveBy(-c1, 0);
                _vx = 0;
            }
        }
        trych1 += ch1;
    }

    if (trych2 == _ch) {
        _inAir = true;
        moveBy(0, c2);
        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects)
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;

        if (collidingObjects.size() > ignoredCollisions) {
            if (id || !((Player*)this)->go()) {
                if (c2 == c2*c2)
                    _inAir = false;
                moveBy(0, -c2);
                if (c2 * _vy > 0)
                    _vy = 0;
                else
                    _ch = 0;
            }
        }

        qreal frictionCoef = 0.1;
        if (collidingItems().size() - ignoredCollisions == 0 && trych2 == ch2)
            applyForce(-_vx * frictionCoef, 0);

        trych2 += ch2;
    }

    _ch = trych1 < trych2 ? trych1 : trych2;
}
