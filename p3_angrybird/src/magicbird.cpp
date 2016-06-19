#include "magicbird.h"

magicbird::magicbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    safe = 0;
}

void magicbird::superpower()
{
    connect(&tri_up,SIGNAL(timeout()),this,SLOT(magic()));
    tri_up.start(700);
}



void magicbird::magic()
{
    if(safe<3)
    {
        int tmp;
        safe++;
        b2Vec2 vel = this->g_body->GetLinearVelocity();
        if(vel.x<25)
            tmp = 25;
        else
            tmp = vel.x;
        this->g_body->SetLinearVelocity(b2Vec2((tmp>0?2*tmp:-2*tmp),(vel.y>0?vel.y:-vel.y)));
    }
    else
    {
        tri_up.stop();
    }
}
