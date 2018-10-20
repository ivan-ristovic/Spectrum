#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "include/entity.h"


/**
 * @brief Provides a base for all entities that are moving on the scene.
 *
 * All classes derived from DynamicEntity are moving on the scene, hence they are affected by the gravity or player action.
 *
 * The moving logic is implemented in the move() function.
 *
 * The mass is there because there is a chance to add entities which are unaffected by (or affected negatively)
 * by gravity, such as helium baloons for example. For now, all items have same default mass of 1.
 */
class DynamicEntity : public Entity
{
public:
    /**
     * @brief               DynamicEntity constructor
     * @param x             X position of the entity in the scene
     * @param y             Y position of the entity in the scene
     * @param w             Width
     * @param h             Height
     * @param mass          Mass
     * @param color         Color
     * @param collidable    Collidable indicator
     */
    DynamicEntity(qreal x, qreal y, qreal w, qreal h,
                  qreal mass,
                  const QColor color = SpectrumColors::gray,
                  bool collidable = true);

    /**
     * @brief       Set the speed vector X value
     * @param vx    New vx value
     */
    void setVx(qreal vx);

    /**
     * @brief       Set the speed vector Y value
     * @param vy    New vy value
     */
    void setVy(qreal vy);

    /**
     * @brief       Set "changed"
     * @param c     New "changed" value
     */
    void setCh(double c);

    /**
     * @brief       Get "changed" value
     * @return      "changed" value
     */
    double getCh() const;

    /**
     * @brief       Get entity mass
     * @return      Mass
     */
    double getMass() const;

    /**
     * @brief       Apply the force on the entity, given as a vector
     * @param fx    Force X component
     * @param fy    Force Y component
     */
    void applyForce(qreal fx, qreal fy);

    /**
     * @brief       Apply gravity on the entity
     * @param g     Gravity coefficient
     */
    void applyGravity(qreal g);

    /**
     * @brief       Moving logic of the entity
     * @param id    Move value
     */
    void move(int id);


protected:
    bool _inAir;        //!< Determines whether the entity is in air
    qreal _mass;        //!< Entity mass
    qreal _vx;          //!< X speed component
    qreal _vy;          //!< Y speed component
    double _ch;         //!< "changed" indicator
};

#endif // DYNAMICENTITY_H
