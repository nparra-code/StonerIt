#include "map.h"

mapa::mapa(std::string t, QGraphicsScene* s, std::vector<QGraphicsRectItem*>* v,
         std::vector<QGraphicsRectItem*>* e, int enemySize)
{
    QString qstrT = QString::fromStdString(t);
    std::vector<int> auxVctr {};
    QImage aBlock(qstrT+"a.png"), bBlock(qstrT+"b.png"), bg(qstrT+"bg.png"), bull(qstrT+"bu.png");
    QBrush aBlockBrush(aBlock),bBlockBrush(bBlock),bgBrush(bg);
    bullet = QBrush(bull);
    s->setBackgroundBrush(bgBrush);

    std::ifstream inFile;
    inFile.open(t+"map.txt");

    std::string data;
    inFile >> data;

    for(unsigned long long i=0;i<data.length();i++){
        if(data[i]=='1'||data[i]=='0'||data[i]=='2'||data[i]=='3') auxVctr.push_back(data[i]-48);
        else if(data[i]=='}'&&auxVctr.size()!=0){
            value.push_back(auxVctr);
            auxVctr.clear();
        }
    }
    inFile.close();

    QString qstr = QString::fromStdString(t+"e.png");
    enemy Enemy(qstr,enemySize);

    v->clear();
    int y=0;
    for(unsigned long long row=0;row<value.size();row++){
        int x=0;
        for(unsigned long long column=0;column<value.at(row).size();column++){
            if(value.at(row).at(column)==1){
                QGraphicsRectItem* temp = s->addRect(0,0,blockSize,blockSize,QPen(Qt::transparent),aBlockBrush);
                temp->setPos(x,y);
                v->push_back(temp);
            }
            else if(value.at(row).at(column)==2){
                QGraphicsRectItem* temp = s->addRect(0,0,blockSize,blockSize,QPen(Qt::transparent),bBlockBrush);
                temp->setPos(x,y);
                v->push_back(temp);
            }
            else if(value.at(row).at(column)==3){
                QGraphicsRectItem* temp = s->addRect(0,0,enemySize,enemySize,QPen(Qt::transparent),*Enemy.shapeBrush);
                temp->setPos(x,y);
                e->push_back(temp);
            }
            x+=blockSize;
        }
        y+=blockSize;
    }
}

mapa::mapa(std::string t, QGraphicsScene* s,std::vector<QGraphicsRectItem*>* e, int enemySize)
{
    QString qstrT = QString::fromStdString(t);
    std::vector<int> auxVctr {};
    QImage aBlock(qstrT+"a.png"), bBlock(qstrT+"b.png"), bg(qstrT+"bg.png"), bull(qstrT+"bu.png");
    QBrush aBlockBrush(aBlock),bBlockBrush(bBlock),bgBrush(bg);
    bullet = QBrush(bull);
    s->setBackgroundBrush(bgBrush);

    std::ifstream inFile;
    inFile.open(t+"map.txt");

    std::string data;
    inFile >> data;

    for(unsigned long long i=0;i<data.length();i++){
        if(data[i]=='1'||data[i]=='0'||data[i]=='2'||data[i]=='3') auxVctr.push_back(data[i]-48);
        else if(data[i]=='}'&&auxVctr.size()!=0){
            value.push_back(auxVctr);
            auxVctr.clear();
        }
    }
    inFile.close();

    QString qstr = QString::fromStdString(t+"e.png");
    enemy Enemy(qstr,enemySize);

    int y=0;
    for(unsigned long long row=0;row<value.size();row++){
        int x=0;
        for(unsigned long long column=0;column<value.at(row).size();column++){
            if(value.at(row).at(column)==1){
                QGraphicsRectItem* temp = s->addRect(0,0,blockSize,blockSize,QPen(Qt::transparent),aBlockBrush);
                temp->setPos(x,y);
            }
            else if(value.at(row).at(column)==2){
                QGraphicsRectItem* temp = s->addRect(0,0,blockSize,blockSize,QPen(Qt::transparent),bBlockBrush);
                temp->setPos(x,y);
            }
            else if(value.at(row).at(column)==3){
                QGraphicsRectItem* temp = s->addRect(0,0,enemySize,enemySize,QPen(Qt::transparent),*Enemy.shapeBrush);
                temp->setPos(x,y);
                e->push_back(temp);
            }
            x+=blockSize;
        }
        y+=blockSize;
    }
}

QBrush mapa::getBrushBullet() const
{
    return bullet;
}
