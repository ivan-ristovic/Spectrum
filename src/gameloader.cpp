#include "include/gameloader.h"
#include "include/colors.h"
#include <QMessageBox>


GameLoader::GameLoader(const QString &fileName, char flag) :
    _valid(true),
    _gameSaveFile(new QFile(fileName))
{
    if (flag == 'r')  {
        if(_gameSaveFile->open(QIODevice::ReadOnly) == false) {
            QMessageBox::information(nullptr, "Error", "Loading game failed\nCreating new game...");
            _valid = false;
        }
    } else if (flag == 'w') {
        if (_gameSaveFile->open(QIODevice::WriteOnly) == false) {
            QMessageBox::information(nullptr, "Error", "Saving game failed");
            _valid = false;
        }
    } else
        _valid = false;

    if (_valid)
        _fStream.reset(new QTextStream(_gameSaveFile.data()));
}

GameLoader::~GameLoader()
{
    _gameSaveFile->close();
}

bool GameLoader::isValid() const
{
    return _valid;
}

QString GameLoader::readGameData(bool unlockedColors[],
                                 std::vector<bool> &completedLevels)
{
    // Read level ID
    QString level = _fStream->readLine().trimmed();

    // Read unlocked color IDs
    QString line = _fStream->readLine().trimmed();
    QTextStream colorsLineStream(&line);
    while (!colorsLineStream.atEnd()) {
        int id;
        colorsLineStream >> id;
        unlockedColors[id] = true;
    }

    if (level.toUInt() >= completedLevels.size())
        completedLevels.resize(level.toInt() + 1, false);

    // Read completed level IDs
    line = _fStream->readLine().trimmed();
    QTextStream levelsLineStream(&line);
    while (!levelsLineStream.atEnd()) {
        int id;
        levelsLineStream >> id;
        completedLevels[id] = true;
    }

    return level;
}

void GameLoader::writeGameData(unsigned levelID,
                               const bool unlockedColors[],
                               const std::vector<bool> &completedLevels)
{
    // Writing level ID
    QString lvlNumber = QString("%1").arg(levelID, 3, 10, QChar('0'));
    *_fStream << lvlNumber + "\n";

    // Writing unlocked color IDs
    for (unsigned i = 0; i < SpectrumColors::COLOR_NUM; i++)
        if (unlockedColors[i])
            *_fStream << i << " ";
    *_fStream << "\n";

    // Writing completed level IDs
    for (unsigned i = 0; i < completedLevels.size(); i++)
        if (completedLevels[i])
            *_fStream << i << " ";
    *_fStream << "\n";
}
