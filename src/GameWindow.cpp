#include "./GameWindow.h"

#include <QAbstractButton>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStatusBar>
#include <QString>
#include <QWidget>
#include <QWidgetItem>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTimer>
#include <QApplication>

#include <QDebug>

#include <memory>
#include <sstream>

#include "./ClickButton.h"
#include "./stone.h"
#include "./OthelloGame.h"
#include "./FixedAspectRatioWidget.h"
#include "./highScoreWindowColumns.h"
#include "./utility.h"
#include "./HighScoreWindow.h"
#include "./PlayerNamesWindow.h"

GameWindow::GameWindow(QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags),
          game(std::make_unique<OthelloGame>()),
          playername_white_("Player White"),
          playername_black_("Player Black") {
    game->display_board();
    setObjectName("MainWindow");

    createMsgBox();

    loadImages();

    createRightHorizontalBar();
    createOthelloBoard();
    updateOthelloBoard();

    //black = nullptr;

    readSettings();

    createHighScoresTable();


    statusBar()->showMessage("Game Status");
}

void GameWindow::changeEvent(QEvent *e) {

        QMainWindow::changeEvent(e);

}

void GameWindow::loadImages() {
    pixmap_black = new QPixmap();
    if (!pixmap_black->load(":/black.png" ))
        qWarning("Failed to load black.png");

    pixmap_white = new QPixmap();
    if (!pixmap_white->load(":/white.png" ))
        qWarning("Failed to load white.png");

    pixmap_empty = new QPixmap();
    if (!pixmap_empty->load(":/empty.png" ))
        qWarning("Failed to load empty.png");

    pixmap_white_light = new QPixmap();
    if (!pixmap_white_light->load(":/white_light.png" ))
        qWarning("Failed to load white_light.png");

    pixmap_black_light = new QPixmap();
    if (!pixmap_black_light->load(":/black_light.png" ))
        qWarning("Failed to load black_light.png");
}

GameWindow::~GameWindow() {
}

void GameWindow::createRightHorizontalBar() {
    right_side_bar = new QWidget(this);
    right_side_bar->setStyleSheet("background-color: #026633;");
    right_side_bar->setMinimumWidth(200);


    QPushButton *exitButton = new QPushButton("Quit Game", right_side_bar);
    exitButton->setStyleSheet("background-color: #4A2619;color : white;");
    exitButton->setGeometry(QRect(QPoint(60, 500), QSize(100, 50)));
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(exitButton, &QPushButton::clicked, this, &GameWindow::close);

    starting_player = new QPushButton("Black starts", right_side_bar);
    starting_player->setStyleSheet("background-color: #4A2619;color : white;");
    starting_player->setCheckable(true);
    starting_player->setGeometry(QRect(QPoint(50, 160), QSize(130, 30)));
    starting_player->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(starting_player, &QPushButton::clicked, [this](bool checked){
        if (!isGameRunning() || (reset_message_box->exec() == QMessageBox::Ok)) {
            game = std::make_unique<OthelloGame>(game->BoardSize(),
                                                 checked ? Stone::black : Stone::white);
            startNewGame();
        }
    });


    QPushButton * PB_new_game = new QPushButton("New Game", right_side_bar);
    PB_new_game->setStyleSheet("background-color: #4A2619;color : white;");
    PB_new_game->setGeometry(QRect(QPoint(50, 40), QSize(130, 30)));
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(PB_new_game, &QPushButton::clicked, [this]{
        if (!isGameRunning() || (reset_message_box->exec() == QMessageBox::Ok)) {
            Stone starter = starting_player->isChecked() ? Stone::black : Stone::white;
            game = std::make_unique<OthelloGame>(game->BoardSize(), starter);
            startNewGame();
        }
    });

    show_high_scores = new QPushButton("Show High Scores", right_side_bar);
    show_high_scores->setStyleSheet("background-color: #4A2619;color : white;");
    show_high_scores->setGeometry(QRect(QPoint(50, 80), QSize(130, 30)));
    show_high_scores->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    show_high_scores->setStatusTip("Shows the saved scores");
    connect(show_high_scores, &QPushButton::clicked, [this] {
        HighScoreWindow dialog(model);
        dialog.exec();
    });

    delete_high_scores = new QPushButton("Delete High Scores", right_side_bar);
    delete_high_scores->setStyleSheet("background-color: #4A2619;color : white;");
    delete_high_scores->setGeometry(QRect(QPoint(50, 120), QSize(130, 30)));
    delete_high_scores->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delete_high_scores->setStatusTip("Delete all the saved scores");
    connect(delete_high_scores, &QPushButton::clicked, [this] {

        QSqlQuery query;
        query.exec("DELETE FROM scores;");
        model->select();
    });

}

void GameWindow::createOthelloBoard() {
    grid_layout = new QGridLayout;
    grid_layout->setSpacing(0);
    grid_layout->setMargin(0);

    for (int x = game->BoardSize(); x-- > 0; ) {
        for (int y = game->BoardSize(); y-- > 0; ) {
            ClickButton* label = new ClickButton(this);
            label->setMinimumSize(50, 50);
            label->setFrameStyle(QFrame::Panel + QFrame::Sunken);
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap(*pixmap_empty);



            connect(label, &ClickButton::clicked, [this, x, y, label]{ clickedSquareBox(x, y); });

            grid_layout->addWidget(label, y, x);
        }
    }

    HB_layout = new QHBoxLayout();
    FixedAspectRationWidget* dummy = new FixedAspectRationWidget;
    dummy->setLayout(grid_layout);
    HB_layout->addWidget(dummy);
    HB_layout->addWidget(right_side_bar);

    center = new QWidget(this);  // dummy wrapper widget
    center->setStyleSheet("background-color: #026633;");
    center->setLayout(HB_layout);

    setCentralWidget(center);
}

void GameWindow::clearOthelloBoard() {
    for (unsigned int x = 0; x < grid_layout->columnCount(); ++x) {
        for (unsigned int y = 0; y < grid_layout->rowCount(); ++y) {
            QLayoutItem *item = grid_layout->itemAtPosition(y, x);
            auto label = dynamic_cast<ClickButton*>(item->widget());
            label->setPixmap(*pixmap_empty);
        }
    }
}

void GameWindow::clickedSquareBox(unsigned int x, unsigned int y) {
    qDebug() << "clicked " << x << ", " << y;
    qDebug() << "checked " << x << ", " << game->BoardSize() - y - 1;

    if (game->CheckValidMove({x, game->BoardSize() - y - 1})) {

        std::stringstream ss;
        ss << (game->ReturnActivePlayerPiece() == Stone::black ? playername_black_.toStdString() : playername_white_.toStdString());
        ss << " inserted a stone at location [" << x << ", " << y << "]. Now it's ";

        qDebug() << QString::fromStdString(ss.str());

        if (game->MovesPlayed() == 0)
            game_start = QDateTime::currentDateTime();

        undo_state = game->BoardToString();
        game->MakePlayerMove({x, game->BoardSize() - y - 1});

        ss << (game->ReturnActivePlayerPiece() == Stone::black ? playername_black_.toStdString() : playername_white_.toStdString()) << " turn.";
        statusBar()->showMessage(QString::fromStdString(ss.str()));
        updateOthelloBoard();
    } else {
        qDebug("This move is not possible");
    }
    if  (game->GetPossibleMoves().size() == 0) {
        game_end = QDateTime::currentDateTime();
        unsigned int score_white, score_black;
        std::tie(score_white, score_black) = game->GetCurrentScore();

        statusBar()->showMessage("Gae finished");

        createHighScore();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Game finished!");
        msgBox.setStyleSheet("background-color: #87ceeb;");
        if (score_white > score_black) {
            msgBox.setText(playername_white_ + " won!");
        } else if (score_white < score_black) {
            msgBox.setText(playername_black_ + " won!");
        } else {
            msgBox.setText("It's a draw!");
        }
        msgBox.setInformativeText(QString("%1 has %2 stones. %3 has %4 stones. Do you want to restart or close the game?")
                                          .arg(playername_white_).arg(score_white)
                                          .arg(playername_black_).arg(score_black));
        QPushButton *connectButton = msgBox.addButton("Restart", QMessageBox::ActionRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (qobject_cast<QPushButton *>(msgBox.clickedButton()) == connectButton) {
            game = std::make_unique<OthelloGame>(game->BoardSize());
            startNewGame();
        } else if (qobject_cast<QPushButton *>(msgBox.clickedButton()) == closeButton) {
            this->close();
        }
    }
}

void GameWindow::updateOthelloBoard() {
    for (unsigned int x = 0; x < grid_layout->columnCount(); ++x) {
        for (unsigned int y = 0; y < grid_layout->rowCount(); ++y) {
            QLayoutItem *item = grid_layout->itemAtPosition(y, x);
            auto label = dynamic_cast<ClickButton*>(item->widget());

            Stone p = game->GetSquarePiece({x, game->BoardSize() - y - 1});


            if (p == Stone::black) {
                label->setPixmap(*pixmap_black);
            } else if (p == Stone::white) {
                label->setPixmap(*pixmap_white);
            } else {
                label->setPixmap(*pixmap_empty);
            }

            if (game->CheckValidMove({x, game->BoardSize() - y - 1})) {
                if (game->ReturnActivePlayerPiece() == Stone::black)
                    label->setPixmap(*pixmap_black_light);
                else
                    label->setPixmap(*pixmap_white_light);
            }

        label->setScaledContents(true);
        }
    }
}

void GameWindow::startNewGame() {
    if (grid_layout->columnCount() == game->BoardSize()) {
        clearOthelloBoard();
    } else {
        createOthelloBoard();
    }
    updateOthelloBoard();
}

bool GameWindow::isGameRunning() {
    return game->MovesPlayed() > 0 && game->CheckForPossibleMoves();
}

void GameWindow::createMsgBox() {
    reset_message_box = new QMessageBox(this);
    reset_message_box->setStyleSheet("background-color: #87ceeb;");
    reset_message_box->setText("New game:");
    reset_message_box->setInformativeText("Do you want to start a new game?");
    reset_message_box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    reset_message_box->setDefaultButton(QMessageBox::Ok);
}
/**
 * @brief MainWindow::readSettings adjusts window size
 * @param none
 * @returns void
 */
void GameWindow::readSettings() {
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(800, 650)).toSize();
    resize(size);
    move(pos);
}

void GameWindow::writeSettings() {
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void GameWindow::createHighScoresTable() {
    model = new QSqlTableModel(this);
    model->setTable("scores");
    model->select();
}

void GameWindow::createHighScore() {
    const QString DFORMAT = "yyyy-MM-dd HH:mm:ss";
    QSqlRecord record = model->record();
    record.setValue(as_integer(HighScoreColumns::start), game_start.toString(DFORMAT));
    record.setValue(as_integer(HighScoreColumns::end), game_end.toString(DFORMAT));
    record.setValue(as_integer(HighScoreColumns::boardsize), game->BoardSize());
    record.setValue(as_integer(HighScoreColumns::moves), game->MovesPlayed());
    unsigned int score_white, score_black;
    std::tie(score_white, score_black) = game->GetCurrentScore();
    record.setValue(as_integer(HighScoreColumns::blackname), playername_black_);
    record.setValue(as_integer(HighScoreColumns::blackstones), score_black);
    record.setValue(as_integer(HighScoreColumns::whitename), playername_white_);
    record.setValue(as_integer(HighScoreColumns::whitestones), score_white);
    model->insertRecord(-1, record);
}

void GameWindow::setPlayerNames() {
    PlayerNamesWindow dialog;
    dialog.firstname_line_edit->setText(playername_white_);
    dialog.secondname_line_edit->setText(playername_black_);
    dialog.exec();

    if (!dialog.firstname_line_edit->text().isEmpty())
        playername_white_ = dialog.firstname_line_edit->text();

    if (!dialog.secondname_line_edit->text().isEmpty())
        playername_black_ = dialog.secondname_line_edit->text();
}

bool GameWindow::event(QEvent *event) {
    int returnValue = QWidget::event(event);

    if (!afterShownCalledFlag && event->type() == QEvent::Show) {
        setPlayerNames();
        afterShownCalledFlag = true;
        return true;
    }

    return returnValue;
}
