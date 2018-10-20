#ifndef SPIKE_H
#define SPIKE_H

#include "include/entity.h"


/**
 * @brief A deadly object.
 */
class Spike : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief       Spike constructor
     * @param x     X position of the spike in the scene
     * @param y     Y position of the spike in the scene
     * @param w     Width
     * @param h     Height
     */
    Spike(qreal x, qreal y, qreal w, qreal h);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // SPIKE_H
