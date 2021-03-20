#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "menu.h"

void DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    float halfWidth = width/2;
    glPointSize(3);
    glColor3f (R, G, B);
    glBegin(GL_POINTS);
        glVertex2f(-halfWidth, 0);
        glVertex2f(halfWidth, 0);
        glVertex2f(halfWidth, height);
        glVertex2f(-halfWidth, height);
    glEnd();
}

void Menu::DesenhaTexto(GLfloat x, GLfloat y, char *tmpStr)
{
    glRasterPos2f(x, y);

    while(*tmpStr){
        glColor3f(0, 0, 0);
        glutBitmapCharacter(fonte, *tmpStr);
        tmpStr++;
    }
}

void Menu::DesenhaPlacar(GLint pontosLutador, GLint pontosBot)
{
        static char str[1000];
        char *temp;
        sprintf(str, "%d / %d", pontosLutador, pontosBot);
        temp = str;

        DesenhaTexto(-(gX/2) + 10, - (gY/2) + 10, temp);

}

void Menu::DesenhaFinalJogo(bool ganhou)
{
        static char str[1000];
        char *temp;
        if(ganhou)
        {
           sprintf(str, "JOGADOR GANHOU!!");
        }
        else
        {
           sprintf(str, "BOT GANHOU!!");
        }
        temp = str;

        DesenhaTexto(0, 0, temp);

}