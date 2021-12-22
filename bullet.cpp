#include "bullet.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemy.h"
#include "game.h"

extern Game * game;
Bullet::Bullet()
{
    // Building the bullet
    // setRect( 0, 0, 10, 15);
    //qDebug()<<"Bullet got created.";

    // Draw graphics
    setPixmap(QPixmap(":/images/bullet.png"));

    // Connecting QTimer to the bullet
    QTimer *timer = new QTimer();
    connect( timer, SIGNAL( timeout() ), this, SLOT( move() ) );
    timer->start(50);// Emits timeout() signal every 50 milliseconds
}

void Bullet::move()
{
    // If bullet collides with enemy, destroy both
    QList<QGraphicsItem *> colliding_items_list = collidingItems();
    int listCount = colliding_items_list.size();

    for(int i = 0; i < listCount; i++)
    {
        if( typeid(* (colliding_items_list[i]) ) == typeid(Enemy) )
        {
            // Increase the score
            game->score->increase();

            // Remove them both
            scene()->removeItem( colliding_items_list[i] ); // Remove current enemy
            scene()->removeItem(this);// Remove the current bullet

            // Release memory for removed bullet and enemy
            delete colliding_items_list[i];
            delete this;
            return;// Once a bullet is removed and destroyed, leave the function to prevent code from moving bullet below
        }
    }// End for

    // Move bullet up
    setPos(x(),y()-10);

    // Deleting bullets that have gone out of scene
    if( ( pos().y() + pixmap().height() )< 0 )
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Bullet deleted.";
    }

}
