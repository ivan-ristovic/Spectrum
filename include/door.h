#ifndef DOOR_H
#define DOOR_H

#include <QScopedPointer>
#include <QTimer>
#include "include/entity.h"


/**
 * @brief Passage to a new level.
 *
 * This entity acts as a portal between two levels.
 *
 * A door can be locked, and then it will require a Key of the same color to unlock them. Player unlocks the
 * door by collecting the Key entity.
 *
 * Player can pass through a door by pressing E.
 */
class Door : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief               Door constructor
     * @param x             X position of the door in the scene
     * @param y             Y position of the door in the scene
     * @param nextLevel     A string representing the name of the level where the door leads
     * @param color         Door color
     * @param locked        Indicates whether the door is locked
     */
    Door(qreal x,
         qreal y,
         const QString& nextLevel,
         const QColor color = SpectrumColors::gray,
         bool locked = false);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief   Lock the door
     */
    void lock();

    /**
     * @brief   Unlock the door
     */
    void unlock();

    /**
     * @brief   Get the next level string
     * @return  String containing the name of the level where the doors lead
     */
    QString nextLevel() const;

    /**
     * @brief   Check if the door is locked
     * @return  Door lock indicator
     */
    bool isLocked() const;

    /**
     * @brief   Check if the doors change the current player spawn in the level
     * @return  Spawn change indicator
     */
    bool changesDefaultSpawn() const;

    /**
     * @brief       Set the spawn change indicator
     * @param b     New spawn change indicator value
     */
    void setChangesDefaultSpawn(bool b);

    /**
     * @brief       Get X position of spawn point
     * @return      X position of spawn point
     */
    int spawnAtX() const;

    /**
     * @brief       Get Y position of spawn point
     * @return      Y position of spawn point
     */
    int spawnAtY() const;

    /**
     * @brief       Set X position of spawn point
     * @param x     New X position value
     */
    void setSpawnAtX(int x);

    /**
     * @brief       Set Y position of spawn point
     * @param y     New Y position value
     */
    void setSpawnAtY(int y);

private slots:
    /**
     * @brief       Unlock the door by removing the door bars
     */
    void shrinkBars();

private:
    qreal _barH;                                //!< Door bar height
    bool _locked;                               //!< Door lock indicator
    bool _drawBars;                             //!< An indicator determining whether to draw door bars or not
    QScopedPointer<QTimer> _barShrinkTicker;    //!< Handles bar shrinking
    QString _nextLevel;                         //!< Name of the level where the doors lead
    bool _changesDefaultSpawn;                  //!< Indicator whether the door change the default player spawn position
    int _spawnAtX = 200;                        //!< X player spawn location
    int _spawnAtY = 200;                        //!< Y player spawn location
};

#endif // DOOR_H
