#ifndef LITTLEMERMAIDGAME_H
#define LITTLEMERMAIDGAME_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QSqlQueryModel>
#include "level1dialog.h"
#include "database.h"

namespace Ui {
class littleMermaidGame;
}

class littleMermaidGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit littleMermaidGame(QWidget *parent = nullptr);
    ~littleMermaidGame();

private slots:
    void on_pushButtonPlay_clicked();

    void on_pushButtonCreateAccount_clicked();

    void on_pushButtonCreateMyAccount_clicked();

    void on_pushButtonLogIn_clicked();

    void on_pushButtonLogIntoAccount_clicked();

    void on_pushButtonForgotYourPassword_clicked();

    void on_pushButtonResetPassword_clicked();

    void on_pushButtonLogOut_clicked();

    void on_pushButtonBack_clicked();

    void on_pushButtonUsersname_clicked();

    void loadMyTopScoresTableView();

    void on_pushButtonBackToLogin_clicked();

    void on_pushButtonBackForgot_clicked();

    void on_pushButtonLevel1_clicked();

    void on_pushButtonBackCreate_clicked();

    void startGame();

private:
    Ui::littleMermaidGame *ui;
    database db;
    QMediaPlayer * music;
    QSqlQueryModel *myTopScores;
    Level1Dialog *level1PopUp;
};

#endif // LITTLEMERMAIDGAME_H
