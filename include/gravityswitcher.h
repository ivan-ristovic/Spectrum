#ifndef GRAVITYSWITCHER_H
#define GRAVITYSWITCHER_H

#include <QScopedPointer>
#include <QTimer>
#include "include/entity.h"
#include "include/colors.h"


/**
 * @brief Lever that "flips" the gravity.
 */
class GravitySwitcher : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief           GravitySwitcher constructor
     * @param x         X position of lever in the scene
     * @param y         Y position of lever in the scene
     * @param color     Lever color
     */
    GravitySwitcher(qreal x, qreal y,
                    const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief Lever pull handler
     */
    void pull();

    /**
     * @brief           Sets the angle of the lever relative to the surface
     * @param newAngle  New lever angle
     */
    void setAngle(qreal newAngle);


private slots:
    /**
     * @brief Handles lever angle changing animation, increments or decrements the angle based on the _step
     */
    void changeAngle();


private:
    qreal _angle;                           //!< Lever angle
    qreal _step;                            //!< Angle changing step
    QScopedPointer<QTimer> _angleTicker;    //!< Handles lever angle changing animation
};

#endif // GRAVITYSWITCHER_H
