#ifndef LUTADOR_H
#define	LUTADOR_H
#include <GL/gl.h>
#include <GL/glu.h>

#define thetaInicial1 225
#define thetaInicial2 135

#define cores 135, 1, 2


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

    // Controle
    GLboolean jogador;

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

    void Iniciacao(GLfloat x, GLfloat y, GLfloat angulo, GLfloat raio){
    
        rCabeca = raio;
        gX = x;
        gY = y;
        gGiro = angulo;

        bracoHeight = rCabeca * 2;
        bracoWidth = rCabeca/4;

        rNariz = rCabeca/3;
        rMao = rCabeca/2;

        gThetaDireito1 = thetaInicial1;
        gThetaDireito2 = thetaInicial2;

        gThetaEsquerdo1 = thetaInicial2;
        gThetaEsquerdo2 = thetaInicial1;

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
