#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <math.h>

class movement
{
public:
    movement(float _pxo, float _px,float _py, float _vxo,float _vx,float _vy){
        px = _px;
        pxo = _pxo;
        py = _py;
        vx = _vx;
        vxo = _vxo;
        vy = _vy;
        vyo = _vy;
    }
    movement(float _pxo, float _px,float _py, float _vxo,float _vx,float _vy,float _a){
        px = _px;
        pxo = _pxo;
        py = _py;
        vx = _vx;
        vxo = _vxo;
        vy = _vy;
        vyo = _vy;
        a = _a;
    }
    float getPx() const{
        return px;
    }

    float getPy() const{
        return py;
    }

    void calcParabPos(float t){
        py += vy*t;
        px += (vx*t)+(g*t*t)/2.0;
        vx += g*t;
        if(px>=pxo){
            vx=vxo;
            vy=-vy;
        }
    }

    void calcCircPos(float t){
        ax = a*cos(atan2(py,px));
        ay = a*sin(atan2(py,px));
        py += (vy*t)+(ay*t*t)/2.0;
        px += (vx*t)+(ax*t*t)/2.0;
        vx += ax*t;
        vy += ay*t;

    }

    double getVx() const;

    double getVy() const;

private:
    double px, py, pxo,
    vx, vy, vxo, vyo,
    a, ax, ay, g = 9.81;
};

inline double movement::getVx() const
{
    return vx;
}

inline double movement::getVy() const
{
    return vy;
}

#endif // MOVEMENT_H
