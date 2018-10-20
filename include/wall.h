#ifndef WALL_H
#define WALL_H

#include "include/entity.h"


/**
 * @brief A colored static object.
 *
 * This is a building block of the game. Made out of high quality bricks.
 *
 * It's functionality is similar to a block, except this entity has a color, so it can be hidden.
 */
class Wall : public Entity
{
public:
    /**
     * @brief           Wall construtor
     * @param x         X position of the wall in the scene
     * @param y         Y position of the wall in the scene
     * @param w         Width
     * @param h         Height
     * @param color     Wall color
     */
    Wall(qreal x, qreal y, qreal w, qreal h,
         const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


private:
    const qreal _brick_w = 20;      //!< Brick width
    const qreal _brick_h = 10;      //!< Brick height
};

#endif // WALL_H
