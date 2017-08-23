#include "plane.h"
#include <QImage>
#include <QPainter>
#include <cstdio>
#include <QDebug>
void plane::move(int key)
{
    switch (key)
    {
    case 87: if (MyLoc->y() > 100) MyLoc->setY(MyLoc->y() - 100); break; //up
    case 83: if (MyLoc->y() < 800) MyLoc->setY(MyLoc->y() + 100); break; //down
    case 65:  if (MyLoc->x() >= 50 ) MyLoc->setX(MyLoc->x() - 50); break; //left
    case 68: if (MyLoc->x() < 400) MyLoc->setX(MyLoc->x() + 50); break;//right
    }
    MyLoc->setWidth(100);
    MyLoc->setHeight(100);
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
    MyLoc->setWidth(100);
    MyLoc->setHeight(100);
    MyPlane->load("res/hero.png");
}

plane::plane()
{

}

plane::~plane()
{

}
