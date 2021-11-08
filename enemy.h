#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "movement.h"

#include <QObject>
#include <QPen>

class enemy : public character
{
    //Q_OBJECT
public:
    explicit enemy(int,int,int);
    enemy(int,int,float,float);
    enemy(int,int,float,float,float);
    enemy(QString,int);
    QBrush* shapeBrush;
    QBrush bullet;
    void moveEnemies1(std::vector<QGraphicsRectItem*>);
    void moveEnemie2(std::vector<QGraphicsRectItem*>);
    void moveEnemies3(std::vector<QGraphicsRectItem*>);
    void moveEnemie4(std::vector<QGraphicsRectItem*>);
    void moveEnemie5(std::vector<QGraphicsRectItem*>);
    bool detectCollision(QGraphicsItem*,std::vector<QGraphicsRectItem*>);

signals:
private:
    float vxo, vyo, vx, vy, a;

};

#endif // ENEMY_H
