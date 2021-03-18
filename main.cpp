#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>

#include "lutador.h"
#include "iniciacao.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.1

//Key status
int keyStatus[256];

Iniciacao iniciacao;

Lutador lutador;
Lutador bot;

// Window dimensions
GLint Width;
GLint Height;

GLint pontoCentral;

//Pontuacao
GLint pontoLutador;
GLint pontoBot;


// Bot socando pow pow pow
GLint distanciaSoco = 0;
GLint distanciaSocoTotal = 100;
GLint braco = 1;
GLboolean parouDeSocar = true;
int atingido = 0;
static char str[1000];
void * font = GLUT_BITMAP_9_BY_15;
void ImprimePlacar(GLfloat x, GLfloat y)
{
glColor3f(1.0, 1.0, 1.0);
//Cria a string a ser impressa
char *tmpStr;
sprintf(str, "Atingido: %d", atingido );
//Define a posicao onde vai comecar a imprimir
glRasterPos2f(x, y);
//Imprime um caractere por vez
tmpStr = str;
while( *tmpStr ){
glutBitmapCharacter(font, *tmpStr);
tmpStr++;
}
}
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

void movimentaBot(double inc)
{
    if(distanciaSoco <= 0)
    {
        distanciaSoco = 0;
        parouDeSocar = true;
    }

    cout << distanciaSoco << endl;
    cout << parouDeSocar << endl;


    if(inc < 1){
        inc = 1;
    }
    if(bot.VerificaSePode(inc, Width, Height, lutador.GetX(), lutador.GetY())){
        bot.Anda(inc);
    }
    else
    {
        //distanciaSoco += inc;
        bool acertou = bot.Soca(distanciaSocoTotal, distanciaSoco, braco, lutador.GetX(), lutador.GetY());
        if(acertou)
        {
            if(parouDeSocar)
            {
                pontoLutador++;
                parouDeSocar = false;
            }
            distanciaSoco -= inc;
        }
        else
        {
            if(parouDeSocar)
            {
                distanciaSoco += inc;
            }
            else
            {
                distanciaSoco -= inc;
            }
        }
    }
    bot.GiraSozinho(inc, lutador.GetX(), lutador.GetY());
}

void idle(void)
{
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    double inc = INC_KEY * timeDiference * INC_KEYIDLE;

    movimentaBot(inc);

    //Treat keyPress
    if(keyStatus[(int)('w')])
    {
        if(lutador.VerificaSePode(inc, Width, Height, bot.GetX(), bot.GetY()))
        {
            lutador.Anda(inc);
        }
    }
    if(keyStatus[(int)('s')])
    {
        if(lutador.VerificaSePode(-inc, Width, Height, bot.GetX(), bot.GetY()))
        {
            lutador.Anda(-inc);
        }
    }  
    if(keyStatus[(int)('a')])
    {
        lutador.Gira(inc);
    }
    if(keyStatus[(int)('d')])
    {
        lutador.Gira(-inc);
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(state == 0)
    {
        pontoCentral = x;
    }
    else
    {
        pontoCentral = 0;
        lutador.ParaDeSocar();
    }
}

void mouseArrasta(int x, int y)
{
    GLfloat distanciaPercorrida = abs(x - pontoCentral);

    if(distanciaPercorrida > (Width/2))
    {
        distanciaPercorrida = (Width/2);
    }
  
    if(x > pontoCentral){

        lutador.Soca(Width/2, distanciaPercorrida, 1, bot.GetX(), bot.GetY());
    }
    else if(x < pontoCentral)
    {
        lutador.Soca(Width/2, distanciaPercorrida, 2, bot.GetX(), bot.GetY());

  
    }
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
    glutMotionFunc(mouseArrasta);
    glutMouseFunc(mouse);
   
    init();
 
    glutMainLoop();
 
    return 0;
}
