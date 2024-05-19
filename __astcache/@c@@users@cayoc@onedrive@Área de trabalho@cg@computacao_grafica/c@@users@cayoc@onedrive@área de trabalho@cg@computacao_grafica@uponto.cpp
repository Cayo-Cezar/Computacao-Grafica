//---------------------------------------------------------------------------


#pragma hdrstop


#include "uPonto.h"
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
Ponto::Ponto(){
    x = y = z = 0;
}

Ponto::Ponto(double xN, double yN){
    x = xN;
    y = yN;
}

Ponto::Ponto(double xN, double yN, double zN){
    x = xN;
    y = yN;
    z = zN;
}
    int Ponto::xw2vp(Janela mundo, Janela vp){
        return((x - mundo.xMin) / (mundo.xMax - mundo.xMin)) *
            (vp.xMax-vp.xMin);
    }
    int Ponto::yw2vp(Janela mundo,Janela vp){
        return (1 - (y - mundo.yMin) / (mundo.yMax-mundo.yMin)) *
            (vp.xMax-vp.xMin);
    }

AnsiString Ponto::mostra(){
    return "(" + FloatToStrF(x, ffFixed, 3, 3) + ", " + FloatToStrF(y, ffFixed, 3, 3) + ", " + FloatToStrF(z, ffFixed, 3, 3) + ")";
}


void Ponto::reflexoX (){
        x *= -1;
}

void Ponto::reflexoY (){
        y *= -1;
}

void Ponto::reflexoXY (){
        reflexoX();
        reflexoY();
}

//REGIONCODE CLIPPING
int Ponto::regionCode(Janela clip)
{
int cohen = 0;

        cohen += (x < clip.xMin) ? 1 : 0;
        cohen += (x > clip.xMax) ? 2 : 0;
        cohen += (y < clip.yMin) ? 4 : 0;
        cohen += (y > clip.yMax) ? 8 : 0;

return cohen;
}
