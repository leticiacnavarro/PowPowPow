#include "lutador.h"
#include <math.h>
#include <stdio.h>

void Lutador::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    float halfWidth = width/2;

    glColor3f (R, G, B);
    glBegin(GL_QUADS);
        glVertex2f(-halfWidth, 0);
        glVertex2f(halfWidth, 0);
        glVertex2f(halfWidth, height);
        glVertex2f(-halfWidth, height);
    glEnd();
}

void Lutador::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    int pts = 20;
    glColor3f (R, G, B);

    for(unsigned int i = 0; i <= pts; ++i ){

        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        float x = radius * sin(angle);
        float y = radius * cos(angle);
        
        glPointSize(3);

        glBegin(GL_POLYGON);
            glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void Lutador::DesenhaCabeca(GLfloat x, GLfloat y)
{

    glPushMatrix();
    if(jogador){
        DesenhaCirc(rCabeca, 0.212,	0.52, 0.736);

        glTranslatef(0, rCabeca, 0);
        DesenhaCirc(rNariz, 0.212,	0.52, 0.736);       
    }
    else
    {
        DesenhaCirc(rCabeca, 0.472,	0.664, 0.332);

        glTranslatef(0, rCabeca, 0);
        DesenhaCirc(rNariz, 0.472,	0.664, 0.332);
    }


    glPopMatrix();

}


void Lutador::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2)
{
    glPushMatrix();

    // BRAÇO
    glTranslatef(x, 0, 0);
    glRotatef(theta1, 0, 0, 1);
    DesenhaRect(bracoHeight, bracoWidth, 0.472, 0.664, 0.332);
 
    // ANTEBRAÇO 
    glTranslatef(0, bracoHeight, 0);
    glRotatef(theta2, 0, 0, 1);
    DesenhaRect(bracoHeight, bracoWidth, 0.472,	0.664, 0.332);

    // MAO
    glTranslatef(0, bracoHeight + rMao, 0);
    DesenhaCirc(rMao, 0.656, 0.056,0.104);

    glPopMatrix();
}

void Lutador::DesenhaLutador(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glRotatef(gGiro, 0, 0, 1);

    
    DesenhaBraco(rCabeca, y, gThetaDireito1, gThetaDireito2);
    DesenhaBraco(-rCabeca, y, gThetaEsquerdo1, gThetaEsquerdo2);

    DesenhaCabeca(x, y);

    glPopMatrix();
}



//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

    GLfloat angle2 = angle * (3.14/180);

    GLfloat xl = (cos(angle2) * x) - (y * sin(angle2));
    GLfloat yl = (sin(angle2) * x) + (y * cos(angle2));

    xOut = xl;
    yOut = yl;    

}

//Função pra ver aonde tá apontando o nariz
void DirecaoNariz(GLfloat raio, GLfloat angulo, GLfloat gx, GLfloat gy, GLfloat &x, GLfloat &y, GLfloat dy)
{
    
    GLfloat xOut;
    GLfloat yOut;
 
    GLfloat xAux = 0;
    GLfloat yAux = dy;

    RotatePoint(xAux, yAux, angulo, xOut, yOut);
  //  printf("angulo %0.2f  \n", angulo);

    x = xOut + gx;
    y = yOut + gy;

}
void Lutador::Gira(GLfloat inc)
{
    if(inc > 0)
    {
        gGiro++;
        if(gGiro > 360){
            gGiro = 1;
        }

    }
    else{
        gGiro--;
        if(gGiro < 0){
            gGiro = 359;
        }
    }


}
void Lutador::Anda(GLfloat dY)
{     
    GLfloat xOut;
    GLfloat yOut;
 
    DirecaoNariz(rCabeca, gGiro, gX, gY, xOut, yOut, dY);

    gX = xOut;
    gY = yOut;
}

GLfloat DistanciaPontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    return distanciaPontos;
}

bool Lutador::AcertouCabeca(GLfloat inimigox, GLfloat inimigoy, int braco)
{

    GLfloat angulo1;
    GLfloat angulo2;
    GLfloat distBraco;
       

    if(braco == 1)
    {
        angulo1 = gThetaDireito2;
        angulo2 = gThetaDireito1;
        distBraco = rCabeca;
    }

    else
    {
        angulo1 = gThetaEsquerdo2;
        angulo2 = gThetaEsquerdo1;
        distBraco = -rCabeca;
    }

        GLfloat xOut;
        GLfloat yOut;
    
        GLfloat xAux = 0;
        GLfloat yAux = rMao + bracoHeight;

        GLfloat distanciaSoco =  rMao + rCabeca;            


        RotatePoint(xAux, yAux, angulo1, xOut, yOut);

        xAux = xOut;
        yAux = yOut + bracoHeight;

        RotatePoint(xAux, yAux, angulo2, xOut, yOut);

        xAux = xOut + distBraco;
        yAux = yOut;

        RotatePoint(xAux, yAux, gGiro, xOut, yOut);    

        xAux = xOut + gX;
        yAux = yOut + gY;

        GLfloat distanciaPontos =  DistanciaPontos(xAux, yAux, inimigox, inimigoy);            

      //  printf("Distancia Soco %0.2f  \n", distanciaSoco);
      //  printf("Distancia Pontos %0.2f  \n", distanciaPontos);

    if(distanciaPontos < distanciaSoco){
        return true;
    }
    
    return false;
}

bool Lutador::VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2){
 
    GLfloat xOut;
    GLfloat yOut;

    DirecaoNariz(rCabeca, gGiro, gX, gY, xOut, yOut, dY);

    GLfloat yColisaoLutador = gY + dY + (rCabeca * 3);
    GLfloat xColisaoLutador = gX + (rCabeca * 3);

    GLfloat distanciaPontos = DistanciaPontos(xOut, yOut, xLutador2, yLutador2);
    GLfloat distancia = rCabeca * 3.5;

    yArena = (yArena / 2) - rCabeca;
    xArena = (xArena / 2) - rCabeca;

    if(yOut > (yArena))
        return false;
    
    if(yOut < -(yArena))
        return false;

    if(xOut > (xArena))
        return false;
    
    if(xOut < -(xArena))
        return false;

    if(distanciaPontos < distancia){
        return false;
    }
    else{
        return true;
    } 

    return true;
}

void Lutador::SocaBracoDireito(GLfloat angulo1, GLfloat angulo2){
    gThetaDireito1 = angulo1;
    gThetaDireito2 = angulo2;

}


void Lutador::SocaBracoEsquerdo(GLfloat angulo1, GLfloat angulo2){
    gThetaEsquerdo1 = angulo1;
    gThetaEsquerdo2 = angulo2;
}

bool Lutador::Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, GLfloat inimigox, GLfloat inimigoy){
    
    GLfloat angulo1 = thetaInicial2 + ((90 * distanciaPercorrida)/distanciaTotal);
    GLfloat angulo2 = thetaInicial1 - ((60 * distanciaPercorrida)/distanciaTotal);

    //DIREITO
    if(braco == 1){
        SocaBracoDireito(angulo1, angulo2);
        SocaBracoEsquerdo(thetaInicial1, thetaInicial2);

    }
    //ESQUERDO
    else if(braco == 2){
        SocaBracoEsquerdo(-angulo1, - angulo2);
        SocaBracoDireito(thetaInicial2, thetaInicial1);
    }

    bool fezPonto = AcertouCabeca(inimigox, inimigoy, braco);
    return fezPonto;
}


void Lutador::ParaDeSocar()
{
    SocaBracoEsquerdo(135, 225);
    SocaBracoDireito(225, 135);

}

GLfloat Lutador::GetX(){
    return gX;
}

GLfloat Lutador::GetY(){
    return gY;
}

GLfloat Lutador::GetXColisao(){
    GLfloat colisao = gX + (rCabeca * 3);
    return gX;
}

GLfloat Lutador::GetYColisao(){
    GLfloat colisao = gY + (rCabeca * 3);
    return gY;
}

GLfloat CalculaCoeficienteCabecas(GLfloat gXLutador, GLfloat gYLutador, GLfloat gX, GLfloat gY){

    GLfloat deltaX = abs(gXLutador - gX);
    GLfloat deltaY = abs(gYLutador - gY);

    GLfloat tangente = deltaX/deltaY;
    GLfloat angulo = (atan (tangente) * 180 / 3.14);

    if(gY > gYLutador && gXLutador > gX)
    {
        angulo = 180 + angulo;
    }
    
    else if(gY > gYLutador && gX > gXLutador)
    {
        angulo = 90 + angulo;
    }
    
    else if(gX == gXLutador && gY > gYLutador)
    {
        angulo = 180 + angulo;
    }
    
    else if(gYLutador > gY && gXLutador > gX)
    {
        angulo = 360 - angulo;
    }
    
    else if(gYLutador ==  gY && gXLutador > gX)
    {
        angulo = 180 + angulo;
    }

    return angulo;
}

void Lutador::GiraSozinho(GLfloat inc, GLfloat xLutador, GLfloat yLutador)
{
    GLfloat anguloLutador = CalculaCoeficienteCabecas(xLutador, yLutador, gX, gY);

    gGiro = anguloLutador;
}
