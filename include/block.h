#ifndef BLOCK_H
#define BLOCK_H

#include <QPixmap>
#include "include/entity.h"


/**
 * @brief Static collidable block.
 *
 * This is an entity which does not have the ability to be colored.
 * It is always static, meaning it does not change it's position in game.
 */
class Block : public Entity
{
public:
    /**
     * @brief       Block constructor
     * @param x     X position of the block in the scene
     * @param y     Y position of the block in the scene
     * @param w     Width
     * @param h     Height
     */
    Block(qreal x, qreal y, qreal w, qreal h);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


private:
    QPixmap _texture;   //!< Block texture represented in a QPixmap
};

#endif // BLOCK_H
