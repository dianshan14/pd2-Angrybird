#ifndef MASTER_H
#define MASTER_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>


#define MASTER_DENSITY 10.0f
#define MASTER_FRICTION 0.2f
#define MASTER_RESTITUTION 0.5f

class master : public GameItem
{
public:
    master(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // MASTER_H
