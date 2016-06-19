#ifndef MAGICBIRD_H
#define MAGICBIRD_H

#include <bird.h>
#include <QTimer>

class magicbird : public Bird
{
    Q_OBJECT

public:
    magicbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void superpower();

    QTimer tri_up;
    int safe;

private slots:
    void magic();
};

#endif // MAGICBIRD_H
