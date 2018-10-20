#include "ui_mainwindow.h"
#include "include/mainwindow.h"
#include <QFileDialog>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->frLevelTree->hide();
    _ui->frHelp->hide();
    _ui->gwDisplay->hide();
    _ui->btnResumeGame->hide();
    _ui->btnSaveGame->hide();
    _ui->btnChooseLevel->hide();

    _ui->gwDisplay->setRenderHint(QPainter::Antialiasing);

    connectSignalsToSlots();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::initializeGameWindow()
{
    _ui->gwDisplay->setScene(&(*_game));
    _ui->gwDisplay->raise();
    _ui->gwDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->gwDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::connectSignalsToSlots()
{
    connect(_ui->btnResumeGame, SIGNAL(clicked()), this, SLOT(resumeGame()));
    connect(_ui->btnNewGame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(_ui->btnLoadGame, SIGNAL(clicked()), this, SLOT(loadGame()));
    connect(_ui->btnSaveGame, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(_ui->btnHelp, SIGNAL(clicked()), this, SLOT(showHelp()));
    connect(_ui->btnHideHelp, SIGNAL(clicked()), this, SLOT(hideHelp()));
    connect(_ui->btnExit, SIGNAL(clicked()), this, SLOT(closeApp()));
    connect(_ui->btnChooseLevel, SIGNAL(clicked()), this, SLOT(showLevelTree()));
    connect(_ui->pbHideLevelPanel, SIGNAL(clicked()), this, SLOT(hideLevelTree()));
    connect(_ui->pbLevel1, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel2, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel3, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel4, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel5, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel6, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel7, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel8, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel9, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel10, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel11, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel12, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel13, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevel14, SIGNAL(clicked()), this, SLOT(levelLoad()));
    connect(_ui->pbLevelDemo, SIGNAL(clicked()), this, SLOT(levelLoad()));
}

void MainWindow::resumeGame()
{
    _game->resume();
    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
    _ui->frLevelTree->hide();
}

void MainWindow::newGame()
{
    _game.reset(new SpectrumGame(_ui->gwDisplay));
    initializeGameWindow();

    _ui->gwDisplay->show();
    _ui->gwDisplay->setFocus();
    _ui->btnResumeGame->show();
    _ui->btnSaveGame->show();
    _ui->btnChooseLevel->show();
}

void MainWindow::loadGame()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Choose a save file."),
                                                    QDir::currentPath(),
                                                    tr("Spectrum Save File (*.sav)"));
    if (fileName != "") {
        newGame();
        _game->load(fileName);
    }
}

void MainWindow::saveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Choose a save file."),
                                                    QDir::currentPath() + QDir::separator() + "save.sav",
                                                    tr("Spectrum Save File (*.sav)"));
    if (fileName != "")
        _game->save(fileName);
}

void MainWindow::showLevelTree()
{
    _ui->frLevelTree->show();
}

void MainWindow::hideLevelTree()
{
    _ui->frLevelTree->hide();
}

void MainWindow::showHelp()
{
    _ui->frHelp->show();
}

void MainWindow::hideHelp()
{
    _ui->frHelp->hide();
}

void MainWindow::closeApp()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::levelLoad()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    _game->loadLevel(btn->text());
    _ui->btnResumeGame->click();
}
