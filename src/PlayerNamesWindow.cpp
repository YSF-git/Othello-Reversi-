#include "PlayerNamesWindow.h"

#include <QtWidgets>
#include <QPushButton>
#include <QString>
#include <QGridLayout>
#include <QDialogButtonBox>

PlayerNamesWindow::PlayerNamesWindow(QWidget* parent) : QDialog(parent) {
    setStyleSheet("background-color : #6E3B2E");
    QLabel *firstname_label = new QLabel(tr("White Color Player:"));
    firstname_label->setStyleSheet("QLabel { background-color : white; color : black; }");
    firstname_line_edit = new QLineEdit;
    firstname_line_edit->setStyleSheet("background-color : white");

    QLabel * secondname_label= new QLabel(tr("Black Color Player:"));
    secondname_label->setStyleSheet("QLabel { background-color : black; color : white; }");
    secondname_line_edit = new QLineEdit;
    secondname_line_edit->setStyleSheet("QLineEdit { background-color : black; color: white}");

    QDialogButtonBox* dialog_button = new QDialogButtonBox(QDialogButtonBox::Ok);
    dialog_button->setStyleSheet("background-color : #026633");
    connect(dialog_button, SIGNAL(accepted()), this, SLOT(accept()));

    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(firstname_label, 0, 0);
    grid_layout->addWidget(firstname_line_edit, 0, 1);
    grid_layout->addWidget(secondname_label, 1, 0);
    grid_layout->addWidget(secondname_line_edit, 1, 1);


    QVBoxLayout *vbox_mainlayout = new QVBoxLayout;
    vbox_mainlayout->addLayout(grid_layout);
    vbox_mainlayout->addWidget(dialog_button);

    setLayout(vbox_mainlayout);
    resize(380, 120);

    setWindowTitle(tr("Please specify player names"));
}
