#ifndef COLORUNLOCKER_H
#define COLORUNLOCKER_H

#include <QTimer>
#include <QScopedPointer>
#include "include/entity.h"


/**
 * @brief A simple color unlocking mechanism.
 *
 * This entity can be collected, and upon collecting it, a color is unlocked and can be used by the player.
 */
class ColorUnlocker : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief           ColorUnlocker constructor
     * @param x         X position of the unlocker in the scene
     * @param y         Y position of the unlocker in the scene
     * @param color     Color of the unlocker (and which will be unlocked upon collecting it)
     */
    ColorUnlocker(qreal x, qreal y,
                  const QColor color);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief Triggers events which happen upon collection
     */
    void collect();


signals:
    /**
     * @brief       Emits the signal that the unlocker has been collected and a color is unlocked
     * @param id    ID of the unlocked color
     */
    void colorUnlocked(int id);


private slots:
    /**
     * @brief       Since in idle state, the unlocker is "blinking", this method handles the opacity change
     */
    void incrementOpacity();

    /**
     * @brief       When the unlocker is collected, it is raised above the player
     */
    void raise();


private:
    const int MAX_OPACITY = 250;                //!< Maximum allowed opacity
    const int MIN_OPACITY = 200;                //!< Minimum allowed opacity
    const int MAX_RAISE_H = 50;                 //!< When the object is collected, raise it until the height reaches this value

    int _opacity;                               //!< Opacity of the entity
    int _step;                                  //!< The opacity increment step
    qreal _raiseH;                              //!< Raise height, 0 on start
    QScopedPointer<QTimer> _opacityTicker;      //!< Handles the opacity change
    QScopedPointer<QTimer> _raiseTicker;        //!< Handles the entity raising upon collection
};

#endif // COLORUNLOCKER_H
