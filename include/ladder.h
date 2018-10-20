#ifndef LADDER_H
#define LADDER_H

#include "include/entity.h"


/**
 * @brief Climbable ladders.
 *
 * Player can climb the ladder by pressing Up/Down.
 *
 * Ladders have their own color and they can be hidden/shown.
 */
class Ladder : public Entity
{
public:
    /**
     * @brief           Ladder constructor
     * @param x         X position of the ladder in the scene
     * @param y         Y position of the ladder in the scene
     * @param w         Width
     * @param h         Height
     * @param color     Ladder color
     */
    Ladder(qreal x, qreal y, qreal w, qreal h,
           const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


private:
    const qreal _step = 5;      //!< Ladder step
};

#endif // LADDER_H
