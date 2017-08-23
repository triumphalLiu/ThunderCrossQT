#ifndef ENEMY_H
#define ENEMY_H
#include "common.h"
#include <QPixmap>

class enemy
{
public:
    enemy();
    ~enemy();
    bool GG;
    int count;
    Eair *create(int);
    Eair *move();
    Eair *destroyed(int);
    Eair *head;
    void init();
    int check(int x, int y);
    int getinfo(int, int);
    QPixmap *EnemyGraph;

private:

};
#endif // ENEMY_H
