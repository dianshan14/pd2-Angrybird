#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
//#include <mainwindow.h>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void setLinearVelocity(b2Vec2 velocity);

    virtual void superpower(); //被繼承實作能力 繼承的要丟member initializer 給被繼承的做ctor
//ctor在創造鳥的時候 給座標 給半徑(旋轉用)
    float x;
    float y;
    float radius;
    QTimer * timer;
    QPixmap pixmap;
    b2World *world;
    QGraphicsScene *scene;
};

#endif // BIRD_H
