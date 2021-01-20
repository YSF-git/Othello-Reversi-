#ifndef OTHELLO_PLAYER_NAMES_WINDOW_H
#define OTHELLO_PLAYER_NAMES_WINDOW_H


#include <QDialog>
#include <QString>
#include <QLineEdit>

class PlayerNamesWindow : public QDialog {
Q_OBJECT

public:
    explicit PlayerNamesWindow(QWidget* parent = 0);

public:
    QLineEdit *firstname_line_edit;
    QLineEdit *secondname_line_edit;
};


#endif //OTHELLO_PLAYER_NAMES_WINDOW_H
