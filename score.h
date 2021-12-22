#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score( QGraphicsItem * parent = 0);
    void increase();
    int getScore();
    void setScore(); // Carries no parameter because score will always be set to 0 in the case of a replay
private:
    int score;
};

#endif // SCORE_H
