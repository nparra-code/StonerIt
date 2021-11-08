#include "sprite.h"

sprite::sprite(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    rows=0;
    columns=0;

    pixmap = new QPixmap(":/BD/heroSprite.png");

    width=70;
    height=70;

    timer->start(150);

    connect(timer,SIGNAL(timeout()),this,SLOT(act()));
}

void sprite::act()
{
    columns+=70;
    if(columns>=210) columns=0;

    this->update(0,0,width,height);
}

QRectF sprite::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,*pixmap,columns,direction,width,height);
}

void sprite::changeDirection(int _direction)
{
    direction = _direction;
}

