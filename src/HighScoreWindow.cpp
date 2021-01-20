#include <QtWidgets>
#include <QTextDocument>
#include <QTextStream>
#include <QString>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>

#include "./HighScoreWindow.h"
#include "./highScoreWindowColumns.h"
#include "./utility.h"

HighScoreWindow::HighScoreWindow(QSqlTableModel* table_model, QWidget* parent) : QDialog(parent) {
    table_model->setHeaderData(as_integer(HighScoreColumns::start), Qt::Horizontal, "Start date");
    table_model->setHeaderData(as_integer(HighScoreColumns::end), Qt::Horizontal, "End date");
    table_model->setHeaderData(as_integer(HighScoreColumns::boardsize), Qt::Horizontal, "Game Board");
    table_model->setHeaderData(as_integer(HighScoreColumns::moves), Qt::Horizontal, "Move");
    table_model->setHeaderData(as_integer(HighScoreColumns::blackname), Qt::Horizontal, "Black");
    table_model->setHeaderData(as_integer(HighScoreColumns::blackstones), Qt::Horizontal, "Stones");
    table_model->setHeaderData(as_integer(HighScoreColumns::whitename), Qt::Horizontal, "White");
    table_model->setHeaderData(as_integer(HighScoreColumns::whitestones), Qt::Horizontal, "Stones");

    setStyleSheet("background-color: #87ceeb;");

    table_view = new QTableView;
    table_view->setModel(table_model);
    table_view->resizeColumnsToContents();
    table_view->verticalHeader()->hide();
    table_view->setSortingEnabled(true);
    table_view->sortByColumn(as_integer(HighScoreColumns::start), Qt::SortOrder::DescendingOrder);
    table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_view->setSelectionMode(QAbstractItemView::SingleSelection);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    box_button = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(box_button, SIGNAL(accepted()), this, SLOT(accept()));

    QVBoxLayout *main_vlayout = new QVBoxLayout;
    main_vlayout->addWidget(table_view);
    main_vlayout->addWidget(box_button);
    setLayout(main_vlayout);
    resize(680, 300);

    setWindowTitle("Highscore Window");
}

void HighScoreWindow::Highscore_print() {
    QString str_stream;
    QTextStream text_stream(&str_stream);

    const int nbr_of_rows = table_view->model()->rowCount();
    const int nbr_of_columns = table_view->model()->columnCount();

    text_stream <<  "<html>\n<head>\n<meta Content=\"Text/html; charset=Windows-1251\">\n"
            "<title>Highscore</title>\n"
            "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

    text_stream << "<thead><tr bgcolor=#dbdbdb>";
    for (int column = 0; column < nbr_of_columns; column++) {
        if (!table_view->isColumnHidden(column)) {
            text_stream << QString("<th>%1</th>").arg(
                    table_view->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    text_stream << "</tr></thead>\n";

    for (int row = 0; row < nbr_of_rows; row++) {
        text_stream << "<tr>";
        for (int column = 0; column < nbr_of_columns; column++) {
            if (!table_view->isColumnHidden(column)) {
                QString data = table_view->model()->data(
                        table_view->model()->index(row, column)).toString().simplified();
                text_stream << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        text_stream << "</tr>\n";
    }
    text_stream <<  "</table>\n</body>\n</html>\n";

    QTextDocument *text_document = new QTextDocument();
    text_document->setHtml(str_stream);

    QPrinter qprinter;

    QPrintDialog *print_dialog = new QPrintDialog(&qprinter, NULL);
    if (print_dialog->exec() == QDialog::Accepted) {
        text_document->print(&qprinter);
    }
//include in report: challenges, performance, mem leaks,
    delete text_document;
}
