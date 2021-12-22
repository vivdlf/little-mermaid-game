#include "game.h"
#include <QTimer>
#include <QMediaPlayer>


Game::Game(QWidget *parent)
{
        // Create the scene by initializing our scene data member
        scene = new QGraphicsScene();
        scene->setSceneRect(0,0,800,600); // Make the scene 800x600 instead of infinity by infinity (default)
        setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

        // Make the newly created scene the scene to visualize (since Game inherits from QGraphicsView Widget,
        // It can be used to visualize scenes)
        setScene(scene); // Visualize the scene by adding it to the view.
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedSize(800,600);

        // Create the player
        player = new Player();
        // player->0,0,100,100); // Change the rect from 0x0 (default) to 100x100 pixels

        player->setPos(400,500); // Generalize to always be in the middle bottom of screen

        // Make the player focusable and set it to be the current focus
        player->setFlag(QGraphicsItem::ItemIsFocusable);
        player->setFocus();
        // Add the player to the scene
        scene->addItem(player);

        // Create the score/health
        score = new Score();
        scene->addItem(score);
        health = new Health();
        health->setPos(health->x(),health->y()+25);
        scene->addItem(health);


        // Spawn enemies
        timer = new QTimer();
        QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
        timer->start(2000);

        // Play background music
        music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
        music->play();

        // Show the view
        show();
}
