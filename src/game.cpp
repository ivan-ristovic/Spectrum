#include "include/game.h"
#include "include/gameloader.h"
#include "include/ladder.h"
#include "include/door.h"
#include "include/key.h"
#include "include/colorunlocker.h"
#include "include/gravityswitcher.h"


SpectrumGame::SpectrumGame(QGraphicsView *parent) :
    _paused(false),
    _expandInProgress(false),
    _parent(parent),
    _gravCoeff(0.25),
    _activeColor(SpectrumColors::defaultActiveColor),
    _oldActiveColor(SpectrumColors::defaultActiveColor),
    _player(new Player()),
    _spectrum(new ColorChooser(_unlockedColors)),
    _gameTicker(new QTimer()),
    _unlockedColors {true, false, false, false, false, false}
{
    // Adding color chooser to the scene
    addItem(&(*_spectrum));
    _spectrum->hide();

    // Loading new level
    loadLevel("001");

    // Adding player to the scene
    addItem(&(*_player));

    // Connecting timer to game-tick function
    connect(&(*_gameTicker), SIGNAL(timeout()), this, SLOT(update()));
    _gameTicker->start(15);

    connect(&(*_player), SIGNAL(playerHit()), this, SLOT(startGameOverAnimation()));

    // Setting focus to scene
    setFocus();
}

SpectrumGame::~SpectrumGame()
{
    _gameTicker->stop();
}

void SpectrumGame::loadLevel(const QString id)
{
    // Load next level
    _level.reset(new Level(id, *_player, &_activeColor));
    _level->load(this);
    setBackgroundBrush(QBrush(_activeColor));
    _oldActiveColor = _activeColor;

    if (_level->id() >= _completedLevels.size())
        _completedLevels.resize(_level->id() + 1, false);

    // Stop player
    _player->setVx(0);
    _player->setVy(0);

    // Restore gravity coefficient
    _gravCoeff = 0.25;
    _player->setAngle(0);

    // Connecting slots
    connectSlots(_level->staticEntities());
}

void SpectrumGame::pause()
{
    _gameTicker->stop();
    _paused = true;
    clearFocus();
    _parent->hide();
}

void SpectrumGame::resume()
{
    _gameTicker->start();
    _paused = false;
}

void SpectrumGame::load(QString &fileName)
{
    GameLoader loader(fileName, 'r');
    if (loader.isValid()) {
        QString level = loader.readGameData(_unlockedColors, _completedLevels);
        loadLevel(level);
    }
}

void SpectrumGame::save(QString &fileName) const
{
    GameLoader saver(fileName, 'w');
    if (saver.isValid())
        saver.writeGameData(_level->id(), _unlockedColors, _completedLevels);
}

void SpectrumGame::keyPressEvent(QKeyEvent *event)
{
    if (_paused)
        return;

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        _player->setLeft(true);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        _player->setRight(true);
    else if (event->key() == Qt::Key_Space) {
        _player->setJump(true);
        _player->jumpSprite().startAnimation();
    }
    else if (event->key() == Qt::Key_Z)
        _player->setPull(true);
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
        _player->setDown(true);
        _player->setVx(0);
    } else if (event->key() == Qt::Key_Escape)
        pause();
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _player->setUp(true);
    else if (event->key() == Qt::Key_E && !_expandInProgress && _activeColor != SpectrumColors::gray)
        interact();
}

void SpectrumGame::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        _player->setLeft(false);
    else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        _player->setRight(false);
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        _player->setUp(false);
    else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
        _player->setDown(false);
    else if (event->key() == Qt::Key_Z)
        _player->setPull(false);
}

void SpectrumGame::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            ((Entity*)item)->show();
    _activeColor = SpectrumColors::gray;
    animateColorChange(_activeColor);
    _spectrum->show();
    // Slow down the game while choosing the color
    _gameTicker->setInterval(50);
}

void SpectrumGame::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QPointF mouseReleasePos = e->lastScenePos();
    int colorID = _spectrum->determineColorID(mouseReleasePos);
    QColor chosenColor = SpectrumColors::getColorFromID(colorID);

    // If the player is inside of a collidable object, don't allow the change
    QList<QGraphicsItem *> collidingObjects = _player->collidingItems();
    bool shouldChangeActiveColor = true;
    foreach (QGraphicsItem* item, collidingObjects)
        if (((Entity*)item)->collidable() && chosenColor != ((Entity*)item)->color()) {
            if (typeid(Ladder) != typeid(*item)) {
                shouldChangeActiveColor = false;
                break;
            }
        }

    if (shouldChangeActiveColor && isUnlocked(colorID)) {
        _activeColor = chosenColor;
        _oldActiveColor = _activeColor;
    } else {
        _activeColor = _oldActiveColor;
    }
    animateColorChange(_activeColor);
    _spectrum->hide();
    // Reset game speed back to normal when the color is chosen
    _gameTicker->setInterval(15);
}

void SpectrumGame::changeActiveColor(QKeyEvent *event)
{
    QColor newActiveColor = _activeColor;
    if (event->key() == Qt::Key_1 && _unlockedColors[SpectrumColors::BLUE])
        newActiveColor = SpectrumColors::blue;
    else if (event->key() == Qt::Key_2 && _unlockedColors[SpectrumColors::GREEN])
        newActiveColor = SpectrumColors::green;
    else if (event->key() == Qt::Key_3 && _unlockedColors[SpectrumColors::YELLOW])
        newActiveColor = SpectrumColors::yellow;
    else if (event->key() == Qt::Key_4 && _unlockedColors[SpectrumColors::RED])
        newActiveColor = SpectrumColors::red;
    else if (event->key() == Qt::Key_5 && _unlockedColors[SpectrumColors::ORANGE])
        newActiveColor = SpectrumColors::orange;
    else if (event->key() == Qt::Key_6 && _unlockedColors[SpectrumColors::PURPLE])
        newActiveColor = SpectrumColors::purple;

    // If the chosen new active color is the same as the one before, do nothing
    if (newActiveColor == _activeColor)
        return;

    // Show all entities on the scene to be able to check collisions
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            item->show();

    // Disable changing active color when there's a collision with entities with activeColor
    QList<QGraphicsItem *> collidingObjects = _player->collidingItems();
    bool shouldChangeActiveColor = true;
    foreach (QGraphicsItem* item, collidingObjects)
        if (((Entity*)item)->collidable() && _activeColor == ((Entity*)item)->color()) {
            shouldChangeActiveColor = false;
            break;
        }

    if (shouldChangeActiveColor) {
            if (!_expandInProgress) {
                _activeColor = newActiveColor;
                animateColorChange(newActiveColor);
            }
            update();
        }
    else
        foreach (QGraphicsItem* item, items())
            if (((Entity*)item)->color() == _activeColor)
                item->show();
}

void SpectrumGame::interact()
{/*
     if (_colorCircleTicker.data() != nullptr || _colorCircleTicker->isActive())
         return;*/
    foreach (QGraphicsItem *item, _player->collidingItems()) {
        // Try to cast the colliding object to class Door
        // If the result is not nullptr, then go through the door if it's unlocked
        Door *door = qobject_cast<Door *>((Entity *)item);
        if (door != nullptr) {
            if (!door->isLocked()) {
                // door will be destroyed when loadLevel is called, so data has to be saved
                bool shouldChangeSpawn = door->changesDefaultSpawn();
                int x = door->spawnAtX();
                int y = door->spawnAtY();
                loadLevel(door->nextLevel());
                if (shouldChangeSpawn)
                    _player->setPos(x, y);
                _completedLevels[_level->id()] = true;  // TODO
            }
            break;
        }

        GravitySwitcher *lever = qobject_cast<GravitySwitcher *>((Entity *)item);
        if (lever != nullptr) {
            lever->pull();
            _gravCoeff = -_gravCoeff;
            _player->flip();
        }
    }
}

void SpectrumGame::unlockColor(int id)
{
    _unlockedColors[id] = true;
}

bool SpectrumGame::isUnlocked(const QColor &color) const
{
    return _unlockedColors[SpectrumColors::toEnum(color)];
}

bool SpectrumGame::isUnlocked(int colorID) const
{
    return _unlockedColors[colorID];
}

void SpectrumGame::animateColorChange(QColor color)
{
    _expandInProgress = true;
    _colorCircle.reset(new ColorChanger(_parent, _player->centerX(), _player->centerY(), color));
    connect(&(*_colorCircle), SIGNAL(expandingDone()), this, SLOT(stopColorChangeAnimation()));
    addItem(&(*_colorCircle));
    _parent->update();
}

void SpectrumGame::stopColorChangeAnimation()
{
    if (_expandInProgress)
        removeItem(&(*_colorCircle));
    setBackgroundBrush(_activeColor);
    _expandInProgress = false;
    if (_activeColor != SpectrumColors::gray)
        hideObjectsWithActiveColor();
}

void SpectrumGame::keyCollected()
{
    Key *sender = (Key*)QObject::sender();
    removeItem(sender);
    _level->removeStaticEntity((Entity*)sender);
}


void SpectrumGame::startGameOverAnimation()
{
    if (!_player->isAlive())
        return;
    _gameTicker->setInterval(50);
    _paused = true;
    _player->setIsAlive(false);
    // TODO replace:
    QTimer::singleShot(2000, this, SLOT(stopGameOverAnimation()));
    // with:
    // _player->deathSprite().startAnimation();
    // QTimer::singleShot(ANIMATION_TIME, this, SLOT(stopGameOverAnimation()));
}

void SpectrumGame::stopGameOverAnimation()
{
    _player->setIsAlive(true);
    _gameTicker->setInterval(15);
    _paused = false;
    loadLevel(QString("%1").arg(_level->id(), 3, 10, QChar('0')));
}


void SpectrumGame::connectSlots(std::vector<Entity *> entities)
{

    foreach (QGraphicsItem *item, entities) {
        if (typeid(*item) == typeid(ColorUnlocker)) {
            if (isUnlocked(((ColorUnlocker*)item)->color()))
                removeItem(item);
            else
                connect((ColorUnlocker*)item, SIGNAL(colorUnlocked(int)), this, SLOT(unlockColor(int)));
        } else if (typeid(*item) == typeid(Key)) {
            connect((Key*)item, SIGNAL(collected()), this, SLOT(keyCollected()));
        }
    }
}

void SpectrumGame::hideObjectsWithActiveColor()
{
    // Hide objects from the scene that have the same color as activeColor
    foreach (QGraphicsItem* item, items())
        if (((Entity*)item)->color() == _activeColor)
            ((Entity*)item)->hide();
}

void SpectrumGame::update() const
{
    _player->jump();
    _player->movement();

    std::vector<DynamicEntity *> dynamicEntities = _level->dynamicEntities();
    foreach (DynamicEntity *ent, dynamicEntities) {
        ent->setCh(0);
    }

    while (true) {
        int i = 0;
        int min = 0;
        double minch = 2;
        foreach (DynamicEntity *ent, dynamicEntities) {
            if (ent->getCh() < minch) {
                min = i;
                minch = ent->getCh();
            }
            i++;
        }
        if (minch >= 1)
            break;
        DynamicEntity *ent = dynamicEntities.at(min);
        ent->move(min);
    }
    _player->applyGravity(_gravCoeff);
    _level->applyGravity(_gravCoeff);
    _spectrum->setPos(_player->centerX(), _player->centerY());
    _parent->update();
}
