#include "master.h"

master::master(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody; //設定為動態物體
    bodydef.bullet = true; //避免動態物體穿越
    bodydef.position.Set(x,y);
    bodydef.userData = this; //Use this to store application specific body data.//除了物理量的其他東西都存這
    g_body = world->CreateBody(&bodydef); /************************************/
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef; //創造一個有實體形狀的東西(fixture)
    fixturedef.shape = &bodyshape;
    fixturedef.density = MASTER_DENSITY; //密度
    fixturedef.friction = MASTER_FRICTION; //摩擦係數
    fixturedef.restitution = MASTER_RESTITUTION; //恢復係數 0.5=非彈性碰撞
    g_body->SetAngularDamping(3); //設定碰撞到之後的旋轉阻力
    g_body->CreateFixture(&fixturedef);/*********************/
    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

