#include "plane.h"
#include <QImage>
#include <QPainter>
#include <cstdio>
#include <QDebug>
void plane::move(int key)
{
    switch (key)
    {
    case 87: if (MyLoc->y() > SizeHero) MyLoc->setY(MyLoc->y() - SizeHero); break; //up
    case 83: if (MyLoc->y() < (SizeGameY -  SizeHero)) MyLoc->setY(MyLoc->y() + SizeHero); break; //down
    case 65:  if (MyLoc->x() >= SizeEnemy ) MyLoc->setX(MyLoc->x() - SizeEnemy); break; //left
    case 68: if (MyLoc->x() < (SizeGameX -  SizeHero)) MyLoc->setX(MyLoc->x() + SizeEnemy); break;//right
    }
    MyLoc->setWidth(SizeHero);
    MyLoc->setHeight(SizeHero);
}

void plane::destroyed()
{
    delete MyLoc;
    delete MyPlane;
}

void plane::init(int X, int Y)
{
    level = 1;
    score = 0;
    MyLoc = new QRect;
    MyPlane = new QPixmap;
    MyLoc->setX(X);
    MyLoc->setY(Y);
    MyLoc->setWidth(SizeHero);
    MyLoc->setHeight(SizeHero);
    MyPlane->load("res/hero.png");
}

plane::plane()
{

}

plane::~plane()
{

}
