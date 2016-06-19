#include "multibird.h"

multibird::multibird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    ;
}

void multibird::superpower()
{
    b2Vec2 pos = this->g_body->GetPosition();
    b2Vec2 vel = this->g_body->GetLinearVelocity();
    this->setLinearVelocity(b2Vec2(1.5*vel.x,vel.y));
    speed = new multibird(pos.x,pos.y+1.7,0.6f,timer,QPixmap(":/image/9.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene);
    up =new multibird(pos.x,pos.y-1.7,0.6f,timer,QPixmap(":/image/9.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene);
    speed->setLinearVelocity(b2Vec2(1.5*vel.x,1.5*vel.y));
    up->setLinearVelocity(b2Vec2(1.5*vel.x,0.8*vel.y));
    connect(&disappear,SIGNAL(timeout()),this,SLOT(dis()));
    disappear.start(2000);
}


void multibird::dis()
{
    disappear.stop();
    delete speed;
    delete up;
}

