#ifndef OTHELLO_CREATE_HIGHSCORE_H
#define OTHELLO_CREATE_HIGHSCORE_H


#include <QSqlDatabase>
#include <QSqlQuery>

static bool CreateHighscore() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("highscore.sqlite");

    if (!database.open()) {
        qDebug("cannot create a database connection.");
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS scores (start DATETIME, end DATETIME,"
                                                   "boardsize INTEGER, moves INTEGER,"
                                                   "blackname TEXT, blackstones INTEGER,"
                                                   "whitename TEXT, whitestones INTEGER)");
    return true;
}


#endif  // OTHELLO_CREATE_HIGHSCORE_H
