#ifndef SONERIT_H
#define SONERIT_H

#define DATA "../StonerIt/BD/data.txt"
#define RCRD "../StonerIt/BD/record.txt"
#define BCKGS "../StonerIt/BD/start.png"
#define BCKGE "../StonerIt/BD/end.png"
#define MAP_1 "../StonerIt/BD/map1/"
#define MAP_2 "../StonerIt/BD/map2/"
#define MAP_3 "../StonerIt/BD/map3/"
#define MAP_4 "../StonerIt/BD/map4/"
#define MAP_5 "../StonerIt/BD/map5/"
#define HERO_B "../StonerIt/BD/bu.png"

#include <QMainWindow>
#include <QGraphicsScene>
#include <hero.h>
#include "enemy.h"
#include "map.h"
#include "sprite.h"
#include <QTimer>
#include <QFlag>
#include <QKeyEvent>
#include <vector>
#include <fstream>
#include <list>

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class sonerit; }
QT_END_NAMESPACE

class sonerit : public QMainWindow
{
    Q_OBJECT

public:

    sprite *heroS;
    sprite *heroS2;
    std::vector<std::string> gameInfo {};

    sonerit(QWidget *parent = nullptr);
    ~sonerit();

    void changeScene();
    bool detectCollision(QGraphicsItem*);
    bool detectBulletCollision(std::list<QGraphicsRectItem*>*);
    bool bullCollToEnm(std::list<QGraphicsRectItem*>);
    bool secondHeroExists=false;
protected:
    QGraphicsScene* start;
    QGraphicsScene* scene1;
    QGraphicsScene* scene2;
    QGraphicsScene* scene3;
    QGraphicsScene* scene4;
    QGraphicsScene* scene5;
    QGraphicsScene* end;

    void keyPressEvent(QKeyEvent *event);
    void loadGame();
    void saveGame();
    void saveRecord();
    void startGameTimers();
    void stopTimers();
private slots:
    void move();
    void enemyShoot();
    void moveBullet();
    void moveEnemies();
    void timerCount();
    void on_continue_button_clicked();
    void moveHeroBulletsRight(std::list<QGraphicsRectItem*>*);
    void moveHeroBulletsLeft(std::list<QGraphicsRectItem*>*);
    void moveHeroBulletsUp(std::list<QGraphicsRectItem*>*);
    void moveHeroBulletsDown(std::list<QGraphicsRectItem*>*);
    void on_pushButton_clicked();
    void checkStatus();
    void checkScndPly();
private:
    Ui::sonerit *ui;

    QBrush activeBrushBullet,
           brushBullet1,brushBullet2,brushBullet3,brushBullet4,brushBullet5;

    std::string playerName1="", playerName2="";
    int heroHealth1, heroHealth2;
    int enemyDamage;
    int points=0, timeLeft=0, oTime = 61, lastLvlTime=120;

    QTimer* timer;
    QTimer* timerLive;
    QTimer* timerMov;
    QTimer* timerM;
    QTimer* timerHB;
    QTimer* timer2HB;
    QTimer* checkStart;
    QTimer* timerEnemyMov;
    QTimer* timerTimeLeft;

    qreal h1XPOS_O=70, h1YPOS_O=70, h1XPOS=h1XPOS_O, h1YPOS=h1YPOS_O;
    qreal h2XPOS_O=70, h2YPOS_O=860, h2XPOS=h2XPOS_O, h2YPOS=h2YPOS_O;


    hero Hero = hero(20,25,7,HERO_B);
    QGraphicsItem* h1;
    QGraphicsItem* h2;

    std::vector<int> enemiesHealth {};

    std::vector<QGraphicsRectItem*> activeEnemies;
    std::vector<QGraphicsRectItem*> enemies;
    std::vector<QGraphicsRectItem*> enemies2;
    std::vector<QGraphicsRectItem*> enemies3;
    std::vector<QGraphicsRectItem*> enemies4;
    std::vector<QGraphicsRectItem*> enemies5;

    std::vector<QGraphicsItem*> bullets;
    std::list<QGraphicsRectItem*> hero1Bullet;
    std::list<QGraphicsRectItem*> hero2Bullet;
    void createHero1Bullet();
    void createHero2Bullet();
    void createHero();

    int activeScene;

    int shootingTime=6000, bulletTime=shootingTime/100;

    std::vector<QGraphicsRectItem*> blocksVector;
    std::vector<QGraphicsRectItem*> blocksVectorChief;
    std::vector<QGraphicsRectItem*> blocksVector3;

    enemy enemy1 = enemy(50,20,0.0,7.0);
    enemy enemy2 = enemy(200,30,-62.64184,31.32096);
    enemy enemy3 = enemy(100,25,0.0,10.0);
    enemy enemy4 = enemy(400,40,0.0,-20.0,4.0);
    enemy enemy5 = enemy(500,50,250.0,200.0);
    enemy enmArray[5] {enemy1,enemy2,enemy3,enemy4,enemy5};

    char direction1 = 'd', direction2 = 'd';
    bool timerHBe=false,timer2HBe=false;
};
#endif // SONERIT_H
