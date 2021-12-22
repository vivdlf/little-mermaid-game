#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

// This class handles all database related things

// Constructor establishes a connection with the database.
database::database()
{
    // Establishing database connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("viviannie");
    db.setPassword("loveyourselfirst");
    db.setDatabaseName("game");
    if (!db.open())
    {
        qDebug() << "Failed to connect to database.";
        qDebug()<<  db.lastError().text();
    }
}
// Ensures there are no memory leaks by terminating the connection with the database
void database::closeDatabase()
{
    // Ensures that the database connection is closed
    db.close();
}

// Ensures that the username is unique
bool database::checkUsername(QString Username)
{
    QSqlQuery query;

    query.exec( "SELECT Username from Player WHERE Username = '" + Username + "' ");

    if( query.size() > 0 ) // The username already exists
        return true; // Return true if the username already exists
    else
        return false; // Return false if the username is unqiue
}

// Creates a Player Record
void database::createAccount(QString Username, QString Password, QString Nickname)
{
    // Creating record in Player Table
    QSqlQuery query;

    if ( query.exec( "INSERT INTO player(player_ID, Username, Password, Nickname)VALUES  ('NULL','" + Username + "','" + Password + "','" + Nickname + "')") )
        qDebug() << "Insertion success - User table";
    else
        qDebug() << query.lastError().text();
}

// Checks if log in credentials are correct
bool database::logIn(QString Username, QString Password)
{
    QSqlQuery query;

    query.exec( "SELECT Username from player WHERE Username = '" + Username + "' AND Password = '" +
                Password + "'"  );

    if ( query.size() > 0 )
        return true; // If credentials are correct return true
    else
        return false; // If credentials are wrong return false
}

// Resets a user's password
bool database::resetPassword(QString Username, QString Password)
{
    QSqlQuery query;

    // Update password column with new password
    query.exec("UPDATE player SET player.Password = '" +
               Password + "' WHERE Username = '" +
               Username + "'" );
    if( query.size() > 0 )
        return true;
    else
        return false;
}

// Returns the playerID
QString database::getPlayerID(QString Username)
{
    QSqlQuery query;
    QString player_ID ;

    // Get player_ID
    query.exec("SELECT player_ID FROM player WHERE Username= '" +
               Username + "'");

    while( query.next() )
        player_ID = query.value(0).toString();

    qDebug()<<query.value(0).toString();
    return player_ID;
}
