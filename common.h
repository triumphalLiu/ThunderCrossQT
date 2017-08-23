#ifndef COMMON_H
#define COMMON_H

#include <QRect>

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
