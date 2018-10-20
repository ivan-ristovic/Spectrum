#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QtGlobal>
#include <QObject>
#include <QTimer>


/**
 * @brief An class representing collections of images used for the animations
 */
class Sprite : QObject
{
    Q_OBJECT

public:
    /**
     * @brief   Sprite constructor
     */
    Sprite();

    /**
     * @brief   Start the sprite slideshow
     */
    void startAnimation();

    /**
     * @brief   Stop the sprite slideshow
     */
    void stopAnimation();

    /**
     * @brief   Indicates if the animation is already active
     * @return  Animation running indicator
     */
    bool animationActive() const;

    /**
     * @brief   Return inLoop indicator
     * @return  inLoop indicator
     */
    bool inLoop() const;

    /**
     * @brief   Set inLoop indicator
     * @param b New inLoop value
     */
    void setLoop(bool b);

    /**
     * @brief   Get slideshow timer interval
     * @return  Timer interval
     */
    int tickerInterval() const;

    /**
     * @brief       Set slideshow timer interval
     * @param ms    New interval value in ms
     */
    void setTickerInterval(int ms);

    /**
     * @brief   Get the next animation frame
     * @return  Next frame
     */
    QPixmap nextFrame() const;

    /**
     * @brief           Add a frame to the slideshow
     * @param frame     Frame to add
     */
    void addFrame(const QString& frame);


private slots:
    /**
     * @brief Change the current image
     */
    void change();


private:
    std::vector<QPixmap> _sprites;      //!< Sprites vector
    unsigned _current;                  //!< Current sprite image index
    bool _inLoop;                       //!< rename pls
    QTimer _ticker;                     //!< Animation ticker
};

#endif // SPRITE_H
