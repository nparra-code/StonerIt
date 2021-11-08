#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = nullptr);
    QTimer* timer;
    QPixmap* pixmap;

    float rows,columns,
    width,height;

    QRectF boundingRect() const;
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);

    void changeDirection(int _direction);

    int direction=0;

signals:

public slots:
    void act();

};

#endif // SPRITE_H
