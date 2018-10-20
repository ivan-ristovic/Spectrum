#ifndef KEY_H
#define KEY_H

#include <QTimer>
#include <vector>
#include "include/entity.h"
#include "include/door.h"


/**
 * @brief An entity which unlockes the locked doors.
 *
 * Doors can generally be locked, and the way to unlock them is to collect the key.
 *
 * Each Door has a Key that unlocks the door. Upon collecting, the key is removed from the scene.
 */
class Key : public Entity
{
    Q_OBJECT

public:
    /**
     * @brief           Key constructor
     * @param x         X position of the key in scene
     * @param y         Y position of the key in scene
     * @param door      Door that the key unlocks
     * @param color     Key color
     */
    Key(qreal x, qreal y,
        Door *door,
        const QColor color = SpectrumColors::gray);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * @brief Key collect handler
     */
    void collect();


signals:
    /**
     * @brief Key collected signal
     */
    void collected();


private slots:
    /**
     * @brief Update key shining sparkles
     */
    void updateSparklesPos();


private:
    /**
     * @brief Unlock the door which correspond to this key
     */
    void unlockDoor();

    /**
     * @brief Lock the door which correspond to this key
     */
    void lockDoor();

    Door *_door;                                //!< Locked door pointer
    QScopedPointer<QTimer> _sparkTicker;        //!< Handles sparkles animation
    const unsigned _sparkNum = 5;               //!< Number of sparks
    std::vector<int> _sx {0, 0, 0, 0, 0};       //!< Sparks X position
    std::vector<int> _sy {0, 0, 0, 0, 0};       //!< Sparks Y position
};

#endif // KEY_H
