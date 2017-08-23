#ifndef ENEMY_H
#define ENEMY_H
#include "common.h"
#include <QPixmap>

class enemy
{
public:
    enemy();
    ~enemy();
    void init();
    Eair *head;
    int count;
    int getinfo(int, int);
    Eair *create(int);
    Eair *destroyed(int);
    Eair *move();
    int check(int x, int y);
    QPixmap *EnemyGraph;
private:

};
#endif // ENEMY_H
