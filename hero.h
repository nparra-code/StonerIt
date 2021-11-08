#ifndef HERO_H
#define HERO_H

#include "character.h"

#include <QObject>
#include <QPen>

class hero : public character
{
    //Q_OBJECT
public:
    explicit hero(int,int,int,QString);
    QBrush getBrush() const;
private:
    QBrush brush;
};

#endif // HERO_H
