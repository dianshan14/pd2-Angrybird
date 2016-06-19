#ifndef SPEEDBIRD_H
#define SPEEDBIRD_H

#include <bird.h>
#include <QTimer>

class speedBird : public Bird
{
public:
    speedBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void superpower();
};

#endif // SPEEDBIRD_H
