#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <cmath>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <cstdlib>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <barrier.h>
#include <speedbird.h>
#include <multibird.h>
#include <magicbird.h>
#include <master.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void QUITSLOT(bool);
    void generateBird();
    void getItemPos();
    void deleteItem();
    void finally();
    //void restart();
private:
    Ui::MainWindow *ui;
    QGraphicsView * view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem * back , *shot ;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;

    double aa,bb,cc,dd,ee,ff;
    //double line_x , line_y;
    b2Vec2 po;
    int bird_mode ,superPower_mode;
    bool isMouseControl , isLineAppear , isButtonControl , isExist[17] , canDelete , isResultOpen;
    QTimer gen_bird , get_bird , ge_bird , start , item , delete_timer , finalCheck;
    QPushButton *btn_exit ;
    //QPixmap line_pic;
    QLabel * score_label;
    int score , score2;
    double item_x[13] , item_y[13] , item_r[13];
    QString lab , lab2;
    QGraphicsPixmapItem *result;
    //Bird * now_bird;
};

#endif // MAINWINDOW_H
