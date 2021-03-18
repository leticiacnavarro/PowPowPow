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
    glColor3f(1.0, 1, 1.0);

    while(*tmpStr){
        glutBitmapCharacter(fonte, *tmpStr);
        tmpStr++;
    }
}

void Menu::DesenhaPlacar(GLint pontosLutador, GLint pontosBot)
{
    glPushMatrix();
        static char str[1000];
        char *temp;
        sprintf(str, "%d / %d", pontosLutador, pontosBot);
        temp = str;

        DesenhaTexto(-(gX/2) + 10, - (gY/2) + 10, temp);
    glPopMatrix();

}

void Menu::DesenhaFinalJogo(bool ganhou)
{
    glPushMatrix();
        static char str[1000];
        char *temp;
        if(ganhou)
        {
           sprintf(str, "VOCE GANHOU!!");
        }
        else
        {
           sprintf(str, "VOCE PERDEU TROXA!!");
        }
        temp = str;

        DesenhaTexto(0, 0, temp);
    glPopMatrix();

}