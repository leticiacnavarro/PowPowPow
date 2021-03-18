#ifndef INICIACAO_H
#define	INICIACAO_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "tinyxml/tinyxml.h"
#include "lutador.h"

using namespace std;

class Iniciacao
{

    // Lutador

    GLfloat gXLutador;
    GLfloat gYLutador;
    GLfloat gGiroLutador;
    GLfloat rCabecaLutador;

    // Bot

    GLfloat gXBot;
    GLfloat gYBot;
    GLfloat gGiroBot;
    GLfloat rCabecaBot;

    // Arena

    GLfloat width;
    GLfloat height;
 
    GLfloat widthHalf;
    GLfloat heightHalf;


private:
    void ProcessaArena(TiXmlElement *arena);
 
    void ProcessaLutadores(TiXmlElement *lutador1, TiXmlElement *lutador2);
  
    void ProcessaBot(TiXmlElement *arena);
 
    string ObtemNomeArquivo();
  
    void ProcessaArquivo(string nomeArquivo);

public:
    Iniciacao()
    {
        ProcessaArquivo(ObtemNomeArquivo());
    }
    
    void IniciaLutadores(Lutador &lutador, Lutador &bot);

    void IniciaArena(GLint &widthArena, GLint &heightarena);

};

#endif	/* ROBO_H */
