#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "lutador.h"
#include "iniciacao.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.01

//Key status
int keyStatus[256];

Iniciacao iniciacao;

Lutador lutador;
Lutador bot;

// Window dimensions
GLint Width;
GLint Height;

void renderScene(void)
{
     // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    
    lutador.Desenha();
    bot.Desenha();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
   
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-(Width/2),     // X coordinate of left edge             
            (Width/2),     // X coordinate of right edge            
            -(Height/2),     // Y coordinate of bottom edge             
            (Height/2),     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

void idle(void)
{

    double inc = INC_KEYIDLE;

    //Treat keyPress
    if(keyStatus[(int)('a')])
    {

    }
    if(keyStatus[(int)('d')])
    {

    }
    
    
    glutPostRedisplay();
}

void Inicializa()
{
    iniciacao.IniciaArena(Width, Height);
    iniciacao.IniciaLutadores(lutador, bot);    
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    Inicializa();

    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Pow Pow Pow");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    
    init();
 
    glutMainLoop();
 
    return 0;
}
