#ifndef LASER_H
#define LASER_H

#include <QTimer>
#include <QScopedPointer>
#include "include/entity.h"


/**
 * @brief A deadly laser that brings destruction to anything in it's wake.
 *
 * A "one hit kill" laser with a static base.
 * The length of a laser is "infinite" (big enough to cover whole screen) but it will be blocked by
 * a first object the laser ray collides with.
 *
 * Laser can be static (not move at all), or have a defined base length in which case it will
 * slide on it.
 *
 * Laser has it's own color, so if it is picked as active, the laser will dissapear leaving only the base.
 * The base is always black.
 */
class Laser : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief The Direction enumerator
     */
    enum Direction { UP, DOWN, LEFT, RIGHT };

    /**
     * @brief               Laser constructor
     * @param x             X position of the laser in the scene
     * @param y             Y position of the laser in the scene
     * @param dx            Base horizontal length
     * @param dy            Base vertical length
     * @param direction     Laser ray direction
     * @param color         Laser ray color
     *
     * The base length cannot have both dx and dy set at the same time.
     * The laser can only be horizontal or vertical
     */
    Laser(qreal x, qreal y,
          qreal dx = 0, qreal dy = 0,
          Direction direction = DOWN,
          const QColor color = SpectrumColors::black);

    // Overrides from Entity
    void hide() override;
    void show() override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


private slots:
    /**
     * @brief   Move the laser ray (if the laser isn't static)
     */
    void move();

private:
    /**
     * @brief   Calculate the laser ray length determined by the first object the laser ray collides with
     * @return  Ray length
     */
    qreal calculateLaserLength();

    const qreal MAX_LASER_LEN = 800;        //!< Default maximum length
    const qreal LASER_WIDTH = 5;            //!< Laser ray width
    Direction _direction;                   //!< Laser direction
    bool _hidden;                           //!< Indicates whether the laser is hidden
    qreal _step;                            //!< Laser move step
    qreal _laserPos;                        //!< Laser position relative to the base
    QScopedPointer<QTimer> _moveTicker;     //!< Handles laser moving
};

#endif // LASER_H
