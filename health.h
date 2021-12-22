#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
class Health : public QGraphicsTextItem
{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
    void setHealth(); // Carries no parameter because health will always be set to 3 in case of a replay
private:
    int health;
};

#endif // HEALTH_H
