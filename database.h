#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

// Foward declaring classes
class QSqlDatabase;

class database
{
public:
    database();
    void closeDatabase();
    bool checkUsername(QString);
    void createAccount(QString, QString, QString);
    bool logIn(QString, QString);
    bool resetPassword(QString, QString);
    QString getPlayerID(QString);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
