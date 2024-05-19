//---------------------------------------------------------------------------

#ifndef uPoligonoH
#define uPoligonoH
#include<vector>
#include <StdCtrls.hpp>   
#include "uPonto.h"
#include "uJanela.h"
#define PI 3.14159265

using namespace std;
//---------------------------------------------------------------------------
class Poligono{
    public:
        vector <Ponto> pontos;
        int id, TipoDesenho;
        char nome;

        double PontoCentralX();
        double PontoCentralY();
        double PontoCentralZ();

        void mostra(TListBox *retorno);
        void desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta);
        
        void drawBresenham(TCanvas *canvas, int x1, int y1, int x2, int y2);
        void drawDDA(TCanvas *canvas, int x1, int y1, int x2, int y2);
        //TRANSFORMA��ES
        void translada(double x, double y, double *px, double *py, boolean homogenea);
        void escalona(Janela mundo,Janela vp,double x, double y, double *px, double *py, double Xc, double Yc,boolean homogenea);
        void rotacao(double teta, double *px, double *py, double Xc, double Yc,boolean homogenea);
        void reflexo (int op);
        void reflexoX();
        void reflexoY();
        void circunferencia(Ponto aux, int r);
        //TRANSFORMA��ES 3D
        void translada(double x, double y, double z, double *px, double *py, double *pz, boolean homogenea);
        void escalona(Janela mundo,Janela vp,double x, double y, double z, double *px, double *py, double *pz, double Xc, double Yc, double Zc, boolean homogenea);
        void rotacao(double teta, double *px, double *py, double *pz, double Xc, double Yc,double Zc, boolean homogenea, int eixo);
        //CURVAS
        void casteljau(Ponto p1, Ponto p2, Ponto p3, double limite);
        void hermite(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
        void bezier(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
        void bSpline(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
        void fwdDifferences(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
        //CLIPPING
        Poligono clipping(Janela clip, int nPol);
        Ponto novoPonto(Ponto aux, double x, double y);

};



#endif
 