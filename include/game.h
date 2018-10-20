#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScopedPointer>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "include/player.h"
#include "include/level.h"
#include "include/colors.h"
#include "include/colorchanger.h"
#include "include/colorchooser.h"


/**
 * @brief The main game class.
 *
 * SpectrumGame class is derived from QGraphicsScene, so entities (QGraphicsObjects) can be added to it (or removed).
 *
 * SpectrumGame class has the following functionalities:
 * - Handles level creation has control over the entities in the level
 * - Handles the keyboard/mouse events
 * - Updates the entities and level on each tick
 */
class SpectrumGame : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief           SpectrumGame constructor
     * @param parent    The view represeting the scene
     */
    SpectrumGame(QGraphicsView *parent);

    ~SpectrumGame();

    // Deleted functions/operators
    SpectrumGame(const SpectrumGame&) = delete;
    SpectrumGame& operator=(const SpectrumGame&) = delete;

    /**
     * @brief           Loads a new level based on the level name
     * @param id        A string representing level name (for example 001.lvl)
     */
    void loadLevel(const QString id);

    /**
     * @brief           Pauses the game
     */
    void pause();

    /**
     * @brief           Resumes the game
     */
    void resume();

    /**
     * @brief           Loads a game from the save file
     * @param fileName  Save file name
     */
    void load(QString &fileName);

    /**
     * @brief           Save a game to a file
     * @param fileName  Output file name
     */
    void save(QString &fileName) const;

    /**
     * @brief           Handles the interaction of a player and objects on the scene
     */
    void interact();

    /**
     * @brief           Get current active color
     * @return          Current active color
     */
    QColor activeColor() const;

    /**
     * @brief                   Sets a new active color
     * @param newActiveColor    New active color
     */
    void setActiveColor(QColor newActiveColor);

    /**
     * @brief           Check if the color is unlocked
     * @param color     QColor object containing color properties
     * @return          Unlocked indicator
     */
    bool isUnlocked(const QColor &color) const;
    /**
     * @brief           Check if the color is unlocked
     * @param colorID   ID of the color
     * @return          Unlocked indicator
     */
    bool isUnlocked(int colorID) const;


    // Event overrides
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private slots:
    /**
     * @brief       Update the scene (called on each ingame tick)
     */
    void update() const;

    /**
     * @brief       Unlocks a color with the ID given as a parameter
     * @param id    ID of the color to unlock
     */
    void unlockColor(int id);

    /**
     * @brief       Stops the color switch animation (the expanding circle)
     */
    void stopColorChangeAnimation();

    /**
     * @brief       Key collect event processer
     */
    void keyCollected();

    /**
     * @brief       Play the "game over" animation
     */
    void startGameOverAnimation();

    /**
     * @brief       Stop the "game over" animation
     */
    void stopGameOverAnimation();


private:
    /**
     * @brief           Connect the entities which can emit the signals to the corresponding slots
     * @param entities  Vector containing all the entities in the scene
     */
    void connectSlots(std::vector<Entity*> entities);

    /**
     * @brief           Change the active color based on the event
     * @param event     QKeyEvent
     */
    void changeActiveColor(QKeyEvent *event);

    /**
     * @brief           Animate color changing to a new color
     * @param color     Color of the animating circle
     */
    void animateColorChange(QColor color);

    /**
     * @brief           Hides all entities with that have the active color
     */
    void hideObjectsWithActiveColor();

    bool _paused;                                       //!< Indicates whether the game is paused or not
    bool _expandInProgress;                             //!< Indicates whether the color change animation is in progress
    QGraphicsView *_parent;                             //!< Parent view representing the current scene (SpectrumGame)
    qreal _gravCoeff = 0.25;                            //!< Gravity coefficient
    QColor _activeColor;                                //!< Current active color
    QColor _oldActiveColor;                             //!< Old active color
    QScopedPointer<Player> _player;                     //!< Player
    QScopedPointer<Level> _level;                       //!< Current level
    QScopedPointer<ColorChanger> _colorCircle;          //!< Color change expanding circle
    QScopedPointer<ColorChooser> _spectrum;             //!< Color chooser
    QScopedPointer<QTimer> _gameTicker;                 //!< Handles game update
    QScopedPointer<QTimer> _colorCircleTicker;          //!< Handles color change
    bool _unlockedColors[SpectrumColors::COLOR_NUM];    //!< Vector indicating whether a color with a given ID is unlocked
    std::vector<bool> _completedLevels;                 //!< Vector indicating whether a level with a given ID is unlocked
    
};

#endif // GAME_H
