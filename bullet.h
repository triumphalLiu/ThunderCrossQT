#ifndef BULLET_H
#define BULLET_H
#include "common.h"
#include <QPixmap>
class bullet
{
public:
    bullet();
    ~bullet();
    Bair *head;
    int count;
    void init();
    Bair *add(int, int, int);
    Bair *move();
    Bair *del(Bair *);
    bool check(int, int, int);
    QPixmap *BulletGraph;
private:

};

#endif // BULLET_H
