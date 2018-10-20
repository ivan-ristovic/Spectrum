#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"
#include "include/player.h"


/**
 * @brief Stores all the information related to the current level.
 */
class Level {
public:
    /**
     * @brief                   Level constructor
     * @param id                ID of the level to load
     * @param player            Player pointer (in order to change player location in the level)
     * @param activeColor       Current active color (changed if the level is set to change active color)
     */
    Level(const QString &id, Player &player, QColor *activeColor);
    ~Level();

    // Deleted functions/operators
    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    /**
     * @brief   Add items to the scene
     * @param   Scene where the items are added
     */
    void load(QGraphicsScene *scene) const;

    /**
     * @brief   Get all static entities present in the level
     * @return  Static entities vector
     */
    std::vector<Entity *> staticEntities() const;

    /**
     * @brief   Get all dynamic entities present in the level
     * @return  Dynamic entities vector
     */
    std::vector<DynamicEntity *> dynamicEntities() const;

    /**
     * @brief   Get level ID
     * @return  Level ID
     */
    unsigned id() const;

    /**
     * @brief   Applies gravity to all dynamic entities in the level
     * @param   Gravity coefficient
     */
    void applyGravity(qreal g);

    /**
     * @brief   Remove static entity from the level
     * @param   Pointer to entity to be removed
     */
    void removeStaticEntity(Entity *item);

    /**
     * @brief   Remove dynamic entity from the level
     * @param   Pointer to dynamic entity to be removed
     */
    void removeDynamicEntity(DynamicEntity *item);

private:
    std::vector<Entity *> _staticEntities;              //!< Static entities vector
    std::vector<DynamicEntity *> _dynamicEntities;      //!< Dynamic entities vector
    Player &_player;                                    //!< Player reference
    unsigned _id;                                       //!< Level ID
};

#endif // LEVEL_H
