#include "speedbird.h"

speedBird::speedBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    ;
}

void speedBird::superpower()
{
    b2Vec2 vel = this->g_body->GetLinearVelocity();
    this->g_body->SetLinearVelocity(b2Vec2(2.5*vel.x,1.2*vel.y));
}

