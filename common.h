#ifndef COMMON_H
#define COMMON_H

#include <QRect>

#define SizeGameX 500
#define SizeGameY 900
#define SizeHero 100
#define SizeBulletX 5
#define SizeBulletY 11
#define SizeEnemy 50

struct Eair {
    QRect rect;
    Eair *next;
};

struct Bair {
    QRect rect;
    int flag;
    Bair *next;
};

#endif // COMMON_H
