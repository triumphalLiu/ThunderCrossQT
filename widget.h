#ifndef WIDGET_H
#define WIDGET_H
#include "common.h"
#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QSound>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    void loadPictures();
    void startGame();
    void exitGame();
    void pauseGame();
    void returnMainpage();
    void play();
    QImage *backgroundImg;
    QImage *startImg;
    QImage *exitImg;
    QImage *gameImg1;
    QImage *gameImg2;
    QImage *pauseImg;
    QImage *sndonImg;
    QImage *sndoffImg;
    QSound *sound;
    bool soundState;
    bool pauseState = 0;
    QRect *HeroLoc = NULL;
    QPixmap *Hero = NULL;
    Eair *EnemyHead = NULL;
    QPixmap *EnemyGraph = NULL;
    Bair *BulletHead = NULL;
    QPixmap *BulletGraph = NULL;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *t);
};

#endif // WIDGET_H
