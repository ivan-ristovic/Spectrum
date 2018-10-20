#ifndef COLORCHANGER_H
#define COLORCHANGER_H

#include <QTimer>
#include <QScopedPointer>
#include <QGraphicsView>
#include "include/entity.h"


/**
 * @brief Expanding circle which changes the active color in a pretty way.
 *
 * This entity is a circle, expanding on a timer until the whole scene is filled.
 *
 * Usual method of usage:
 * - Create a new ColorChanger object (which automatically starts expanding) from the center of the player
 * - Wait for the signal which is sent when the expanding is finished
 *
 * The signal is sent to the Game class, to stop the expanding animation and process the hidden objects.
 */
class ColorChanger : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief           ColorChanger constructor
     * @param view      The view which contains the object's scene
     * @param x         X position of the changer in the scene
     * @param y         Y position of the changer in the scene
     * @param color     Color
     */
    ColorChanger(QGraphicsView *view,
                 qreal x, qreal y,
                 const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


signals:
    /**
     * @brief Signal emitted when the expanding is stopped
     */
    void expandingDone();


private slots:
    /**
     * @brief Expands the circle by a step
     */
    void expand();


private:
    const qreal STEP = 50;                  //!< Expanding step
    const qreal MAX_DIAMETER = 1700;        //!< Max circle diameter

    QGraphicsView *_view;                   //!< Parent view, needs to be updated every time circle expands
    QScopedPointer<QTimer> _expandTicker;   //!< Timer used to expand the circle
};

#endif // COLORCHANGER_H
