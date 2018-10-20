#include "../include/colors.h"

QColor SpectrumColors::red = QColor(238, 52, 55);
QColor SpectrumColors::green = QColor(108, 210, 77);
QColor SpectrumColors::blue = QColor(40, 123, 219);
QColor SpectrumColors::purple = QColor(158, 24, 166);
QColor SpectrumColors::yellow = QColor(253, 231, 43);
QColor SpectrumColors::orange = QColor(250, 121, 33);
QColor SpectrumColors::gray = QColor(50, 50, 50);
QColor SpectrumColors::black = QColor(25, 25, 25);


QColor SpectrumColors::defaultActiveColor = SpectrumColors::blue;



QColor SpectrumColors::getColorFromName(const QString &colorName)
{
    if (colorName == "red") {
        return red;
    } else if (colorName == "green") {
        return green;
    } else if (colorName == "blue") {
        return blue;
    } else if (colorName == "yellow") {
        return yellow;
    } else if (colorName == "purple") {
        return purple;
    } else if (colorName == "orange") {
        return orange;
    } else if (colorName == "gray") {
        return gray;
    } else if (colorName == "default") {
        return defaultActiveColor;
    } else
        return defaultActiveColor;
}

QColor SpectrumColors::getColorFromID(int id)
{
    if (id == RED) {
        return red;
    } else if (id == GREEN) {
        return green;
    } else if (id == BLUE) {
        return blue;
    } else if (id == YELLOW) {
        return yellow;
    } else if (id == PURPLE) {
        return purple;
    } else if (id == ORANGE) {
        return orange;
    } else if (id == GRAY) {
        return gray;
    } else
        return defaultActiveColor;
}

int SpectrumColors::toEnum(const QColor &c)
{
    // We need a new reference color object because opacity is changing in some cases
    QColor color(c.red(), c.green(), c.blue());

    if (color == red) {
        return RED;
    } else if (color == green) {
        return GREEN;
    } else if (color == blue) {
        return BLUE;
    } else if (color == yellow) {
        return YELLOW;
    } else if (color == purple) {
        return PURPLE;
    } else if (color == orange) {
        return ORANGE;
    } else if (color == gray) {
        return GRAY;
    } else
        return DEFAULT;
}
