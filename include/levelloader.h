#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <QScopedPointer>
#include <QTextStream>
#include <QFile>
#include <vector>
#include "include/entity.h"
#include "include/dynamicentity.h"
#include "include/player.h"


/**
 * @brief Loads a level from the level file.
 *
 * Level files are a way to store the level information.
 * During each loading of a new level, the appropriate file is opened and parsed.
 * Level names are in the format: "%3d.lvl" , level_id
 *
 * Level files start with the active color in the level.
 *
 * Each line that is starting with '#' is considered as a comment.
 *
 * At the begining of each line, there is a character which determines the function:
 * - c <color name>                             : change color
 * - p <x> <y>                                  : set player coordinates
 * - s <name> [position + additional info]      : add static entity (color is inherited from 'c' command)
 * - d <name> [position + additional info]      : add dynamic entity (color is inherited from 'c' command)
 *
 * Read the README file in /res/levels for more information.
 */
class LevelLoader
{
public:
    /**
     * @brief               LevelLoader constructor
     * @param fileName      Level file name
     */
    LevelLoader(const QString &fileName);
    ~LevelLoader();

    // Deleted functions/operators
    LevelLoader(const LevelLoader&) = delete;
    LevelLoader& operator=(const LevelLoader&) = delete;

    /**
     * @brief                   Parse level file
     * @param player            Player reference (to set location)
     * @param activeColor       Active color pointer (to set it if the level says so)
     * @param staticEntities    Pointer to static entity vector (to add entities)
     * @param dynamicEntities   Pointer to dynamic entity vector (to add entities)
     */
    void parse(Player &player,
               QColor *activeColor,
               std::vector<Entity *> &staticEntities,
               std::vector<DynamicEntity *> &dynamicEntities) const;


private:
    /**
     * @brief                   Add static entity to vector
     * @param staticEntities    Vector contatining static entities
     * @param lineStream        Line stream which will be parsed to extract data about the entity
     * @param entityColor       Current color set by 'c' command
     * @param activeColor       Current active color
     */
    void addStaticEntity(std::vector<Entity *> &staticEntities,
                         QTextStream &lineStream,
                         const QColor &entityColor,
                         const QColor &activeColor) const;

    /**
     * @brief                   Add dynamic entity to vector
     * @param dynamicEntities   Vector contatining dynamic entities
     * @param lineStream        Line stream which will be parsed to extract data about the entity
     * @param entityColor       Current color set by 'c' command
     * @param activeColor       Current active color
     */
    void addDynamicEntity(std::vector<DynamicEntity *> &dynamicEntities,
                          QTextStream &lineStream,
                          const QColor &entityColor,
                          const QColor &activeColor) const;

    /**
     * @brief                   Read color from the stream
     * @param lineStream        Line stream
     * @return                  QColor object corresponding to parsed color name
     */
    QColor readColor(QTextStream &lineStream) const;


    QScopedPointer<QFile> _levelFile;           //!< Pointer to a level file
    QScopedPointer<QTextStream> _fStream;       //!< File stream
};

#endif // LEVELLOADER_H
