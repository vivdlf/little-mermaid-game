#include "loginscreen.h"
#include "ui_loginscreen.h"

LogInScreen::LogInScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInScreen)
{
    ui->setupUi(this);

}

LogInScreen::~LogInScreen()
{
    delete ui;
}




