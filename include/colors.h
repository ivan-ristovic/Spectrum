#ifndef COLORS_H
#define COLORS_H

#include <QColor>


/**
 * @brief This class contains all the colors used by the game and their IDs.
 */
class SpectrumColors
{
public:
    SpectrumColors();

    static QColor red;
    static QColor green;
    static QColor blue;
    static QColor purple;
    static QColor yellow;
    static QColor orange;
    static QColor gray;
    static QColor black;
    static QColor defaultActiveColor;

    static const int COLOR_NUM = 6;
    static const int BLUE = 0;
    static const int PURPLE = 1;
    static const int RED = 2;
    static const int YELLOW = 3;
    static const int ORANGE = 4;
    static const int GREEN = 5;
    static const int GRAY = 6;
    static const int DEFAULT = BLUE;

    /**
     * @brief               Get a color based on the name
     * @param colorName     The name of the color
     * @return              Resulting color object
     */
    static QColor getColorFromName(const QString &colorName);

    /**
     * @brief               Get a color based on the ID
     * @param id            The ID of the color
     * @return              Resulting color object
     */
    static QColor getColorFromID(int id);

    /**
     * @brief               Get a color ID based on the color object
     * @param color         Color object
     * @return              Resulting color ID
     */
    static int toEnum(const QColor &color);
};

#endif // COLORS_H
