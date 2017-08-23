#include "widget.h"
#include "ui_widget.h"
#include <windows.h>
#include "plane.h"
#include "enemy.h"
#include "bullet.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <QMessageBox>

plane Plane;
enemy Enemy;
bullet Bullet;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //禁用大小调整
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    //加载图片
    loadPictures();
    //加载声音
    sound = new QSound(""/*"res/music.wav"*/, this);
    sound->play();
    soundState = 1;
    //加载label响应动作
    ui->start_label->installEventFilter(this);
    ui->exit_label->installEventFilter(this);
    ui->sound_label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadPictures()
{
    backgroundImg = new QImage;
    startImg = new QImage;
    exitImg = new QImage;
    gameImg1 = new QImage;
    gameImg2 = new QImage;
    pauseImg = new QImage;
    sndoffImg = new QImage;
    sndonImg = new QImage;
    backgroundImg->load("res/background.png");
    ui->background_label->setPixmap(QPixmap::fromImage(*backgroundImg));
    gameImg1->load("res/shoot_copyright.png");
    ui->title_label_1->setPixmap(QPixmap::fromImage(*gameImg1));
    gameImg2->load("res/gameload.png");
    ui->title_label_2->setPixmap(QPixmap::fromImage(*gameImg2));
    startImg->load("res/startgame.png");
    ui->start_label->setPixmap(QPixmap::fromImage(*startImg));
    exitImg->load("res/exitgame.png");
    ui->exit_label->setPixmap(QPixmap::fromImage(*exitImg));
    pauseImg->load("res/pausegame.png");
    sndonImg->load("res/sndstart.png");
    sndoffImg->load("res/sndpause.png");
    ui->sound_label->setPixmap(QPixmap::fromImage(*sndoffImg));
}

void Widget::startGame()
{
    ui->background_label->clear();
    ui->title_label_1->clear();
    ui->title_label_2->clear();
    ui->start_label->clear();
    ui->exit_label->clear();
    play();
}

void Widget::exitGame()
{
    delete backgroundImg;
    delete startImg;
    delete exitImg;
    delete gameImg1;
    delete gameImg2;
    delete pauseImg;
    delete sndoffImg;
    delete sndonImg;
    delete sound;
    exit(0);
}

void Widget::pauseGame()
{
    pauseState = 1;
    ui->pause_label->setPixmap(QPixmap::fromImage(*pauseImg));
    MSG msg;
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else if (msg.message == WM_KEYDOWN)
            {
                unsigned key = msg.wParam;
                if(key == 27 || key == 'P')
                    break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    ui->pause_label->clear();
    pauseState = 0;
    return;
}

void Widget::returnMainpage()
{
    ui->background_label->setPixmap(QPixmap::fromImage(*backgroundImg));
    ui->title_label_1->setPixmap(QPixmap::fromImage(*gameImg1));
    ui->title_label_2->setPixmap(QPixmap::fromImage(*gameImg2));
    ui->start_label->setPixmap(QPixmap::fromImage(*startImg));
    ui->exit_label->setPixmap(QPixmap::fromImage(*exitImg));
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->exit_label && event->type() == QEvent::MouseButtonPress)
        exitGame();
    else if(obj == ui->start_label && event->type() == QEvent::MouseButtonPress)
        startGame();
    else if(obj == ui->sound_label && event->type() == QEvent::MouseButtonPress)
    {
        if(soundState == 1)
        {
            sound->stop();
            ui->sound_label->clear();
            ui->sound_label->setPixmap(QPixmap::fromImage(*sndonImg));
        }
        else
        {
            sound->play();
            ui->sound_label->clear();
            ui->sound_label->setPixmap(QPixmap::fromImage(*sndoffImg));
        }
        soundState = !soundState;
    }
    return QWidget::eventFilter(obj, event);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(this->backgroundImg == NULL) return;
    painter.drawPixmap(0,0,this->backgroundImg->width(), this->backgroundImg->height(), QPixmap::fromImage(*backgroundImg));
    if(this->HeroLoc == NULL || this->Hero == NULL) return;
    painter.drawPixmap(this->HeroLoc->x(),this->HeroLoc->y(),
                       this->HeroLoc->width(),this->HeroLoc->height(), *this->Hero);
    if(this->EnemyGraph == NULL) return;
    Eair *eh = this->EnemyHead;
    while(eh != NULL)
    {
        painter.drawPixmap(eh->rect.x(), eh->rect.y(), eh->rect.width(), eh->rect.height(), *this->EnemyGraph);
        eh = eh->next;
    }
    if(this->EnemyGraph == NULL) return;
    Bair *bh = this->BulletHead;
    while(bh != NULL)
    {
        painter.drawPixmap(bh->rect.x(), bh->rect.y(), bh->rect.width(), bh->rect.height(), *this->BulletGraph);
        bh = bh->next;
    }
}


int GenerateTimerID, EnemyMoveTimerID, BulletMoveTimerID;
void Widget::play()
{
    repaint();
    Plane.init(400, 800);
    Enemy.init();
    Bullet.init();
    this->BulletGraph = Bullet.BulletGraph;
    this->EnemyGraph = Enemy.EnemyGraph;
    this->HeroLoc = Plane.MyLoc;
    this->Hero = Plane.MyPlane;
    GenerateTimerID = startTimer(1500);
    EnemyMoveTimerID = startTimer(500);
    BulletMoveTimerID = startTimer(2);
    MSG msg;
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else if (msg.message == WM_KEYDOWN)
            {
                unsigned key = msg.wParam;
                if(key == 27)
                    break;
                switch (key) {
                case 'A':
                case 'W':
                case 'D':
                case 'S':Plane.move(key);
                         break;
                case 'H':this->BulletHead = Bullet.head = Bullet.add(Plane.MyLoc->x() + (100 + 5 / 2) / 2, Plane.MyLoc->y() - 11, 1);
                         break;
                case 'P':pauseGame();
                         break;
                default: break;
                }
            }
            update();
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if(0 == Enemy.check(Plane.MyLoc->x(), Plane.MyLoc->y()))
        {
            this->Hero = NULL;
            this->HeroLoc = NULL;
            Plane.destroyed();
            while(Enemy.count > 0)
                Enemy.destroyed(0);
            this->EnemyHead = NULL;
            break;
        }
        for (int i = 0; i < Enemy.count; ++i)
        {
            int x = Enemy.getinfo(i, 0);
            int y = Enemy.getinfo(i, 1);
            if (x != -1 && 0 == Bullet.check(x, y, 0))
            {
                this->EnemyHead = Enemy.head = Enemy.destroyed(i);
                --i;
                Plane.score++;
            }
        }
        if(Enemy.GG) break;
        update();
    }
    killTimer(GenerateTimerID);
    killTimer(EnemyMoveTimerID);
    killTimer(BulletMoveTimerID);
    char gameInfo[20];
    sprintf(gameInfo, "*你的分数是%d*\n*最高关卡是%d*", Plane.score, Plane.level);
    QString buffer(gameInfo);
    QMessageBox::information(this, "游戏结束", buffer);
    returnMainpage();
}

void Widget::timerEvent(QTimerEvent *t)
{
    if(pauseState) return;
    srand(time(0));
    if(t->timerId() == GenerateTimerID)
    {
        this->EnemyHead = Enemy.head = Enemy.create((rand() % 9) * 50 + 25);
    }
    else if(t->timerId() == EnemyMoveTimerID)
    {
        this->EnemyHead = Enemy.head = Enemy.move();
    }
    else if(t->timerId() == BulletMoveTimerID)
    {
        this->BulletHead = Bullet.head = Bullet.move();
    }
    update();
}

