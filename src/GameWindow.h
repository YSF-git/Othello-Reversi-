#ifndef OTHELLO_GAME_WINDOW_H
#define OTHELLO_GAME_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QtWidgets>
#include <QMessageBox>
#include <QSound>
#include <QObject>

#include <QCloseEvent>
#include <QSqlTableModel>
#include <QDateTime>
#include <QTranslator>
#include <memory>
#include <string>

#include "./OthelloGame.h"
#include "./ClickButton.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

 private:
    QWidget* center;
    QGridLayout* grid_layout;

    QWidget *right_side_bar;
    QHBoxLayout* HB_layout;

    std::unique_ptr<OthelloGame> game;
    QString playername_black_;
    QString playername_white_;

    QPixmap* pixmap_black;
    QPixmap* pixmap_white;
    QPixmap* pixmap_empty;
    QPixmap* pixmap_white_light;
    QPixmap* pixmap_black_light;

    //QMenu *fileMenu;
    //QMenu *highScoreMenu;

    QPushButton *show_high_scores;
    QPushButton *delete_high_scores;
    QPushButton * starting_player;

    std::string undo_state;

    QMessageBox* reset_message_box;
    QSqlTableModel *model;

    QDateTime game_start;
    QDateTime game_end;

    bool afterShownCalledFlag = false;

 public:
    explicit GameWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    QString playername_black() const { return playername_black_; }
    void playername_black(const QString& playername) {
        if (playername.isNull() || playername.isEmpty()) return;
        playername_black_ = playername;
    }

    const QString& playername_white() const { return playername_white_; }
    void playername_white(const QString& playername) {
        if (playername.isNull() || playername.isEmpty()) return;
        playername_white_ = playername;
    }

    ~GameWindow();

 protected:
    void changeEvent(QEvent *) override;
    bool event(QEvent* event) override;

 private:
    //create, update, delete game grid
    void createOthelloBoard();
    void updateOthelloBoard();
    void clearOthelloBoard();

    void clickedSquareBox(unsigned int x, unsigned int y);
    bool isGameRunning();

    //reset game
    void startNewGame();

    void createMsgBox();

    void createRightHorizontalBar();

    void loadImages();

    void readSettings();
    void writeSettings();

    void createHighScoresTable();
    void createHighScore();

    void setPlayerNames();

signals:
    bool isChecked();
};


#endif  // REVERSI_MAINWINDOW_H
