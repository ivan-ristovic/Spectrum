#include "include/sprite.h"


Sprite::Sprite() :
    _current(0),
    _inLoop(false)
{
    connect(&_ticker, SIGNAL(timeout()), this, SLOT(change()));
    _ticker.setInterval(90);
}

void Sprite::startAnimation()
{
    if (!_ticker.isActive())
        _ticker.start();
}

void Sprite::stopAnimation()
{
    _current = 0;
    if (_ticker.isActive())
        _ticker.stop();
}

bool Sprite::animationActive() const
{
    return _ticker.isActive();
}

bool Sprite::inLoop() const
{
    return _inLoop;
}

void Sprite::setLoop(bool b)
{
    _inLoop = b;
}

int Sprite::tickerInterval() const
{
    return _ticker.interval();
}

void Sprite::setTickerInterval(int ms)
{
    _ticker.setInterval(ms);
}

QPixmap Sprite::nextFrame() const
{
    return _sprites[_current];
}

void Sprite::addFrame(const QString& frame)
{
    _sprites.push_back(QPixmap(frame));
}

void Sprite::change()
{
    if (_current == 0 && !animationActive()) {
        _ticker.start();
    }

    _current = (_current + 1) % _sprites.size();

    if (_current == 0 && !_inLoop) {
        _ticker.stop();
    }
}
