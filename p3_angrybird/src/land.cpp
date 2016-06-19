#include "land.h"

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    //g_pixmap.setPixmap(pixmap);
    g_size = QSizeF(2*w,2*h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef); //g_body放到world裡
    b2PolygonShape bodyBox; //設定物件的大小 (?待查)
    bodyBox.SetAsBox(w,h); //shape設成box(長方形)
    g_body->CreateFixture(&bodyBox,9.0f);//讓body跟shape做連結 //前面是shape 後面是 density (density會自動更新body的mass)

    scene->addItem(&g_pixmap); //加到scene裡面
    paint(); //只要做一次paint
}

/*b2Fixture* b2Body::CreateFixture	(	const b2Shape * 	shape, float32 	density )
Creates a fixture from a shape and attach it to this body. This is a convenience function. Use b2FixtureDef
if you need to set parameters like friction, restitution, user data, or filtering. If the density is non-zero,
this function automatically updates the mass of the body.

Parameters:
shape	the shape to be cloned.
density	the shape density (set to zero for static bodies).
Warning:
This function is locked during callbacks.
*/  //polygonShape繼承自shape

/*
void b2PolygonShape::SetAsBox	(	float32 	hx,
float32 	hy
)
Build vertices to represent an axis-aligned box.

Parameters:
hx	the half-width.
hy	the half-height.
*/
