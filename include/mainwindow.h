#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include "include/game.h"



namespace Ui {

class MainWindow;
}

/**
 * @brief GUI window containing the game scene.
 *
 * Generated by Qt Creator
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Deleted functions/operators
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;


private slots:
    /**
     * @brief Resume a paused game
     */
    void resumeGame();

    /**
     * @brief Create a new game
     */
    void newGame();

    /**
     * @brief Load a game state from the save file
     */
    void loadGame();

    /**
     * @brief Save a game state to a file
     */
    void saveGame();

    /**
     * @brief Show level map
     */
    void showLevelTree();

    /**
     * @brief Hide level map
     */
    void hideLevelTree();

    /**
     * @brief Load a level
     */
    void levelLoad();
    
    /**
     * @brief Show help
     */
    void showHelp();
    
    /**
     * @brief Hide help
     */
    void hideHelp();

    /**
     * @brief Exit the game
     */
    void closeApp();


private:
    /**
     * @brief Prepare the window for the new scene
     */
    void initializeGameWindow();

    /**
     * @brief Connect all the GUI elements to the corresponding slots
     */
    void connectSignalsToSlots();


    Ui::MainWindow *_ui;                    //!< User interface
    QScopedPointer<SpectrumGame> _game;     //!< Game instance
};

#endif // MAINWINDOW_H
