#include "cuerpo.h"
#include <QPainter>

double cuerpo::getPX() const
{
    return pX;
}

double cuerpo::getPY() const
{
    return pY;
}

double cuerpo::getM() const
{
    return m;
}

double cuerpo::getAX() const
{
    return aX;
}

void cuerpo::setAX(double newAX)
{
    aX = newAX;
}

double cuerpo::getAY() const
{
    return aY;
}

void cuerpo::setAY(double newAY)
{
    aY = newAY;
}

cuerpo::cuerpo()
{

}

cuerpo::cuerpo(double x, double y, double ms, double rd, double vx, double vy)
{
    pX = x;
    pY = y;
    velX = vx;
    velY = vy;
    m = ms;
    r = rd*0.1;
    setPos(pX*0.025,-pY*0.025);
}

void cuerpo::CalVel()
{
    velX = velX+aX*tiempo;
    velY = velY/*sin(this->a)*/+aY*tiempo/**tiempo*/;
}

void cuerpo::CalP()
{
    pX += velX*tiempo+((aX*tiempo*tiempo)/2);
    pY += velY*tiempo+((aY*tiempo*tiempo)/2);
    setPos(pX*0.025,-pY*0.025); //setPos(pX,-pY);
}

void cuerpo::CalA(double mO, double xO, double yO)
{
    if(xO != pX || yO != pY) {
        aX = ((mO) / (pow((xO - pX), 2) + pow((yO - pY), 2))) * std::cos(a);
        aY = ((mO) / (pow((xO - pX), 2) + pow((yO - pY), 2))) * std::sin(a);
    }
    else
    {
        // Manejo de división por cero
        aX = 0.0;
        aY = 0.0;
    }
}

void cuerpo::A(double xO, double yO)
{
    double d1, d2;
    d1 = (yO-pY);
    d2 = (xO-pX);
    a = atan2(d1, d2);
}

QRectF cuerpo::boundingRect() const
{
    return QRect(-r, -r, 2*r,2*r);
}

void cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}
