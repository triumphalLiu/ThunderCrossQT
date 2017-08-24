#ifndef BULLET_H
#define BULLET_H
#include "common.h"
#include <QPixmap>
class bullet
{
public:
    bullet();
    ~bullet();
    int count;
    void init();
    bool check(int, int, int);
    Bair *head;
    Bair *add(int, int, int);
    Bair *move();
    Bair *del(Bair *);
    QPixmap *BulletGraph;
    QPixmap *BulletEnemyGraph;
private:

};

#endif // BULLET_H
