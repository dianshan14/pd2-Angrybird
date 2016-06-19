#ifndef PUSH_H
#define PUSH_H

#include <QObject>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsView>

class push : public QPushButton
{
    Q_OBJECT
public:
    push();
    bool eventFilter(QObject *,QEvent *event);
    QPushButton * btn_exit;
};

#endif // PUSH_H
