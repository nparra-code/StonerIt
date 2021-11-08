#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsRectItem>
#include <QImage>

class character
{
public:
    int getHealth();
    int getDamage();

    /*classtype*/ int power;
    int size;
    int health;
    int powerDamage;
    int movementSpeed;

    int powerDistance;
    QImage charImg;
private:

};

#endif // CHARACTER_H
