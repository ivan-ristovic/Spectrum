#ifndef CUBE_H
#define CUBE_H

#include "include/dynamicentity.h"


/**
 * @brief An entity which is affected by the gravity and player collision.
 *
 * This entity is one of the building blocks of the game.
 * It has a color, so it can be hidden or shown, based on active color.
 * It also can be pushed/pulled to a certain position.
 */
class Cube : public DynamicEntity
{
public:
    /**
     * @brief           Cube constructor
     * @param x         X position of the cube in the scene
     * @param y         Y position of the cube in the scene
     * @param size      Cube size
     * @param color     Cube color
     */
    Cube(qreal x, qreal y, qreal size,
         const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // CUBE_H
