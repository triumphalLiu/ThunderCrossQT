#include "enemy.h"

Eair *enemy::create(int x)
{
    int y = 50;
    Eair *p = new Eair;
    p->rect.setX(x);
    p->rect.setY(y);
    p->rect.setWidth(50);
    p->rect.setHeight(50);
    p->next = NULL;
    if (head == NULL)
        head = p;
    else
    {
        p->next = head;
        head = p;
    }
    ++enemy::count;
    return head;
}

Eair *enemy::move()
{
    Eair *p = head;
    int  i = 0;
    while (p != NULL)
    {
        p->rect.setY(p->rect.y() + SizeEnemy/2);
        p->rect.setWidth(SizeEnemy);
        p->rect.setHeight(SizeEnemy);
        Eair *nxt = p->next;
        if (p->rect.y() > (SizeGameY - SizeHero))
        {
            head = enemy::destroyed(i);
            i--;
            GG = 1;
        }
        p = nxt;
        ++i;
    }
    return head;
}

int enemy::getinfo(int i, int option)
{
    Eair *p = enemy::head;
    for (int j = 0; j < i && p != NULL; ++j)
        p = p->next;
    if (p == NULL)
        return -1;
    else
        return (option == 0) ? p->rect.x() : p->rect.y();
}

Eair *enemy::destroyed(int i)
{
    --enemy::count;
    Eair *p = enemy::head;
    if (i == 0)
    {
        enemy::head = p->next;
        free(p);
        return enemy::head;
    }
    for (int j = 0; j < i - 1; ++j)
        p = p->next;
    Eair *del = p->next;
    p->next = del->next;
    free(del);
    return enemy::head;
}

int enemy::check(int x, int y)
{
    Eair *p = head;
    while (p != NULL)
    {
        if (p->rect.y() >= (SizeGameY - SizeHero) || (p->rect.x() > x && p->rect.x() < x + SizeHero &&
            p->rect.y() + SizeEnemy > y && p->rect.y() + SizeEnemy < y + SizeHero))
            return 0;
        p = p->next;
    }
    return 1;
}

void enemy::init()
{
    head = NULL;
    count = 0;
    EnemyGraph = new QPixmap;
    EnemyGraph->load("res/enemy.png");
    GG = 0;
}

enemy::enemy()
{

}

enemy::~enemy()
{

}
