#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    //qApp->installEventFilter(push);
    bird_mode = 13;
    superPower_mode = 0;
    isMouseControl = true;
    //isLineAppear = false;
    isButtonControl = true;
    canDelete = false;
    isResultOpen = false;
    score = 0;
    for(int i=0;i<14;++i)
    {
        isExist[i]=true;
    }
    for(int i=14;i<17;++i)
        isExist[i] = false;

    //line = new QGraphicsPixmapItem;
    //line_pic.load(":/image/line.png");
    //line_pic = line_pic.scaled(500,500);
    //line->setPixmap(line_pic);
    //line->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
  //  this->centralWidget()

    // Setting the QGraphicsScene
//    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
   // scene = new QGraphicsScene(0,0,width(),height());
//    ui->graphicsView->setScene(scene);

    view = new QGraphicsView(this);
    ui->centralWidget->layout()->addWidget(view);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene(0,0,this->centralWidget()->width(),this->centralWidget()->height());
    view->setScene(scene);
    // Create world
    //b2World ctor是 "重力" 向上為正 向下為負
    //b2Vec2:2D column vector
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    //設定世界大小，前為world 後為 window
    GameItem::setGlobalSize(QSizeF(32,18),size()); //32*18

    // Create ground (You can edit here)
    //land的座標 是32*18格式
    back = new QGraphicsPixmapItem;
    QPixmap barr(":/image/background.jpg");
    barr = barr.scaled((32/32.0)*1280,(18/18.0)*720);
    back->setPixmap(barr);
    scene->addItem(back);

    shot = new QGraphicsPixmapItem;
    QPixmap eye(":/image/slingshot.png");
    eye = eye.scaled((2/32.0)*1280,(3.5/18.0)*720);
    shot->setPos(120,470);
    shot->setPixmap(eye);
    scene->addItem(shot);

    //scene->addItem(line);

    itemList.push_back(new Land(16,1.5,16,1.1,QPixmap(":/ground.png").scaled((32/32.0)*1280,(2.2/18.0)*720),world,scene));
    itemList.push_back(new barrier(18,7.5,0.4,2.5,&timer,QPixmap(":/image/barrier1v.png").scaled((0.8/32.0)*1280,(5/18.0)*720),world,scene));
    itemList.push_back(new barrier(26,7.5,0.4,2.5,&timer,QPixmap(":/image/barrier1v.png").scaled((0.8/32.0)*1280,(5/18.0)*720),world,scene));
    itemList.push_back(new barrier(22,10.5,4.5,0.4,&timer,QPixmap(":/image/barrier1.png").scaled((9/32.0)*1280,(0.8/18.0)*720),world,scene));
    itemList.push_back(new barrier(19,13,0.4,2.0,&timer,QPixmap(":/image/barrier2v.png").scaled((0.8/32.0)*1280,(4/18.0)*720),world,scene));
    itemList.push_back(new barrier(25,13,0.4,2.0,&timer,QPixmap(":/image/barrier2v.png").scaled((0.8/32.0)*1280,(4/18.0)*720),world,scene));
    itemList.push_back(new barrier(22,15,3.5,0.4,&timer,QPixmap(":/image/barrier2.png").scaled((7/32.0)*1280,(0.8/18.0)*720),world,scene));
    itemList.push_back(new barrier(20.5,17,0.3,1.5,&timer,QPixmap(":/image/barrier3v.png").scaled((0.6/32.0)*1280,(3/18.0)*720),world,scene));
    itemList.push_back(new barrier(23.5,17,0.3,1.5,&timer,QPixmap(":/image/barrier3v.png").scaled((0.6/32.0)*1280,(3/18.0)*720),world,scene));
    itemList.push_back(new barrier(22,19,2.0,0.3,&timer,QPixmap(":/image/barrier3.png").scaled((4/32.0)*1280,(0.6/18.0)*720),world,scene));
    itemList.push_back(new master(22,5.0,1.2,&timer,QPixmap(":/image/pig7.png").scaled((2.4/32.0)*1280,(2.4/18.0)*720),world,scene));
    itemList.push_back(new master(22,12.0,1.0,&timer,QPixmap(":/image/pig2.png").scaled((2/32.0)*1280,(2/18.0)*720),world,scene));
    itemList.push_back(new master(22,17.0,1.0,&timer,QPixmap(":/image/pig6.png").scaled((2/32.0)*1280,(2/18.0)*720),world,scene));

    itemList.push_back(new Bird(4.0f,6.0f,0.6f,&timer,QPixmap(":/bird.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene));
    itemList[bird_mode]->g_body->SetAwake(false);

    btn_exit = new QPushButton;
    btn_exit->setStyleSheet("border-image:url(:/image/exit.png)");
    btn_exit->setParent(view);
    btn_exit->setGeometry(0,0,100,100);

    lab = "Score : ";
    lab2 = lab + QString::number(score);
    score_label = new QLabel(this);
    score_label->setText(lab2);
    score_label->setFont(QFont("Courier",24,QFont::Black));
    score_label->setGeometry(965,0,500,100);
    //score_label->setParent(view);
    score_label->show();

    //btn_re = new QPushButton;
    //btn_re->setStyleSheet("border-image:url(:/image/retry.png)");
    //btn_re->setParent(view);
    //btn_re->setGeometry(0,100,100,100);

    connect(&item,SIGNAL(timeout()),this,SLOT(getItemPos()));
    item.start(1000);

    // Timer
    connect(&delete_timer,SIGNAL(timeout()),this,SLOT(deleteItem()));
    delete_timer.start(100/6);
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6); //1000(ms)/60 = 100/6
    //cout << "count : " << itemList.count() << endl;
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        //cout << "fukc" << mouseEvent->x() << " " << mouseEvent->y() << endl;
        if(((mouseEvent->x()<=100) && (mouseEvent->x()>=0)) && ((mouseEvent->y()>=0) && (mouseEvent->y()<=100)))
        {
            QTimer *aaaaa=new QTimer;
            aaaaa->start(1);
            connect(aaaaa,SIGNAL(timeout()),this,SLOT(close()));
            return true;
        }
        /*else if(((mouseEvent->x()<=100) && (mouseEvent->x()>=0)) && ((mouseEvent->y()>=101) && (mouseEvent->y()<=200)))
        {
            cout << "I got it!!!" << endl;
            isButtonControl = true;
            connect(&start,SIGNAL(timeout()),this,SLOT(restart()));
            start.start(500);
            return true;
        }*/
        if(((itemList.count()-1) == bird_mode) && (superPower_mode == 0))
        {
            if(!isMouseControl)
                return true;
            //po = itemList[4]->g_body->GetWorldCenter();
            po = itemList[bird_mode]->g_body->GetPosition();
           // po = itemList[bird_mode]->g_body->GetPosition();
            //cout << po.x << " -- " << po.y << endl;
            //line_x=mouseEvent->x();
            //line_y=mouseEvent->y();
            aa = mouseEvent->globalX();
            bb = mouseEvent->globalY();
            cc = pow(pow(aa,2)+pow(bb,2),0.5);
            //cout << aa << " " << bb << endl;
            //cout << "cc : " << cc << endl;
            //itemList[4]->g_body->SetTransform(b2Vec2(10,10),0);
            itemList[bird_mode]->g_body->SetAwake(false);
            //itemList[4]->g_body->SetTransform(b2Vec2(po.x+5,po.y+5),0);
            //cout << "1" << endl;
            //isLineAppear = true;
            //isButtonControl = false;
            //line->setPos(line_x,line_y);
            //cout << "X YYYYYY " << line_x << " " << line_y << endl;
            //line->show();

            return true;
        }
        else if(((itemList.count()-1) == bird_mode) && (superPower_mode == 1))
        {
            //cout << "2" << endl;
            if(bird_mode == 13) //第一支紅鳥
            {
                static_cast<Bird *>(itemList[bird_mode])->superpower();
                superPower_mode = 0;
                return true;
            }
            else if(bird_mode == 14)
            {
                static_cast<speedBird *>(itemList[bird_mode])->superpower();
                superPower_mode = 0;
                return true;
            }
            else if(bird_mode == 15)
            {
                static_cast<multibird *>(itemList[bird_mode])->superpower();
                superPower_mode = 0;
                //cout << "mode 6" << endl;
                return true;
            }
            else if(bird_mode == 16)
            {
                static_cast<magicbird *>(itemList[bird_mode])->superpower();
                superPower_mode = 0;
                //cout << "mode 7" << endl;
                connect(&finalCheck,SIGNAL(timeout()),this,SLOT(finally()));
                finalCheck.start(6000);
                return true;
            }

        }
        else
        {
            //cout << "BUG IN　PRESS" << endl;
            return true;
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        //if((!isLineAppear) && (!isMouseControl))
        //    return true;

        //line_pic = line_pic.scaled(1000,1000);
        //line->setPos(120,470);

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(((itemList.count()-1) == bird_mode) && (superPower_mode == 0) )
        {
            if(!isMouseControl)
                return true;
            //else if(isButtonControl && (bird_mode==13))
            //    return true;
            //line->hide();
            itemList[bird_mode]->g_body->SetLinearVelocity(b2Vec2(0.0,0.0));
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            //int aa=mouseEvent->x();
            //int bb=mouseEvent->y();
            dd = mouseEvent->globalX();
            ee = mouseEvent->globalY();
            ff = pow(pow(dd,2)+pow(ee,2),0.5);
            //cout <<  "F : "  << ff << endl;
            double resu=abs(ff-cc);
            //cout << "resu: " << resu << endl;
            if(resu>25)
                resu = 25;
            if((aa-dd)>5)
                ff = -atan((bb-ee)/(aa-dd));
            else
                ff = -atan((bb-ee)/(aa-dd+5));
            //cout << "ff : " << ff << endl;
            itemList[bird_mode]->g_body->SetTransform(po,ff);
            itemList[bird_mode]->g_body->SetLinearVelocity(b2Vec2(resu*cos(ff),resu*sin(ff)));
            itemList[bird_mode]->g_body->SetAwake(true);
            {
                //cout << "bird ? " << bird_mode << endl;
                if(bird_mode == 13) //第一支紅鳥
                {                    //需要再timer後面+ ?
                    connect(&gen_bird,SIGNAL(timeout()),this,SLOT(generateBird()));
                    gen_bird.start(3000);
                }
                else if(bird_mode == 14)
                {
                    connect(&ge_bird,SIGNAL(timeout()),this,SLOT(generateBird()));
                    ge_bird.start(3000);
                    //cout << "emode 6" << endl;
                }
                else if(bird_mode == 15)
                {
                    connect(&get_bird,SIGNAL(timeout()),this,SLOT(generateBird()));
                    get_bird.start(3000);
                    //cout << "emode 7" << endl;
                }
                //else if(bird_mode == 7)
                //{
                //    connect(&gen_bird,SIGNAL(timeout()),this,SLOT(generateBird()));
                //    gen_bird.start(3000);
                //    cout << "emode 8" << endl;
                //}
            }
            //cout << "3" << endl;
            superPower_mode = 1;
            isMouseControl = false;
            //isLineAppear = false;
            return true;
        }
        else
        {
            //itemList.pop_front();
                        //cout << itemList.count() << " I an count!" << endl;
            //cout << "BUG IN RELEASE" << endl;
            return true;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,10); //再了解  >> 更新box2D 每1/60秒更新一次 每次的速度要更新六次 每次的位置要更新兩次
    scene->update(); //更新Qt
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::QUITSLOT(bool)
{
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::generateBird()
{
    if(bird_mode == 13)
    {
        gen_bird.stop();
        delete itemList[bird_mode];
        isExist[bird_mode] = false ; //13
        ++bird_mode;
        itemList.push_back(new speedBird(4.0f,6.0f,0.6f,&timer,QPixmap(":/image/8.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene));
        itemList[bird_mode]->g_body->SetBullet(false);
        itemList[bird_mode]->g_body->SetAwake(false);
        superPower_mode = 0;
        isMouseControl = true;
        isExist[bird_mode] = true; //14
        //cout << " de bug : " << bird_mode << endl;
    }
    else if(bird_mode == 14)
    {
        ge_bird.stop();
        delete itemList[bird_mode];
        isExist[bird_mode] = false ; //14
        ++bird_mode;
        itemList.push_back(new multibird(4.0f,6.0f,0.6f,&timer,QPixmap(":/image/9.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene));
        itemList[bird_mode]->g_body->SetBullet(false); //?
        itemList[bird_mode]->g_body->SetAwake(false);
        superPower_mode = 0;
        isMouseControl = true;
        isExist[bird_mode] = true; //15
        //cout << "genmode 6" << endl;
    }
    else if(bird_mode == 15)
    {
        get_bird.stop();
        delete itemList[bird_mode];
        isExist[bird_mode] = false ; //15
        ++bird_mode;
        itemList.push_back(new magicbird(4.0f,6.0f,0.6f,&timer,QPixmap(":/image/10.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene));
        itemList[bird_mode]->g_body->SetBullet(false); //?
        itemList[bird_mode]->g_body->SetAwake(false);
        superPower_mode = 0;
        isMouseControl = true;
        isExist[bird_mode] = true; //16
        //cout << "genmode 7" << bird_mode << endl;
    }
}

void MainWindow::getItemPos()
{
    item.stop();
    for(int i=0;i<13;++i)
    {
        item_x[i]=pow(itemList[i]->g_body->GetPosition().x,2);
        item_y[i]=pow(itemList[i]->g_body->GetPosition().y,2);
        //cout << "POS BUG " << "x= " << item_x[i] << " y= " << item_y[i] << endl;
        item_r[i]=pow(item_x[i]+item_y[i],0.5);

            //cout << " DEBUG : " << i << " -> " << item_r[i] << endl;
    }
    canDelete = true;
}

void MainWindow::deleteItem()
{
    if(!canDelete)
        return;

    lab2 = lab + QString::number(score);
    score_label->setText(lab2);
    //cout << "1" << endl;
    score_label->hide();
    score_label->show();
    for(int i=0;i<10;++i)
    {
        item_x[i]=pow(itemList[i]->g_body->GetPosition().x,2);
        item_y[i]=pow(itemList[i]->g_body->GetPosition().y,2);
        if((abs(item_r[i]-pow(item_x[i]+item_y[i],0.5))>=4) && isExist[i])
        {
            score = score + (rand()%2000+1000);
            isExist[i] = false;
            delete itemList[i];
        }
    }
    for(int i=10;i<13;++i)
    {
        item_x[i]=pow(itemList[i]->g_body->GetPosition().x,2);
        item_y[i]=pow(itemList[i]->g_body->GetPosition().y,2);
        if((abs(item_r[i]-pow(item_x[i]+item_y[i],0.5))>=7) && isExist[i])
        {
            score = score + (rand()%5000+10000);
            isExist[i] = false;
            delete itemList[i];
        }
    }
}

void MainWindow::finally()
{
    finalCheck.stop();
    if((score>=12000))
    {
        result = new QGraphicsPixmapItem;
        QPixmap barr(":/image/win.png");
        barr = barr.scaled((8/32.0)*1280,(5/18.0)*720);
        result->setPixmap(barr);
        result->setPos(300,300);
        scene->addItem(result);
    }
    else
    {
        result = new QGraphicsPixmapItem;
        QPixmap barr(":/image/lose.png");
        barr = barr.scaled((8/32.0)*1280,(5/18.0)*720);
        result->setPixmap(barr);
        result->setPos(200,200);
        scene->addItem(result);
    }
}

/*void MainWindow::restart()
{
    start.stop();
    for(int i=0;i<14;++i)
    {
        if(isExist[i])
        {
            //cout << i << "ok" << endl;
            if(itemList.empty())
                cout << "EMPTY!" << endl;
            else
            {
                //world->DestroyBody(itemList[i]->g_body);
                cout << itemList.count() << " WORLD " << endl;
                delete itemList[i];
                //itemList.pop_front();
                //world->DestroyBody(itemList[i]->g_body);
            //itemList[i] = 0;
            }
        }
    }
    cout << "Count in final :" << itemList.count() << endl;
    bird_mode = 13;
    superPower_mode = 0;
    isMouseControl = true;
    isLineAppear = false;
    isButtonControl = true;

    for(int i=0;i<17;++i)
    {
        isExist[i]=true;
       // itemList.removeFirst(); 從這裡開始 要把Qlist用成空的 ?
    }
    itemList.push_front(new Land(16,1.5,16,1.1,QPixmap(":/ground.png").scaled((32/32.0)*1280,(2.2/18.0)*720),world,scene));
   // itemList.push_back(new barrier(16,6,1,3,&timer,QPixmap(":/ground.png").scaled(width()*20.0/334.0,height()*64/190.0),world,scene));
    itemList.push_front(new barrier(18,7.5,0.4,2.5,&timer,QPixmap(":/ground.png").scaled((0.8/32.0)*1280,(5/18.0)*720),world,scene));
    itemList.push_front(new barrier(26,7.5,0.4,2.5,&timer,QPixmap(":/ground.png").scaled((0.8/32.0)*1280,(5/18.0)*720),world,scene));
    itemList.push_front(new barrier(22,10.5,4.5,0.4,&timer,QPixmap(":/ground.png").scaled((9/32.0)*1280,(0.8/18.0)*720),world,scene));

    itemList.push_front(new barrier(19,13,0.4,2.0,&timer,QPixmap(":/ground.png").scaled((0.8/32.0)*1280,(4/18.0)*720),world,scene));
    itemList.push_front(new barrier(25,13,0.4,2.0,&timer,QPixmap(":/ground.png").scaled((0.8/32.0)*1280,(4/18.0)*720),world,scene));
    itemList.push_front(new barrier(22,15,3.5,0.4,&timer,QPixmap(":/ground.png").scaled((7/32.0)*1280,(0.8/18.0)*720),world,scene));
    itemList.push_front(new barrier(20.5,17,0.3,1.5,&timer,QPixmap(":/ground.png").scaled((0.6/32.0)*1280,(3/18.0)*720),world,scene));
    itemList.push_front(new barrier(23.5,17,0.3,1.5,&timer,QPixmap(":/ground.png").scaled((0.6/32.0)*1280,(3/18.0)*720),world,scene));
    itemList.push_front(new barrier(22,19,2.0,0.3,&timer,QPixmap(":/ground.png").scaled((4/32.0)*1280,(0.6/18.0)*720),world,scene));
    itemList.push_front(new master(22,5.0,1.2,&timer,QPixmap(":/image/pig7.png").scaled((2.4/32.0)*1280,(2.4/18.0)*720),world,scene));
    itemList.push_front(new master(22,12.0,1.0,&timer,QPixmap(":/image/pig2.png").scaled((2/32.0)*1280,(2/18.0)*720),world,scene));
    itemList.push_front(new master(22,17.0,1.0,&timer,QPixmap(":/image/pig6.png").scaled((2/32.0)*1280,(2/18.0)*720),world,scene));
    itemList.push_front(new Bird(4.0f,6.0f,0.6f,&timer,QPixmap(":/bird.png").scaled((1.2/32.0)*1280,(1.2/18.0)*720),world,scene));
    //itemList[bird_mode]->g_body->SetAwake(false);
}*/


/*
void b2World::Step	(	float32 	timeStep,
int32 	velocityIterations,
int32 	positionIterations
)
Take a time step. This performs collision detection, integration, and constraint solution.

Parameters:
timeStep	the amount of time to simulate, this should not vary.
velocityIterations	for the velocity constraint solver.
positionIterations	for the position constraint solver.
*/
