#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "bullet.h"
#include <QGraphicsScene>
#include "enemy.h"


void Player::keyPressEvent(QKeyEvent *event)
{
    //qDebug()<<"MyRect knows that you pressed a key.";
    if( event->key() == Qt::Key_Left )
    {
        if( pos().x() > 0 )
            setPos( x() - 10, y() );
    }
    else if( event->key() == Qt::Key_Right )
    {
        if( pos().x() + 100 < 800 )
            setPos( x() + 10, y() );
    }
    /*
    else if( event->key() == Qt::Key_Up )
        setPos( x(), y() - 10 );
    else if( event->key() == Qt::Key_Down )
        setPos( x(), y() + 10 );
    */
    else if( event->key() == Qt::Key_Space )
    {
        Bullet * bullet = new Bullet();
        bullet->setPos( x(), y() );
        scene()->addItem( bullet );

        // play bulletsound
        if (bulletsound->state() == QMediaPlayer::PlayingState)
        {
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState)
        {
            bulletsound->play();
        }
    }
}

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/bullet.wav"));

    // Set graphic
    setPixmap( QPixmap(":/images/player.png") );
}

void Player::spawn()
{
    // Create a new Enemy
    Enemy *enemy = new Enemy();

    // Add newly created enemy to the same scene as the player
    scene()->addItem(enemy);
}
