#include "littleMermaidGame.h"
#include "ui_littleMermaidGame.h"
#include "game.h"
#include <QMessageBox>
#include <QDebug>

extern Game * game;
littleMermaidGame::littleMermaidGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::littleMermaidGame)
{
    ui->setupUi(this);
    littleMermaidGame::setFixedSize(800,600);
    ui->stackedWidget->setFixedSize(800,600);

    level1PopUp = 0;

    // Start off game
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("Little Mermaid");

    // Set background picture
    QPixmap bkgnd(":/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    // Play background music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/themeSong.mp3"));
    music->play();

    // Set username

}

// Destructor
littleMermaidGame::~littleMermaidGame()
{
    delete ui;
}

// If user clicks PLAY take them to the log in screen to either log in or create an account
void littleMermaidGame::on_pushButtonPlay_clicked()
{
    // Set correct page
    ui->stackedWidget->setCurrentIndex(1);
    setWindowTitle("Little Mermaid");

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogInf.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

// If user clicks CREATE ACCOUNT take them to page to fill out necessary information in order to create
// their account
void littleMermaidGame::on_pushButtonCreateAccount_clicked()
{
    // Set correct page - the background picture is already set
    ui->stackedWidget->setCurrentIndex(2);

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogIn.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

// If user clicks CREATE MY ACCOUNT ensure that they have all necessary information filled in and that their
// username is unqiue
void littleMermaidGame::on_pushButtonCreateMyAccount_clicked()
{
    // Create My Account is clicked

    // BEFORE any information is added onto the database we muse ensure that ALL required data has been inputed
    // if not pop up an error message

    QString errorMessage = "";

    // Checking required information in the Teacher Information Section

    if( ui->lineEditUsername->text().isEmpty() || ui->lineEditUsername->text() == " " ) // checking if field is empty or had only a space
        errorMessage += " Username field must be filled in.\n";
    if( ui->lineEditPassword->text().isEmpty() || ui->lineEditPassword->text() == " " )
        errorMessage += " Password field must be filled in.\n";
    if( ui->lineEditNickname->text().isEmpty() || ui->lineEditNickname->text() == " " )
        errorMessage += " Nickname field must be filled in.\n";

    if( errorMessage != "")
        QMessageBox::warning(this, "Error",
                             errorMessage);
    else{
        // Save information in the database

        // BEFORE we save the information into the database we must ensure that the username is unique

        if( db.checkUsername(ui->lineEditUsername->text()) )
            errorMessage = " This username already exists. Please try another one.";

        if( errorMessage != "") // If the username is not unique inform the user.
            QMessageBox::warning(this, "Error",
                                 errorMessage);
        else{
            // If the username is unique create the account.
            db.createAccount(ui->lineEditUsername->text(), ui->lineEditPassword->text(), ui->lineEditNickname->text());

            // Notify user that the account is created - DOESN'T WORK
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, "Account Created","Your account was successfully created. You may now log in.");

            // Once they have been notified take them to the log in page
            if (reply == QMessageBox::Ok)
            {
                qDebug()<<"reaches here";
                ui->stackedWidget->setCurrentIndex(3);
            }
        }

    }

}

// If user click LOG IN take them to page to enter their log in credentials
void littleMermaidGame::on_pushButtonLogIn_clicked()
{
    // Set current page - the background picture is already set
    ui->stackedWidget->setCurrentIndex(3);

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogIn.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

// Ensure that log in credentials are correct
void littleMermaidGame::on_pushButtonLogIntoAccount_clicked()
{
    bool login = db.logIn(ui->lineEditUsernameEnter->text(), ui->lineEditPasswordEnter->text());

    if( login ) // Log in is successful
    {
        ui->pushButtonUsersname->setText(ui->lineEditUsernameEnter->text());
        // Set background picture
        QPixmap bkgnd(":/images/levelbg.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

        ui->stackedWidget->setCurrentIndex(5);

    }
    else // Log in is not successful therefore inform user
    {
        QMessageBox::warning(this, "Login failed",
                             "Invalid username or password.");
    }
}

// If user clicks that they forgot their password then take them to the page toreset their password
void littleMermaidGame::on_pushButtonForgotYourPassword_clicked()
{
    // Set current page - the background picture is already set
    ui->stackedWidget->setCurrentIndex(4);

}

// Resets an already existing user's password
void littleMermaidGame::on_pushButtonResetPassword_clicked()
{
    // Reset password
    bool ans = db.resetPassword(ui->lineEditUsernameForgot->text(), ui->lineEditPasswordForgot->text());

    if( ans )
    {
        // Notify user that their password has been reset - DOESN'T WORK
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Password Reset","Your password was successfully reset. You may now log in.");

        // Once they click OK take them to the log in page
        if (reply == QMessageBox::Ok) {
            qDebug()<<"reaches here";
            ui->stackedWidget->setCurrentIndex(3);
        }
    }
    else
    {
        QMessageBox::warning(this, "Password reset failed", "Username does not exist.");
    }
}

// User wants to log out
void littleMermaidGame::on_pushButtonLogOut_clicked()
{
    db.closeDatabase();
    littleMermaidGame::close();
}

// User clicks Back and is sent to the Page where all levels are shown
void littleMermaidGame::on_pushButtonBack_clicked()
{
    // Set Current Page
    ui->stackedWidget->setCurrentIndex(5);

    // Set background picture
    QPixmap bkgnd(":/images/levelbg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

// Once the user clicks their name they will be shown their TOP 10 scores
void littleMermaidGame::on_pushButtonUsersname_clicked()
{
    // Set Current Page
    ui->stackedWidget->setCurrentIndex(6);

    // Set background picture
    QPixmap bkgnd(":/images/myScoreBoardBg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    // Load the table that will display the TOP 10 scores
    loadMyTopScoresTableView();
}

// Loads the TOP 10 scores
void littleMermaidGame::loadMyTopScoresTableView()
{
    // Get player ID
    QString player_ID = db.getPlayerID(ui->lineEditUsernameEnter->text());

    // Create QSqlModel and get the TOP 10 scores from the database
    myTopScores =  new QSqlQueryModel;
    myTopScores->setQuery("SELECT Score AS TOP_SCORES FROM level_rounds WHERE Player_ID = '" +
                          player_ID + "' ORDER BY Score DESC LIMIT 10");
    ui->tableViewMyTopScores->setModel(myTopScores);

    // Disable the grid from the table
    ui->tableViewMyTopScores->setShowGrid(false);
}

// When user clicks back show log in page
void littleMermaidGame::on_pushButtonBackToLogin_clicked()
{
    // Set Current Page
    ui->stackedWidget->setCurrentIndex(1);

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogInf.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

// When user clicks back show log in page
void littleMermaidGame::on_pushButtonBackForgot_clicked()
{
    // Set Current Page
    ui->stackedWidget->setCurrentIndex(1);

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogInf.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

// Pop up Dialog that gives the user instructions
void littleMermaidGame::on_pushButtonLevel1_clicked()
{
    // Pop up Dialog
    if(!level1PopUp)
        level1PopUp = new Level1Dialog();

    level1PopUp->show();
    level1PopUp->raise();
    level1PopUp->activateWindow();

    connect(level1PopUp, SIGNAL(Closed()), this, SLOT(startGame()));
}

// When user clicks back show log in page
void littleMermaidGame::on_pushButtonBackCreate_clicked()
{
    // Set Current Page
    ui->stackedWidget->setCurrentIndex(1);

    // Set background picture
    QPixmap bkgnd(":/images/backgroundLogInf.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void littleMermaidGame::startGame()
{
    game = new Game();
}
