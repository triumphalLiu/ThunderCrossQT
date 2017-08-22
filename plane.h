#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
class plane
{
public:
    plane(int X, int Y);
    ~plane();
    int score;
    int level;
    void destroyed();
    void move(int key);
    QPixmap *MyPlane;
    QRect *MyLoc;
private:
};

#endif // PLANE_H
