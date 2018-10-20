#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include "include/colors.h"


/**
 * @brief Provides a drawing base for all objects
 *
 * The Entity class is derived from QGraphicsObject, which is a virtual class (and is virtual itself).
 * Hence, any class which is derived from Entity must implement the methods overridden from QGraphicsObject.
 */
class Entity : public QGraphicsObject
{
    Q_OBJECT

public:
    /**
     * @brief               Constructor
     * @param x             X position of the item in scene
     * @param y             Y position of the item in scene
     * @param w             Width
     * @param h             Height
     * @param color         Item color
     * @param collidable    Indicates whether the item is collidable or not
     */
    Entity(qreal x, qreal y, qreal w, qreal h,
           const QColor color = SpectrumColors::gray,
           bool collidable = true);

    // Overrides from QGraphicsObject
    virtual void hide();
    virtual void show();
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;


    /**
     * @brief   Get entity height
     * @return  Entity height
     */
    qreal h() const;

    /**
     * @brief   Get entity width
     * @return  Entity width
     */
    qreal w() const;

    /**
     * @brief   Color getter
     * @return  QColor object representing the Entity color
     */
    QColor color() const;

    /**
     * @brief           Color setter
     * @param newColor  New Entity color
     */
    void setColor(const QColor newColor);

    /**
     * @brief   Collidable getter
     * @return  Boolean value indicating whether the entity is collidable
     */
    bool collidable() const;

    /**
     * @brief   Get X coordinate of the center in parent coordinate system
     * @return  X coordinate of the center
     */
    virtual qreal centerX() const;

    /**
     * @brief   Get Y coordinate of the center in parent coordinate system
     * @return  Y coordinate of the center
     */
    virtual qreal centerY() const;


protected:
    qreal _w;           //!< Width
    qreal _h;           //!< Height
    QColor _color;      //!< Color
    bool _collidable;   //!< Collidable indicator
};

#endif // ENTITY_H
