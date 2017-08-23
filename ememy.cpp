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
        p->rect.setY(p->rect.y() + 25);
        p->rect.setWidth(50);
        p->rect.setHeight(50);
        Eair *nxt = p->next;
        if (p->rect.y() > 800)
        {
            head = enemy::destroyed(i);
            i--;
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
        if (p->rect.y() >= 800 || (p->rect.x() > x && p->rect.x() < x + 100 &&
            p->rect.y() + 50 > y && p->rect.y() + 50 < y + 100))
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
}

enemy::enemy()
{

}

enemy::~enemy()
{

}
