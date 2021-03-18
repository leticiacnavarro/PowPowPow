#ifndef LUTADOR_H
#define	LUTADOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

using namespace std;

#define thetaInicial1 135
#define thetaInicial2 225

using namespace std;

class Lutador
{
    // Dimensões Corpo
    GLfloat rCabeca;
    GLfloat rNariz;
    GLfloat rMao;

    GLfloat bracoHeight;
    GLfloat bracoWidth;

    // Angulos
    GLfloat gGiro;

    GLfloat gThetaDireito1;
    GLfloat gThetaDireito2;

    GLfloat gThetaEsquerdo1;
    GLfloat gThetaEsquerdo2;

    //Posições
    GLfloat gX;
    GLfloat gY;

    // Cores RGB
    array<float,3> maoRGB; 
    array<float,3> bracoRGB; 
    array<float,3> cabecaRGB; 

private:
    void DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B);

    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);

    void DesenhaCabeca(GLfloat x, GLfloat y);

    void DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2);

    void DesenhaLutador(GLfloat x, GLfloat y);

    bool AcertouCabeca(GLfloat inimigox, GLfloat inimigoy, int braco);

    void SocaBracoDireito(GLfloat angulo1, GLfloat angulo2);

    void SocaBracoEsquerdo(GLfloat angulo1, GLfloat angulo2);

public:

    Lutador(){
    }

    void Iniciacao(GLfloat x, GLfloat y, GLfloat angulo, GLfloat raio, bool bot){
        
        array<float,3> maoLutadorRGB = {1.02, 0.616, 0.648};
        array<float,3> bracoLutadorRGB = {0.62,	0.872, 0.772};
        array<float,3> cabecaLutadorRGB = {1.02, 0.732, 0.712};

        array<float,3> maoBotRGB = {0.1, 0.5, 0.4};
        array<float,3> bracoBotRGB = {0.1, 0.5, 0.4};
        array<float,3> cabecaBotRGB = {0.1, 0.5, 0.4};

        rCabeca = raio;
        gX = x;
        gY = y;
        gGiro = angulo;

        bracoHeight = rCabeca * 1.5;
        bracoWidth = rCabeca/3;

        rNariz = rCabeca/3;
        rMao = rCabeca/2;

        gThetaDireito1 = thetaInicial2;
        gThetaDireito2 = thetaInicial1;

        gThetaEsquerdo1 = thetaInicial1;
        gThetaEsquerdo2 = thetaInicial2;

        if(bot)
        {
            maoRGB = maoBotRGB;
            cabecaRGB = cabecaBotRGB;
            bracoRGB = bracoBotRGB;
        }
        else
        {
            maoRGB = maoLutadorRGB;
            cabecaRGB = cabecaLutadorRGB;
            bracoRGB = bracoLutadorRGB;
        }  

    };

    GLfloat GetX();

    GLfloat GetY();
    
    void Desenha(){
        DesenhaLutador(gX, gY);
    }

    void Gira(GLfloat inc);
    
    void Anda(GLfloat dY);
    
    bool Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, GLfloat inimigox, GLfloat inimigoy);
    
    void ParaDeSocar();

    bool VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2);
    
    void GiraSozinho(GLfloat inc, GLfloat xLutador, GLfloat yLutador);

};

#endif	/* LUTADOR_H */
