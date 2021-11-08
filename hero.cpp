#include "hero.h"

hero::hero(int _health, int _damage, int _moveSp, QString s)
{
    health = _health;
    powerDamage = _damage;
    movementSpeed = _moveSp;

    QImage img(s);
    brush = QBrush(img);
}

QBrush hero::getBrush() const
{
    return brush;
}
