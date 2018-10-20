#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QFile>
#include <QScopedPointer>
#include <QTextStream>


/**
 * @brief Loads/Saves the game state.
 *
 * The main functionality of GameLoader is saving/loading the game.
 *
 * The game save state is made of the current unlocked colors, the current level and the unlocked levels vector.
 *
 * Upon loading/saving, they are all set to those values.
 */
class GameLoader
{
public:
    /**
     * @brief           GameLoader constructor
     * @param fileName  File to save/load from
     * @param flag      Flag to determine whether to save ('w'), or load ('r')
     */
    GameLoader(const QString &fileName, char flag);
    ~GameLoader();

    // Deleted functions/operators
    GameLoader(const GameLoader&) = delete;
    GameLoader& operator=(const GameLoader&) = delete;

    /**
     * @brief   Get the file validity indicator
     * @return  File validity indicator
     */
    bool isValid() const;

    /**
     * @brief                   Read game data from the file
     * @param unlockedColors    Unlocked colors vector
     * @param completedLevels   Completed levels vector
     * @return                  Level name to load from the caller
     */
    QString readGameData(bool unlockedColors[],
                          std::vector<bool> &completedLevels);

    /**
     * @brief                   Write game data to the file
     * @param levelID           Current level ID
     * @param unlockedColors    Unlocked colors vector
     * @param completedLevels   Completed levels vector
     */
    void writeGameData(unsigned levelID,
                       const bool unlockedColors[],
                       const std::vector<bool> &completedLevels);


private:
    bool _valid;                            //!< Determines whether the file opening went alright
    QScopedPointer<QFile> _gameSaveFile;    //!< QFile pointer to a game save file
    QScopedPointer<QTextStream> _fStream;   //!< File stream
};

#endif // GAMELOADER_H
