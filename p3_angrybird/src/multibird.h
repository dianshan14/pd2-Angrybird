#ifndef MULTIBIRD_H
#define MULTIBIRD_H

#include <bird.h>
#include <QTimer>
#include <QObject>

class multibird : public Bird
{
    Q_OBJECT
public:
    multibird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void superpower();
    QTimer disappear;
    Bird * speed , *up;
private slots:
    void dis();

};

#endif // MULTIBIRD_H
