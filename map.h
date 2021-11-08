#ifndef MAP_H
#define MAP_H

#include <QImage>
#include <string>
#include <vector>
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "enemy.h"

class mapa
{
public:
    mapa(std::string,QGraphicsScene*,std::vector<QGraphicsRectItem*>*,std::vector<QGraphicsRectItem*>*,int);
    mapa(std::string,QGraphicsScene*,std::vector<QGraphicsRectItem*>*,int);

    int blockSize = 50;

    QBrush getBrushBullet() const;

private:
    std::vector<std::vector<int>> value;
    QBrush bullet;
};

#endif // MAP_H
