#include "barrier.h"

barrier::barrier(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(2*w,2*h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; //********之後決定設定哪一個
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef); //g_body放到world裡
    g_body->SetTransform(b2Vec2(x,y),3.14);
    b2PolygonShape bodyBox; //設定物件的大小 (?待查)
    bodyBox.SetAsBox(w,h); //shape設成box(長方形)
    b2FixtureDef fixturedef;
    fixturedef.shape= &bodyBox;
    fixturedef.density = BARRIER_DENSITY;
    fixturedef.friction = BARRIER_FRICTION;
    fixturedef.restitution = BARRIER_RESTITUTION;

    g_body->SetAngularDamping(5);
    g_body->CreateFixture(&fixturedef);//讓body跟shape做連結 //前面是shape 後面是 density (density會自動更新body的mass)

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap); //加到scene裡面
    //paint(); //只要做一次paint

}

