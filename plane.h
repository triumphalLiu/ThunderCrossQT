#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
class plane
{
public:
    plane();
    ~plane();
    void init(int X, int Y);
    int score;
    int level;
    void destroyed();
    void move(int key);
    QPixmap *MyPlane;
    QRect *MyLoc;
private:
};

#endif // PLANE_H
