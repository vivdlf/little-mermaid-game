#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <cstdlib>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
using std::srand;
using std::rand;

#include "game.h"
#include "player.h"

extern Game * game;
Enemy::Enemy(): QObject(), QGraphicsPixmapItem()
{
    // 700 ensures enemies are created within our screen’s 800 width because the rand num will be a value
    // in the range of 0 and 699.  However, we must take into account that the width of the enemy is 100
    int random_x = rand() % 700;
    setPos(random_x, 0);

    // Draw Enemy rect the same size as our player rect
    //setRect(0,0, 100, 100);

    // Draw the rect/image
    setPixmap(QPixmap(":/images/enemy.png"));

    //    setTransformOriginPoint(50,50);
    //    setRotation(180);

    QTimer * timer = new QTimer(this);

    // Connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move() ) );

    timer->start(50);// Repeat countdown clock to emit timeout() signal every 50 milliseconds
}
void Enemy::move()
{
    setPos( x(), y() + 5);// Enemy is moving down so we increase the y value.  We increase by 5 to be slower than bullet

    if( pos().y()  > 600 )
    {
        //decrease the health
        game->health->decrease();

        if( game->health->getHealth() == 0 )
        {
            // Stop the spawning of enemies
            game->timer->stop();

            // Stop music
            game->music->stop();

            // Play game over background music
            QMediaPlayer * music = new QMediaPlayer();
            music->setMedia(QUrl("qrc:/sounds/gameover.wav"));
            music->play();

            // Ask user if they want to replay or quit
            QMessageBox messageBox(QMessageBox::Question, "Game Over!", QString("Oops! You've lost.\n Score: ")+ QString::number(game->score->getScore()),
                                   QMessageBox::NoButton, 0);

            // Creating our own custom buttons
            messageBox.addButton(new QPushButton("Replay", 0), QMessageBox::AcceptRole);
            messageBox.addButton(new QPushButton("Exit", 0), QMessageBox::RejectRole);

            // If they want to play again then restart
            if( messageBox.exec() == QMessageBox::AcceptRole )
            {
                // Start music from begining
                game->music->setPosition(0);
                game->music->play();

                // Setting player in focus once again
                game->player->setFocus();
                // Set score to 0 and health to 3

                game->score->setScore();
                game->health->setHealth();

                // Begin spawning enemies again
                game->timer->start();
            }
            else
                QApplication::quit(); // If they don't want to play again close the program
        }
        scene()->removeItem(this);
        delete this;
        //qDebug()<<"Enemy deleted.";
    }
}

