#include "include/player.h"
#include "include/key.h"
#include "include/ladder.h"
#include "include/colorunlocker.h"
#include "include/spike.h"
#include "include/laser.h"
#include <cmath>

Player::Player(qreal x, qreal y) :
    DynamicEntity::DynamicEntity(x, y, 60, 80, 1),
    _canJump(2),
    _body(":/sprites/base.png"),
    _armsAndLegs(":/sprites/jump/jump00.png"),
    _arms(":/sprites/arms_00.png"),
    _angle(0),
    _flipTicker(new QTimer()),
    _deadEye(":/sprites/dead.png"),
    _isAlive(true)
{
    setZValue(0.9);

    initializeBlinkSprite();
    initializeJumpSprite();
    initializeWalkSprite();

    setTransformOriginPoint(centerX(), centerY());
    connect(&(*_flipTicker), SIGNAL(timeout()), this, SLOT(incrementAngle()));
}

void Player::initializeBlinkSprite()
{
    _blinkSprite.addFrame(":/sprites/blink/blink1.png");
    _blinkSprite.addFrame(":/sprites/blink/blink2.png");
    _blinkSprite.addFrame(":/sprites/blink/blink3.png");
    _blinkSprite.addFrame(":/sprites/blink/blink4.png");
    _blinkSprite.addFrame(":/sprites/blink/blink3.png");
    _blinkSprite.addFrame(":/sprites/blink/blink2.png");
    _blinkSprite.addFrame(":/sprites/blink/blink1.png");
    connect(&_blinkTicker, SIGNAL(timeout()), this, SLOT(blinkAnimation()));
    _blinkTicker.setInterval(3000);
    _blinkTicker.start();
}

void Player::initializeJumpSprite()
{
    _jumpSprite.addFrame(":/sprites/jump/jump01.png");
    _jumpSprite.addFrame(":/sprites/jump/jump02.png");
    _jumpSprite.addFrame(":/sprites/jump/jump03.png");
    _jumpSprite.addFrame(":/sprites/jump/jump04.png");
    _jumpSprite.addFrame(":/sprites/jump/jump05.png");
    _jumpSprite.addFrame(":/sprites/jump/jump06.png");
    //_jumpSprite.addFrame(":/sprites/jump/jump07.png");
    _jumpSprite.addFrame(":/sprites/jump/jump08.png");
    //_jumpSprite.addFrame(":/sprites/jump/jump09.png");
    _jumpSprite.addFrame(":/sprites/jump/jump10.png");
    //_jumpSprite.addFrame(":/sprites/jump/jump11.png");
    _jumpSprite.addFrame(":/sprites/jump/jump12.png");
    _jumpSprite.setTickerInterval(80);
}

void Player::initializeWalkSprite()
{
    _walkSprite.addFrame(":/sprites/walk/walk_00.png");
    _walkSprite.addFrame(":/sprites/walk/walk_01.png");
    _walkSprite.addFrame(":/sprites/walk/walk_02.png");
    _walkSprite.addFrame(":/sprites/walk/walk_03.png");
    _walkSprite.addFrame(":/sprites/walk/walk_04.png");
    _walkSprite.addFrame(":/sprites/walk/walk_05.png");
    _walkSprite.setTickerInterval(80);
    _walkSprite.setLoop(true);
}

void Player::blinkAnimation()
{
    _blinkSprite.startAnimation();
}

void Player::incrementAngle()
{
    _angle += 5;
    if (_angle % 180 == 0)
        _flipTicker->stop();
}

void Player::setJump(bool b)
{
    _jump = (b && !_inAir);
}

void Player::setLeft(bool b)
{
    _left = b;
}

void Player::setRight(bool b)
{
    _right = b;
}

void Player::setUp(bool b)
{
    _up = b;
}

void Player::setDown(bool b)
{
    _down = b;
}
void Player::setPull(bool b)
{
    pull = b;
}

int Player::angle()
{
    return _angle;
}

void Player::setAngle(int a)
{
    _angle = a;
}

bool Player::getPull()
{
    return pull;
}

Sprite &Player::jumpSprite()
{
    return _jumpSprite;
}

Sprite &Player::walkSprite()
{
    return _walkSprite;
}

bool Player::isAlive() const
{
    return _isAlive;
}

void Player::setIsAlive(bool b)
{
    _isAlive = b;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setRotation(_angle);

    painter->drawPixmap(0, 0, _w, _h, _body);

    if (!_isAlive)
        painter->drawPixmap(0, 0, _w, _h, _deadEye);
    else if (_blinkSprite.animationActive())
        painter->drawPixmap(0, 0, _w, _h, _blinkSprite.nextFrame());
    if (_inAir)
        painter->drawPixmap(0, 0, _w, _h, _jumpSprite.nextFrame());
    else if (_left || _right || std::abs(_vx) > 1) {
        _walkSprite.startAnimation();
        painter->drawPixmap(0, 0, _w, _h, _walkSprite.nextFrame());
        painter->drawPixmap(0, 0, _w, _h, _arms);
    } else {
        _walkSprite.stopAnimation();
        painter->drawPixmap(0, 0, _w, _h, _armsAndLegs);
    }

}

qreal Player::centerX() const
{
    return x() + _w/2;
}

qreal Player::centerY() const
{
    return y() + _h/2;
}

bool Player::go()
{
    movement();
    bool ladder = false;
    int ignoredCollisions = 0;
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
            continue;
        }
        if (typeid(*item) == typeid(Ladder)) {
            ladder = true;
        }
    }

    if (!ladder)
        onLadder = false;
    if (collidingObjects.size() == ignoredCollisions)
        return true;

    if (ladder) {
        for(int z=0;z<3;z++){
        if (!onLadder) {
            moveBy(0, -1);
            onLadder = true;
        }

        int oldColl = collidingItems().size() - ignoredCollisions;
        if (_up && !_left && !_right)
            moveBy(0, -1);
        if (_down && !_left && !_right)
            moveBy(0, 1);
        if (_left)
            moveBy(-1, 0);
        if (_right)
            moveBy(1, 0);

        QList<QGraphicsItem *> collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects) {
            if ( !((Entity*)item)->collidable()) {
                ignoredCollisions++;
                continue;
            }
            if (typeid(*item) == typeid(Ladder)) {
                ignoredCollisions++;
            }
        }

        if (oldColl <= collidingObjects.size() - ignoredCollisions) {
            if (_up && !_left && !_right)
                moveBy(0, 1);
            if (_down && !_left && !_right)
                moveBy(0, -1);
            if (_left)
                moveBy(1, 0);
            if (_right)
                moveBy(-1, 0);
        }
        }
    }

    return false;
}

void Player::jump()
{
    if (_jump && !_inAir) {
        _vy = -10;
        _jump = false;
    }
}

void Player::flip()
{
    _flipTicker->start(10);
}

void Player::movement()
{
    if (_left)
        applyForce(-1200, 0);
    if (_right)
        applyForce(1200, 0);
    QList<QGraphicsItem *> collidingObjects = collidingItems();
    int ignoredCollisions = 0;
    foreach (QGraphicsItem *item, collidingObjects) {
        if ( !((Entity*)item)->collidable()) {
            ignoredCollisions++;
            continue;
        }

        if (typeid(*item) == typeid(Key)) {
            ((Key*)item)->collect();
            ignoredCollisions++;
            continue;
        }

        if (typeid(*item) == typeid(ColorUnlocker)) {
            ((ColorUnlocker*)item)->collect();
            ignoredCollisions++;
            continue;
        }

        if (typeid(*item) == typeid(Ladder)) {
            ignoredCollisions++;
        }

        if (typeid(*item) == typeid(Spike) || typeid(*item) == typeid(Laser)) {
            emit playerHit();
            return;
        }
    }
}
