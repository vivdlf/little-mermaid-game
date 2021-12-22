#include "level1dialog.h"
#include "ui_level1dialog.h"

Level1Dialog::Level1Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Level1Dialog)
{
    ui->setupUi(this);

    // Set Fixed Size
    Level1Dialog::setFixedSize(600,500);

    // Set Title
    setWindowTitle("Level 1");


    // Set Background Picture
    QPixmap bkgnd(":/images/level1DialogBg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

Level1Dialog::~Level1Dialog()
{
    delete ui;
}

void Level1Dialog::on_pushButtonOk_clicked()
{
    // Close Dialog
    emit Closed();
    Level1Dialog::close();
}
