#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>

namespace Ui {
class LogInScreen;
}

class LogInScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LogInScreen(QWidget *parent = nullptr);
    ~LogInScreen();

private:
    Ui::LogInScreen *ui;
};

#endif // LOGINSCREEN_H
