#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"
#include "score.h"
#include "health.h"


class Game : public QGraphicsView
{
public:
    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    QMediaPlayer * music; // ** my changes
    QTimer * timer; // ** my changes
   };

#endif // GAME_H
