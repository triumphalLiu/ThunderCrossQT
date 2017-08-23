#include "bullet.h"
#include <QDebug>
void bullet::init()
{
    count = 0;
    head = NULL;
    BulletGraph = new QPixmap;
    BulletGraph->load("res/bullet.png");
}

Bair *bullet::add(int x, int y, int flag)
{
    count++;
    Bair *p = new Bair;
    p->flag = flag;
    p->rect.setX(x);
    if (flag == 1)
        p->rect.setY(y - 1);
    else
        p->rect.setY(y + 1);
    p->next = NULL;
    if (head == NULL)
        head = p;
    else
    {
        p->next = head;
        head = p;
    }
    return head;
}
Bair *bullet::del(Bair *node)
{
    count--;
    if (node == head)
    {
        head = head->next;
    }
    else
    {
        Bair *p = head;
        while (p->next != node)
        {
            p = p->next;
        }
        Bair *del = p->next;
        p->next = del->next;
        free(del);
    }
    return head;
}

Bair *bullet::move()
{
    Bair *p = head;
    while (p != NULL)
    {
        if (p->flag == 1)
            p->rect.setY(p->rect.y() - 11);
        else if (p->flag == 0)
            p->rect.setY(p->rect.y() + 11);
        Bair *n = p->next;
        if (p->rect.y() <= 100 || p->rect.y() >= 900)
        {
            head = bullet::del(p);
            if (head == NULL)
                return head;
        }
        p = n;
    }
    return head;
}

bool bullet::check(int x, int y, int flag)  // dead=0
{
    qDebug() << x << y;
    Bair *p = head;
    while (p != NULL)
    {
        Bair *nxt = p->next;
        if (p->flag | flag)
        {
            qDebug() << "*" << p->rect.x() << p->rect.y();
            if (flag == 0 && (p->rect.x() >= x && p->rect.x() <= x + 50) && (p->rect.y() >= y && p->rect.y() <= y + 50))
            {
                head = bullet::del(p);
                return 0;
            }
            else if (flag == 1 && (p->rect.x() >= x && p->rect.x() <= x + 100) && (p->rect.y() >= y && p->rect.y() <= y + 100))
            {
                head = bullet::del(p);
                return 0;
            }
        }
        p = nxt;
    }
    return 1;
}

bullet::bullet()
{

}

bullet::~bullet()
{

}
