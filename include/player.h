#ifndef PLAYER_H
#define PLAYER_H

#include <QScopedPointer>
#include <QPixmap>
#include <QTimer>
#include <typeinfo>
#include "include/dynamicentity.h"
#include "include/sprite.h"


/**
 * @brief Pawn controlled by user.
 *
 * This is the only entity that can move using the keyboard.
 *
 * You can move around, jump, interact... Explore!
 */
class Player : public DynamicEntity
{
    Q_OBJECT

public:
    /**
     * @brief       Player constructor
     * @param x     X position of the player in the scene
     * @param y     Y position of the player in the scene
     */
    Player(qreal x = 0, qreal y = 0);

    /**
     * @brief       Set the jump indicator
     * @param b     New indicator value
     */
    void setJump(bool b);

    /**
     * @brief       Set left movement indicator
     * @param b     New indicator value
     */
    void setLeft(bool b);

    /**
     * @brief       Set right movement indicator
     * @param b     New indicator value
     */
    void setRight(bool b);

    /**
     * @brief       Set up movement indicator
     * @param b     New indicator value
     */
    void setUp(bool b);

    /**
     * @brief       Set down movement indicator
     * @param b     New indicator value
     */
    void setDown(bool b);

    /**
     * @brief       Get pull indicator value
     * @return      Pull indicator value
     */
    bool getPull();

    /**
     * @brief       Set pull indicator
     * @param b     New indicator value
     */
    void setPull(bool b);
    int angle();
    void setAngle(int a);

    /**
     * @brief   Initialize images for the blinking animation
     */
    void initializeBlinkSprite();

    /**
     * @brief   Initialize images for the jumping animation
     */
    void initializeJumpSprite();

    /**
     * @brief   Initialize images for the walking animation
     */
    void initializeWalkSprite();

    /**
     * @brief   Get a jumping sprite reference
     * @return  Reference to a jumping sprite object
     */
    Sprite& jumpSprite();

    /**
     * @brief   Get a walking sprite reference
     * @return  Reference to a walking sprite object
     */
    Sprite& walkSprite();
    bool isAlive() const;
    void setIsAlive(bool b);

    // Overrides from Entity
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    qreal centerX() const override;
    qreal centerY() const override;

    /**
     * @brief   Handles the player movement
     */
    void movement();

    /**
     * @brief   Handles the ladder movement
     * @return  ???
     */
    bool go();

    /**
     * @brief   Handles the jumping
     */
    void jump();
    void flip();


signals:
    /**
     * @brief   Emitted if the player has collision with a "deadly" entity
     */
    void playerHit();


private slots:
    /**
     * @brief   Starts the blinking animation
     */
    void blinkAnimation();
    void incrementAngle();


private:
    bool _jump = false;                 //!< Jumping indicator
    int _canJump = 2;                   //!< Determines if the player can jump
    bool _up = false;                   //!< Up movement indicator
    bool _down = false;                 //!< Down movement indicator
    bool _right = false;                //!< Right movement indicator
    bool _left = false;                 //!< Left movement indicator
    bool pull = false;                  //!< Pull indicator
    bool onLadder = false;              //!< Determines whether the player is on the ladder

    QPixmap _body;                      //!< Body sprite component
    QPixmap _armsAndLegs;               //!< Arms and legs sprite component
    QPixmap _arms;                      //!< Arms sprite component

    Sprite _walkSprite;                 //!< Walking animation object
    Sprite _blinkSprite;                //!< Blinking animation obejct
    Sprite _jumpSprite;                 //!< Handles jumping

    int _angle;                         //!< Handles rotation angle
    QScopedPointer<QTimer> _flipTicker; //!< Handles rotation animation
    
    QPixmap _deadEye;                   //!< Dead eye sprite component
    bool _isAlive;                      //!< Dead eye sprite indicator

    QTimer _blinkTicker;                //!< Handles blinking animation
};

#endif // PLAYER_H
