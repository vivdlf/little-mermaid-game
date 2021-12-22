#ifndef LEVEL1DIALOG_H
#define LEVEL1DIALOG_H

#include <QDialog>

namespace Ui {
class Level1Dialog;
}

class Level1Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Level1Dialog(QWidget *parent = nullptr);
    ~Level1Dialog();

private slots:
    void on_pushButtonOk_clicked();
signals:
    void Closed();

private:
    Ui::Level1Dialog *ui;
};

#endif // LEVEL1DIALOG_H
