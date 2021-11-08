#include "enemy.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

enemy::enemy(int _health, int _damage, int _movSpeed)
{
    health = _health;
    powerDamage = _damage;
    movementSpeed = _movSpeed;
}
enemy::enemy(int _health, int _damage, float _vx, float _vy)
{
    health = _health;
    powerDamage = _damage;
    vx = _vx;
    vxo = _vx;
    vy = _vy;
}
enemy::enemy(int _health, int _damage, float _vx, float _vy, float _a)
{
    health = _health;
    powerDamage = _damage;
    vx = _vx;
    vxo = _vx;
    vy = _vy;
    vyo = _vy;
    a = _a;
}
enemy::enemy(QString s, int _size)
{
    charImg = QImage(s);
    shapeBrush = new QBrush(charImg.scaled(_size,_size,Qt::KeepAspectRatio));
}

void enemy::moveEnemies1(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t = 0.1;
        float y = enm->y()+(vy*t);
        enm->setPos(enm->x(),y);
        if(y>=870){
            vy=-vy;
        }
        else if(y<=55){
            vy=-vy;
        }
    }
}

void enemy::moveEnemie2(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t = 0.1;
        float y = enm->y()+(vy*t);
        float x = enm->x()+(vx*t)+(9.81*t*t)/2.0;
        vx += 9.81*t;
        if(x>=1100){
            vx=vxo;
            vy=-vy;
        }
        enm->setPos(x,y);
    }
}

void enemy::moveEnemies3(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t = 0.1;
        float y = enm->y()+(vy*t);
        enm->setPos(enm->x(),y);
        if(y>=870){
            vy=-vy;
        }
        else if(y<=55){
            vy=-vy;
        }
    }
}

void enemy::moveEnemie4(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){

        float t=0.1;
        float px=enm->x(),py=enm->y();
        float ax = a*cos(atan2(500-py,900-px)),
                ay = a*sin(atan2(500-py,900-px));
        py += (vy*t)+(ay*t*t)/2.0;
        px += (vx*t)+(ax*t*t)/2.0;
        vx += ax*t;
        vy += ay*t;
        if(int(py)==500&&px>900){
            px=1000.0;
            py=500.0;
            vx=vxo;
            vy=vyo;
        }
        enm->setPos(px,py);
    }
}

void enemy::moveEnemie5(std::vector<QGraphicsRectItem*> enems)
{
    for(auto enm:enems){
        float t=0.01;
        float px=enm->x(), py=enm->y();
        float ax=-(px-500), ay=-(py-375);

        px+= (vx*t)+((ax*t*t)/2.0);

        vx += ax*t;

        if(px==500){
            px=500.0;
            vx=(-vx/vx)*250.0;
        }

        py+= (vy*t)+((ay*t*t)/2.0);

        vy += ay*t;

        if(py==200){
            py=200.0;
            vy=(-vy/vy)*200.0;
        }
        enm->setPos(enm->x(),py);
    }
}

bool enemy::detectCollision(QGraphicsItem* object, std::vector<QGraphicsRectItem*> bVector){
    for(auto block:bVector){
        if(object->collidesWithItem(block)){
            return true;
        }
    }
    return false;
}
