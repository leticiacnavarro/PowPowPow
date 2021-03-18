#include "iniciacao.h"
#include "tinyxml/tinyxml.h"

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
}

void Iniciacao::ProcessaLutadores(TiXmlElement *lutador1, TiXmlElement *lutador2)
{    
    if(strcmp (lutador1->Attribute("fill"),"red") == 0)
    {
        gXLutador = atoi(lutador2->Attribute("cx")) - width;
        gYLutador = atoi(lutador2->Attribute("cy")) - height;
        rCabecaLutador = atoi(lutador2->Attribute("r"));

        
        gXBot = atoi(lutador1->Attribute("cx")) - width;
        gYBot = atoi(lutador1->Attribute("cy")) - height;
        rCabecaBot = atoi(lutador1->Attribute("r"));
    }
    else if(strcmp (lutador2->Attribute("fill"),"red") == 0)
    {
        gXLutador = atoi(lutador1->Attribute("cx")) - width;
        gYLutador = atoi(lutador1->Attribute("cy")) - height;
        rCabecaLutador = atoi(lutador1->Attribute("r"));

        gXBot = atoi(lutador2->Attribute("cx")) - width;
        gYBot = atoi(lutador2->Attribute("cy")) - height;
        rCabecaBot = atoi(lutador2->Attribute("r"));
    }           
}

void Iniciacao::IniciaLutadores(Lutador &lutador, Lutador &bot)
{
    
    lutador.Iniciacao(gXLutador, gYLutador, 0, rCabecaLutador);
    bot.Iniciacao(gXBot, gYBot, 0, rCabecaBot);
}

void Iniciacao::IniciaArena(GLint &widthArena, GLint &heightArena)
{
    widthArena = width;
    heightArena = height;
}
void Iniciacao::ProcessaArquivo(string nomeArquivo)
{
    // /home/leticia/Downloads/arena_1.svg

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

            }
            cout << "Deu bom abrindo o arquivo!" << endl;

        }

	}
	else
	{
        cout << "Vish, deu ruim abrindo esse SVG D: \n" << endl;
	}

}