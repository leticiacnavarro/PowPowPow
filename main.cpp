#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>

#include "lutador.h"
#include "iniciacao.h"
#include "menu.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.1

//Key status
int keyStatus[256];

Menu menu;

Iniciacao iniciacao;

Lutador lutador;
Lutador bot;

// Window dimensions
GLint Width;
GLint Height;

GLint WidthHalf;
GLint HeightHalf;

GLint pontoCentral;

//Pontuacao
GLint pontoLutador;
GLint pontoBot;


//Lutador Socando pow pow pow
GLboolean parouDeSocarLutador = true;
GLboolean botaoCerto;


// Bot socando pow pow pow
GLint distanciaSoco = 0;
GLint distanciaSocoTotal = 25;
GLint braco = 1;
GLboolean parouDeSocarBot = true;

// Tipo Jogo

bool modoTreino;


void renderScene(void)
{
    
     // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    if(pontoLutador < 10 && pontoBot < 10)
    {    
        menu.DesenhaPlacar(pontoLutador, pontoBot);
        lutador.Desenha();
        bot.Desenha();
    }
    else if(pontoLutador >= pontoBot)
    {
        menu.DesenhaFinalJogo(true);
    }
    else if(pontoBot > pontoLutador)
    {
        menu.DesenhaFinalJogo(false);
    }

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
    glClearColor(0.692,	0.852,	0.988, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-WidthHalf,     // X coordinate of left edge             
            WidthHalf,     // X coordinate of right edge            
            -HeightHalf,     // Y coordinate of bottom edge             
            HeightHalf,     // Y coordinate of top edge             
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
        parouDeSocarBot = true;

        if(braco == 1){
            braco = 2;
        }
        else if(braco == 2){
            braco = 1;
        }
    }

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
            if(parouDeSocarBot)
            {
                pontoBot++;
                parouDeSocarBot = false;
            }
            distanciaSoco -= inc;
        }
        else
        {
            if(parouDeSocarBot)
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

bool VerificaSeEstaAndando()
{
    if(keyStatus[(int)('w')])
    {
        return false;
    }
    if(keyStatus[(int)('s')])
    {
        return false;
    }  
    if(keyStatus[(int)('a')])
    {            
        return false;
    }
    if(keyStatus[(int)('d')])
    {
        return false;
    }

    return true;
} 

void idle(void)
{
    if(pontoLutador < 10 && pontoBot < 10)
    {    
        static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
        GLdouble currentTime, timeDiference;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        timeDiference = currentTime - previousTime;
        previousTime = currentTime;

        double inc = INC_KEY * timeDiference * INC_KEYIDLE;

    //    for(int i = 0; i < 90000000; i++);

        if(!modoTreino)
        {
           movimentaBot(inc);
        }

        //Treat keyPress
        if(keyStatus[(int)('w')])
        {
            if(lutador.VerificaSePode(inc, Width, Height, bot.GetX(), bot.GetY()))
            {
                        lutador.ParaDeSocar();

                lutador.Anda(inc);

            }
        }
        if(keyStatus[(int)('s')])
        {
            if(lutador.VerificaSePode(-inc, Width, Height, bot.GetX(), bot.GetY()))
            {
                        lutador.ParaDeSocar();

                lutador.Anda(-inc);

            }
        }  
        if(keyStatus[(int)('a')])
        {    
                    lutador.ParaDeSocar();
        
            lutador.Gira(inc);
        }
        if(keyStatus[(int)('d')])
        {
                    lutador.ParaDeSocar();

            lutador.Gira(-inc);
        }
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{


    if(state == 0)
    {
        pontoCentral = x;
        if(button == 0)
        {
            botaoCerto = true;
        }
    }
    else
    {
        botaoCerto = false;

        pontoCentral = 0;
        lutador.ParaDeSocar();
    }
}

void mouseArrasta(int x, int y)
{
    if(botaoCerto)
    {
        if(VerificaSeEstaAndando())
        {
        GLfloat distanciaPercorrida = abs(x - pontoCentral);

        if(distanciaPercorrida > WidthHalf)
        {
            distanciaPercorrida = WidthHalf;
        }
        
        if(x > pontoCentral){

            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 1, bot.GetX(), bot.GetY());
            if(acertou)
            {
                if(parouDeSocarLutador)
                {
                    pontoLutador++;
                    parouDeSocarLutador = false;
                }
            }
            else{
                parouDeSocarLutador = true;
            }
        }
        else if(x < pontoCentral)
        {
            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 2, bot.GetX(), bot.GetY());
            if(acertou)
            {
                if(parouDeSocarLutador)
                {
                    pontoLutador++;
                    parouDeSocarLutador = false;
                }
            }
            else{
                parouDeSocarLutador = true;
            }
    
        }
        }
    }


}

void Inicializa()
{
    iniciacao.IniciaArena(Width, Height, WidthHalf, HeightHalf);
    iniciacao.IniciaLutadores(lutador, bot);
    iniciacao.TipoJogo(modoTreino);

    menu.Iniciacao(Width, Height);   
     
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
