#ifndef OTHELLO_HIGH_SCORE_WINDOW_H
#define OTHELLO_HIGH_SCORE_WINDOW_H

#include <QWidget>
#include <QDialog>
#include <QTableView>
#include <QDialogButtonBox>
#include <QSqlTableModel>

class HighScoreWindow : public QDialog {
    Q_OBJECT

 public:
    explicit HighScoreWindow(QSqlTableModel* table_model, QWidget* parent = 0);

 private:
    QTableView *table_view;
    QDialogButtonBox *box_button;

    void Highscore_print();
};


#endif  // OTHELLO_HIGH_SCORE_WINDOW_H
