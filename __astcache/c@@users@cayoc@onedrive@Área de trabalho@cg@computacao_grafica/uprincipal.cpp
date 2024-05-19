//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "uJanela.h"
#include "uPrincipal.h"
#include "uPonto.h"
#include "uPoligono.h"
#include "uDisplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTFormPrincipal *TFormPrincipal;

Janela mundo(-250,-250,250,250);
Janela vp(0,0,500,500);
Janela clipper(-125, -125, 125, 125);
Ponto aux;
Poligono pol;
Poligono polaux;
Display display;
bool novo = false;
bool circulo = false;
bool criaclip = false;
int contId = 1;
int cirX;
int cirY;
int cirP;
int i;
int TipoDesenho=0;
int raio;
double eXe;
//---------------------------------------------------------------------------
__fastcall TTFormPrincipal::TTFormPrincipal(TComponent* Owner)
        : TForm(Owner)
{
    //eixo vertical
    pol.pontos.push_back(Ponto(0, mundo.yMax));
    pol.pontos.push_back(Ponto(0, mundo.yMin));
    pol.id = contId++;
    display.poligonos.push_back(pol);
    pol.pontos.clear();

    //eixo horizontal
    pol.pontos.push_back(Ponto(mundo.xMax , 0));
    pol.pontos.push_back(Ponto(mundo.xMin, 0));
    pol.id = contId++;
    display.poligonos.push_back(pol);
    pol.pontos.clear();

    display.desenha(Image1->Canvas, mundo, vp, 0);



}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    double xW,yW;
    Label1->Caption = "( "+ IntToStr(X) +", " + IntToStr(Y) + ")";
    xW=xvp2mundo(X,mundo,vp);
    yW=yvp2mundo(Y,mundo,vp);
    Label2->Caption = "( "+ FloatToStr(xW) +", " + FloatToStr(yW) + ")";
}
//---------------------------------------------------------------------------
double TTFormPrincipal:: xvp2mundo(int x, Janela mundo, Janela vp){
    return ((x-vp.xMin)/(vp.xMax-vp.xMin))*(mundo.xMax-mundo.xMin)+mundo.xMin;
}
double TTFormPrincipal::yvp2mundo (int y, Janela mundo, Janela vp){
    return(1-(y-vp.yMin)/(vp.yMax-vp.yMin))*(mundo.xMax-mundo.xMin)+mundo.yMin;
}


//------------------------------------------------
void __fastcall TTFormPrincipal::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (novo) {
        if (Button == mbLeft) {
            aux.x = xvp2mundo(X, mundo, vp);
            aux.y = yvp2mundo(Y, mundo, vp);
            //ShowMessage(aux.mostra());
            pol.pontos.push_back(aux);
            pol.mostra(lbPontos);
        } else {
            pol.id = contId++;
            pol.nome = 'B';
            display.poligonos.push_back(pol);
            pol.pontos.clear();
            novo = false;
            display.mostra(lbPoligonos);
            display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
        }
    }
    if (circulo) {
		if (Button == mbLeft) {
			circulo = false;
			aux.x = xvp2mundo(X, mundo, vp);
			aux.y = yvp2mundo(Y, mundo, vp);
                        raio = StrToInt(etRaio->Text);

                        pol.circunferencia(aux, raio);

			pol.mostra(lbPontos);
			pol.id = contId++;
                        pol.nome = 'B';
                        display.poligonos.push_back(pol);
                        pol.pontos.clear();
                        novo = false;
                        display.mostra(lbPoligonos);
			display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::bt3DClick(TObject *Sender)
{
FILE * file;
int k,auxInt;
Ponto aux;
Poligono pol;

        switch (rgTipoPoligono3D->ItemIndex)
        {
                case 0:
                        file = fopen("3DCubo.txt", "r");
                        break;
                case 1:
                        file = fopen("3DCubo2.txt", "r");
                        break;
                case 2:
                        file = fopen("3DPiramide.txt", "r");
                        break;
                case 3:
                        file = fopen("3DPiramide2.txt", "r");
                        break;
                default:
                        ShowMessage("Escolha um Poligono 3D!");
        }


        if(rgTipoPoligono3D->ItemIndex != -1){
                fscanf(file, "%d", &k);


                for(int i=0; i < k; i++){

                        fscanf(file, "%d", &auxInt);
                        aux.x = auxInt;
                        fscanf(file, "%d", &auxInt);
                        aux.y = auxInt;
                        fscanf(file, "%d", &auxInt);
                        aux.z = auxInt;
                        pol.pontos.push_back(aux);

                }

                pol.mostra(lbPontos);
                pol.id = contId++;
                display.poligonos.push_back(pol);
                pol.pontos.clear();

                display.mostra(lbPoligonos);

                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                fclose(file);
        }

}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::btNovoClick(TObject *Sender)
{
    novo = true;    
}
//---------------------------------------------------------------------------






void __fastcall TTFormPrincipal::lbPoligonosClick(TObject *Sender)
{
    //ShowMessage( IntToStr(lbPoligonos->ItemIndex));
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btTranslacaoClick(TObject *Sender)
{
    double dx, dy;
    dx = StrToFloat(edX->Text);
    dy = StrToFloat(edY->Text);
    if (lbPoligonos->ItemIndex >= 0) {
        display.translocaDisplay(mundo,vp,dx,dy,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex);
        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
        display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);


    }
    else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::btRotacionaClick(TObject *Sender)
{

    double graus;
    graus = StrToFloat(etGraus->Text);

    if (lbPoligonos->ItemIndex >= 0) {
        display.rotacionaDisplay(mundo,vp,graus,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex);
        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
        display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
    }
    else
        ShowMessage("Escolha um Poligono!");

}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btFlexionaXClick(TObject *Sender)
{
        if (lbPoligonos->ItemIndex >= 0) {
                display.poligonos[lbPoligonos->ItemIndex].reflexoX();
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }
        else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btFlexionaYClick(TObject *Sender)
{
        if (lbPoligonos->ItemIndex >= 0) {
                display.poligonos[lbPoligonos->ItemIndex].reflexoY();
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }
        else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::btEscalonaClick(TObject *Sender)
{
        double dx, dy;
        dx = StrToFloat(edX->Text);
        dy = StrToFloat(edY->Text);

        if (lbPoligonos->ItemIndex >= 0) {
                display.escalonaDisplay(mundo,vp,dx,dy,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex);
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }
        else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------





void __fastcall TTFormPrincipal::rgTipoDesenhoClick(TObject *Sender)
{
   display.desenha(Image1->Canvas,mundo, vp, rgTipoDesenho->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btCimaClick(TObject *Sender)
{
        mundo.yMax += 10;
        mundo.yMin += 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btBaixoClick(TObject *Sender)
{
        mundo.yMax -= 10;
        mundo.yMin -= 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btDireitaClick(TObject *Sender)
{
        mundo.xMax += 10;
        mundo.xMin += 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btEsquerdaClick(TObject *Sender)
{
        mundo.xMax -= 10;
        mundo.xMin -= 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btZoomInClick(TObject *Sender)
{
        mundo.yMax -= 10;
        mundo.yMin += 10;
        mundo.xMax -= 10;
        mundo.xMin += 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btZoomOutClick(TObject *Sender)
{
        mundo.yMax += 10;
        mundo.yMin -= 10;
        mundo.xMax += 10;
        mundo.xMin -= 10;
        display.desenhaEixo(Image1->Canvas,mundo,vp);        
}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::rgTipoTransformacaoClick(TObject *Sender)
{
rgTipoTransformacao;
}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::btCircunferenciaClick(TObject *Sender)
{
       circulo = true; 
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::rgTipoCurvaClick(TObject *Sender)
{
rgTipoCurva;
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btCurvaClick(TObject *Sender)
{
Poligono novacurva;

if (lbPoligonos->ItemIndex >= 0){
  if (rgTipoCurva->ItemIndex == 0) {

        polaux = display.poligonos[lbPoligonos->ItemIndex];
        aux.x = polaux.pontos[0].x+1;
        aux.y = polaux.pontos[0].y+1;
        pol.pontos.push_back(aux);
        pol.casteljau(polaux.pontos[0], polaux.pontos[1], polaux.pontos[2], 0.1);

        pol.mostra(lbPontos);
        pol.id = contId++;
        pol.nome = 'B';
        display.poligonos.push_back(pol);
        pol.pontos.clear();

        display.mostra(lbPoligonos);

        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);

  }
  else
  {
        if (rgTipoCurva->ItemIndex == 1) {

                polaux = display.poligonos[lbPoligonos->ItemIndex];
                pol.hermite(polaux.pontos[0], polaux.pontos[1], polaux.pontos[2], polaux.pontos[3]);

                pol.mostra(lbPontos);
                pol.id = contId++;
                pol.nome = 'B';
                display.poligonos.push_back(pol);
                pol.pontos.clear();

                display.mostra(lbPoligonos);

                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);


        }
        else
        {
                if (rgTipoCurva->ItemIndex == 2) {
                        polaux = display.poligonos[lbPoligonos->ItemIndex];
                        pol.bezier(polaux.pontos[0], polaux.pontos[1], polaux.pontos[2], polaux.pontos[3]);

                        pol.mostra(lbPontos);
                        pol.id = contId++;
                        pol.nome = 'B';
                        display.poligonos.push_back(pol);
                        pol.pontos.clear();

                        display.mostra(lbPoligonos);

                        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);


                }
                else
                {
                        if (rgTipoCurva->ItemIndex == 3) {
                                polaux = display.poligonos[lbPoligonos->ItemIndex];
                                Ponto p1,p2,p3,p4;

                                for(int i = 0;i < polaux.pontos.size()-3; i++){

                                        if(i==0){
                                                p1.x = polaux.pontos[i].x+1;
                                                p1.y = polaux.pontos[i].y+1;
                                        }else{
                                                p1.x = polaux.pontos[i].x;
                                                p1.y = polaux.pontos[i].y;
                                        }

                                        p2.x = polaux.pontos[i+1].x;
                                        p2.y = polaux.pontos[i+1].y;

                                        p3.x = polaux.pontos[i+2].x;
                                        p3.y = polaux.pontos[i+2].y;

                                        p4.x = polaux.pontos[i+3].x;
                                        p4.y = polaux.pontos[i+3].y;

                                        pol.bSpline(p1, p2, p3, p4);
                                }

                                pol.mostra(lbPontos);
                                pol.id = contId++;
                                pol.nome = 'B';
                                display.poligonos.push_back(pol);
                                pol.pontos.clear();

                                display.mostra(lbPoligonos);

                                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);


                        }
                        else
                        {
                                if (rgTipoCurva->ItemIndex == 4){
                                        polaux = display.poligonos[lbPoligonos->ItemIndex];

                                        pol.fwdDifferences(polaux.pontos[0], polaux.pontos[1], polaux.pontos[2], polaux.pontos[3]);

                                        pol.mostra(lbPontos);
                                        pol.id = contId++;
                                        pol.nome = 'B';
                                        display.poligonos.push_back(pol);
                                        pol.pontos.clear();

                                        display.mostra(lbPoligonos);

                                        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                                }
                                else{
                                        ShowMessage("Escolha um Tipo de Curva!");
                                }


                        }
                }
        }
  }

}
else
ShowMessage("Escolha um Poligono!");





}
//---------------------------------------------------------------------------


void __fastcall TTFormPrincipal::btClippingClick(TObject *Sender)
{
        if (criaclip==false)
        {
                pol.pontos.push_back(Ponto(clipper.xMin, clipper.yMax));
                pol.pontos.push_back(Ponto(clipper.xMax, clipper.yMax));
                pol.pontos.push_back(Ponto(clipper.xMax, clipper.xMin));
                pol.pontos.push_back(Ponto(clipper.xMin, clipper.yMin));
                pol.pontos.push_back(Ponto(clipper.xMin, clipper.yMax));

                pol.nome = 'C';
                pol.id = contId++;
                
                display.poligonos.push_back(pol);

                pol.pontos.clear();

                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                criaclip = true;

        }

        int max = display.poligonos.size();

            for (int i = 2; i <= max; i++)
            {
                if ((display.poligonos[i].nome != 'C') &&(display.poligonos[i].nome != 'A'))
                {
                    Poligono Pol;
                    
                    Pol=display.poligonos[i].clipping(clipper, display.poligonos.size());
                    Pol.nome = 'A';
                    Pol.id = contId++;
                    display.poligonos.push_back(Pol);
                    pol.pontos.clear();

                }
            }

            display.mostra(lbPoligonos);
            display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::rgTipoPoligono3DClick(TObject *Sender)
{
rgTipoPoligono3D;
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::rgTipoEixoClick(TObject *Sender)
{
rgTipoEixo;
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btRotaciona3DClick(TObject *Sender)
{
    double graus;
    graus = StrToFloat(etGraus->Text);

    if (lbPoligonos->ItemIndex >= 0) {
        if(rgTipoEixo->ItemIndex == 3){
                display.rotaciona3DDisplay(mundo,vp,graus,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex,0);
                display.rotaciona3DDisplay(mundo,vp,graus,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex,1);
                display.rotaciona3DDisplay(mundo,vp,graus,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex,2);
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }else{
                display.rotaciona3DDisplay(mundo,vp,graus,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex,rgTipoEixo->ItemIndex);
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }
    }
    else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btEscalona3DClick(TObject *Sender)
{
        double dx, dy, dz;
        dx = StrToFloat(edX->Text);
        dy = StrToFloat(edY->Text);
        dz = StrToFloat(edZ->Text);

        if (lbPoligonos->ItemIndex >= 0) {
                display.escalona3DDisplay(mundo,vp,dx,dy,dz,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex);
                display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
                display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);
        }
        else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------

void __fastcall TTFormPrincipal::btTranslada3DClick(TObject *Sender)
{
    double dx, dy, dz;
    dx = StrToFloat(edX->Text);
    dy = StrToFloat(edY->Text);
    dz = StrToFloat(edZ->Text);
    if (lbPoligonos->ItemIndex >= 0) {
        display.transloca3DDisplay(mundo,vp,dx,dy,dz,lbPoligonos->ItemIndex,rgTipoTransformacao->ItemIndex);
        display.desenha(Image1->Canvas, mundo, vp, rgTipoDesenho->ItemIndex);
        display.poligonos[lbPoligonos->ItemIndex].mostra(lbPontos);


    }
    else
        ShowMessage("Escolha um Poligono!");
}
//---------------------------------------------------------------------------




