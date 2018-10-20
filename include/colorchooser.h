#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QTimer>
#include <QScopedPointer>
#include "include/entity.h"


/**
 * @brief Provides an interactive way to choose active color.
 *
 * This entity is a hexagon, with one color on each side.
 * The user can then pick the color by using the mouse.
 * Note that only unlocked colors will be available for choosing.
 */
class ColorChooser : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief                   ColorChooser constructor
     * @param unlockedColors    Vector which contains boolean values indicating if the certain color is unlocked or not
     */
    ColorChooser(const bool *unlockedColors);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief                   Determines the chosen color based on the mouse release position
     * @param mouseReleasePos   Mouse release coordinates
     * @return                  Chosen color ID
     */
    int determineColorID(QPointF &mouseReleasePos) const;


private:
    qreal _r;                       //!< The radius of the hexagon bounding circle
    const bool *_unlockedColors;    //!< Pointer to a bool vector containing unlocked color indicators
};

#endif // COLORCHOOSER_H
