#include "iniciacao.h"
#include "tinyxml/tinyxml.h"
#include <math.h>

void Iniciacao::CalculaCoeficienteCabecas(){

    GLfloat deltaX = abs(gXLutador - gXBot);
    GLfloat deltaY = abs(gYLutador - gYBot);

    GLfloat tangente = deltaX/deltaY;
    GLfloat angulo = (atan (tangente) * 180 / 3.14);

    gGiroBot = angulo;
    gGiroLutador = angulo;

    //Bot
    if(gYBot > gYLutador && gXLutador > gXBot)
    {
        gGiroBot = 180 + gGiroBot;
    }
    
    else if(gYBot > gYLutador && gXBot > gXLutador)
    {
        gGiroBot = 90 + gGiroBot;
        gGiroLutador = 360 - gGiroLutador;
    }
    
    else if(gXBot == gXLutador && gYBot > gYLutador)
    {
        gGiroBot = 180 + gGiroBot;
    }
    
    else if(gYLutador > gYBot && gXLutador > gXBot)
    {
        gGiroBot = 360 - gGiroBot;
    }
    
    else if(gYLutador ==  gYBot && gXLutador > gXBot)
    {
        gGiroBot = 180 + gGiroBot;
    }

    // Lutador
    if(gYLutador > gYBot && gXBot > gXLutador)
    {
        gGiroLutador = 180 + gGiroLutador;
    }
    
    else if(gYLutador > gYBot && gXLutador > gXBot)
    {
        gGiroLutador = 90 + gGiroLutador;
        gGiroBot = 360 - gGiroBot;
    }
    
    else if(gXLutador == gXBot && gYLutador > gYBot)
    {
        gGiroLutador = 180 + gGiroLutador;
    }
    
    else if(gYBot > gYLutador && gXBot > gXLutador)
    {
        gGiroLutador = 360 - gGiroLutador;
    }
    
    else if(gYBot == gYLutador && gXBot > gXLutador)
    {
        gGiroLutador = 180 + gGiroLutador;
    }

}

string Iniciacao::ObtemNomeArquivo()
{
    string nomeArquivo;
    cout << "Insere o caminho do arquivo SVG aí fera: ";
    cin >> nomeArquivo; 

    // Só dando uma limpadinha né
    cout << flush; 
    return nomeArquivo;
}

void Iniciacao::ProcessaArena(TiXmlElement *arena)
{
    width = atoi(arena->Attribute("width"));
    height = atoi(arena->Attribute("height"));    

    widthHalf = width/2;
    heightHalf = height/2;
}

void Iniciacao::ProcessaLutadores(TiXmlElement *lutador1, TiXmlElement *lutador2)
{    
    if(strcmp (lutador1->Attribute("fill"),"red") == 0)
    {
        gXLutador = atoi(lutador2->Attribute("cx")) - widthHalf;
        gYLutador = - atoi(lutador2->Attribute("cy")) + heightHalf;
        rCabecaLutador = atoi(lutador2->Attribute("r"));

        
        gXBot = atoi(lutador1->Attribute("cx")) - widthHalf;
        gYBot = - atoi(lutador1->Attribute("cy")) + heightHalf;
        rCabecaBot = atoi(lutador1->Attribute("r"));
    }
    else if(strcmp (lutador2->Attribute("fill"),"red") == 0)
    {
        gXLutador = atoi(lutador1->Attribute("cx")) - widthHalf;
        gYLutador = - atoi(lutador1->Attribute("cy")) + heightHalf;
        rCabecaLutador = atoi(lutador1->Attribute("r"));

        gXBot = atoi(lutador2->Attribute("cx")) - widthHalf;
        gYBot = - atoi(lutador2->Attribute("cy")) + heightHalf;
        rCabecaBot = atoi(lutador2->Attribute("r"));
    } 

    CalculaCoeficienteCabecas();       
}

void Iniciacao::IniciaLutadores(Lutador &lutador, Lutador &bot)
{    
    lutador.Iniciacao(gXLutador, gYLutador, gGiroLutador, rCabecaLutador, false);
    bot.Iniciacao(gXBot, gYBot, gGiroBot, rCabecaBot, true);
}

void Iniciacao::IniciaArena(GLint &widthArena, GLint &heightArena)
{
    widthArena = width;
    heightArena = height;

}
void Iniciacao::ProcessaArquivo(string nomeArquivo)
{
    // /home/leticia/Downloads/arena_1.svg
    nomeArquivo = "/home/leticia/Downloads/arena_3.svg";
    // Passando de string pra char array pq se não dá ruim
    int n = nomeArquivo.length(); 
    char char_array[n + 1]; 
    strcpy(char_array, nomeArquivo.c_str());

    // Abrindo o arquivo
    TiXmlDocument doc(char_array);

    TiXmlElement *svg; 
    TiXmlElement *rect;
    TiXmlElement *circle1; 
    TiXmlElement *circle2; 


	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
        svg = doc.FirstChildElement("svg");
        if(svg)
        {
            rect = svg->FirstChildElement("rect");
            if(rect)
            {
                ProcessaArena(rect);
            }

            circle1 = svg->FirstChildElement("circle");
            circle2 = circle1->NextSiblingElement("circle");

            if(circle1 && circle2)
            {
                ProcessaLutadores(circle1, circle2);
            }
            cout << "Deu bom abrindo o arquivo!" << endl;

        }

	}
	else
	{
        cout << "Vish, deu ruim abrindo esse SVG D: \n" << endl;
	}

}