//---------------------------------------------------------------------------
#pragma hdrstop
#include "uDisplay.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void Display::mostra(TListBox *retorno){
    retorno->Items->Clear();
    for(unsigned int i = 0; i < poligonos.size(); i++){
        retorno->Items->Add(IntToStr(poligonos[i].id));
    }
}

void Display::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta){
    canvas->Pen->Color = clBlack;
    canvas->Pen->Width = 3; //grossura da caneta(ocupa 3 pixels)
    canvas->Brush->Color = clWhite;
    canvas->FillRect(Rect(0,0,500,500));

    for(unsigned int i = 0; i < poligonos.size(); i++){
        if (i > 1){
            canvas->Pen->Color = clRed;
        }
        if(poligonos[i].nome == 'A'){
                canvas->Pen->Width = 6;
        }
        else{
                canvas->Pen->Width = 3;
        }
        poligonos[i].desenha(canvas, mundo, vp, tipoReta);
    }
}

void Display::desenhaEixo(TCanvas *canvas,Janela mundo, Janela vp){

  canvas->FillRect(Rect(1,1,500,500));
  poligonos[0].pontos[0].x = 0;
  poligonos[0].pontos[0].y = mundo.yMax;	//eixo y de cima para baixo
  poligonos[0].pontos[1].x=0;
  poligonos[0].pontos[1].y = mundo.yMin;
  poligonos[1].pontos[0].x = mundo.xMin;
  poligonos[1].pontos[0].y = 0;	//eixo x da esquerda pra direita
  poligonos[1].pontos[1].x = mundo.xMax;
  poligonos[1].pontos[1].y = 0;

  desenha(canvas,mundo,vp,0);

}

void Display::translocaDisplay(Janela mundo, Janela vp,double auxX,double auxY, int indice,boolean homogenea)
{
 double x,y;
 for(int j = 0; j < poligonos[indice].pontos.size(); j++){
    x = poligonos[indice].pontos[j].x;
    y = poligonos[indice].pontos[j].y;
    poligonos[indice].translada(auxX, auxY, &x, &y,homogenea);

    poligonos[indice].pontos[j].x = x;
    poligonos[indice].pontos[j].y = y;
   }   //j

}

void Display::transloca3DDisplay(Janela mundo, Janela vp,double auxX,double auxY,double auxZ, int indice,boolean homogenea)
{
 double x,y,z;
 for(int j = 0; j < poligonos[indice].pontos.size(); j++){
    x = poligonos[indice].pontos[j].x;
    y = poligonos[indice].pontos[j].y;
    z = poligonos[indice].pontos[j].z;
    poligonos[indice].translada(auxX, auxY, auxZ, &x, &y, &z, homogenea);

    poligonos[indice].pontos[j].x = x;
    poligonos[indice].pontos[j].y = y;
    poligonos[indice].pontos[j].z = z;
   }   //j

}

void Display::escalonaDisplay(Janela mundo, Janela vp,double auxX,double auxY, int indice,boolean homogenea)
{
 double x,y,Xce,Yce;

  Xce=poligonos[indice].PontoCentralX();
  Yce=poligonos[indice].PontoCentralY();

   for(int j = 0; j < poligonos[indice].pontos.size(); j++){
        x = poligonos[indice].pontos[j].x;
        y = poligonos[indice].pontos[j].y;
        poligonos[indice].escalona(mundo,vp,auxX, auxY, &poligonos[indice].pontos[j].x, &poligonos[indice].pontos[j].y,Xce,Yce,homogenea);

   }   //j
}


void Display::escalona3DDisplay(Janela mundo, Janela vp,double auxX,double auxY,double auxZ, int indice,boolean homogenea)
{
 double x,y,z,Xce,Yce,Zce;

  Xce=poligonos[indice].PontoCentralX();
  Yce=poligonos[indice].PontoCentralY();
  Zce=poligonos[indice].PontoCentralZ();

   for(int j = 0; j < poligonos[indice].pontos.size(); j++){
        x = poligonos[indice].pontos[j].x;
        y = poligonos[indice].pontos[j].y;
        z = poligonos[indice].pontos[j].z;
        poligonos[indice].escalona(mundo,vp,auxX, auxY, auxZ, &poligonos[indice].pontos[j].x, &poligonos[indice].pontos[j].y, &poligonos[indice].pontos[j].z, Xce,Yce,Zce, homogenea);

   }   //j
}


void Display::rotacionaDisplay(Janela mundo, Janela vp,double teta, int indice,boolean homogenea)
{
 double x,y,Xce,Yce;
  Xce=poligonos[indice].PontoCentralX();
  Yce=poligonos[indice].PontoCentralY();

   for(int j = 0; j < poligonos[indice].pontos.size(); j++){
        x = poligonos[indice].pontos[j].x;
        y = poligonos[indice].pontos[j].y;
        poligonos[indice].rotacao(teta, &poligonos[indice].pontos[j].x, &poligonos[indice].pontos[j].y,Xce,Yce,homogenea);
   }   //j


}

void Display::rotaciona3DDisplay(Janela mundo, Janela vp,double teta, int indice,boolean homogenea, int eixo)
{
 double x,y,z,Xce,Yce,Zce;
  Xce=poligonos[indice].PontoCentralX();
  Yce=poligonos[indice].PontoCentralY();
  Zce=poligonos[indice].PontoCentralZ();

   for(int j = 0; j < poligonos[indice].pontos.size(); j++){
        x = poligonos[indice].pontos[j].x;
        y = poligonos[indice].pontos[j].y;
        z = poligonos[indice].pontos[j].z;
        poligonos[indice].rotacao(teta, &poligonos[indice].pontos[j].x, &poligonos[indice].pontos[j].y, &poligonos[indice].pontos[j].z,Xce,Yce,Zce,homogenea,eixo);
   }   //j


}
