#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);

public slots:
    void paint();
    // TODO virtual void collide();

public:
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size; //某個物件的大小 例如:地板 鳥
    b2World *g_world; //所有item存在的world
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
