#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


#include "fonte.h"
#include "obj.h"

using namespace std;

bool isEven(int Integer)
{
    if (Integer % 2 == 0)
    {
        return true;
    }

    return false;
};
// menor que < // maior que >

struct line{
    int x0, x1, y0, y1;
};//  int x0, x1, y0, y1
struct RGBA{
    int Red, Green, Blue, Alpha;
};
struct Coord{
    int X, Y, Z;
};
struct CoordScreen{
    int X, Y;
};
struct lines{
    CoordScreen a, b;
};

class Sys{
    public:
        bool Aparece;
        bool criarGrid;

        int x, y, z;
        int xCam, yCam, zBuffer;
        int r, g, b, a;
        int sizeW, sizeH, zbuffer; 

        int size;
        int width;
        int height;

        vector<line> grid;
        vector<Coord> pontos;
        vector<lines> linhas;

        vector<Vertices> ObjV;
        vector<Face> ObjF;

        RGBA corObjeto;

        void screenResolution(int L,int A)// largura / altura
        {
            width = L;
            height = A;
        };

        // Cria uma grid na tela completamente desnecessario
        void UiGrid(bool Grid,RGBA corGrid)
        {
            criarGrid = Grid;
            r = corGrid.Red;
            g = corGrid.Green;
            b = corGrid.Blue;
            a = corGrid.Alpha;

            if(isEven(height)){
                y = height / 2;
            };
            if(isEven(width)){
                x = width / 2;
            };

            //grid
            grid.clear();
            if (criarGrid){
                for (int i = x; i < width; i += 50)
                {   // horizontal depois do 0 pra direita + ->
                    line novalinha = {i, i, 0, height};
                    grid.push_back(novalinha);
                }
                for (int t = x - 50; t > 0; t -= 50)
                {   // horizontal antes do 0 pra esquerda <- +
                    line novalinha = {t, t, 0, height};
                    grid.push_back(novalinha);
                }
                for (int d = y; d < height; d += 50)
                {   // vertical depois de  0 pra baixo 
                    line novalinha = {0, width, d, d};
                    grid.push_back(novalinha);
                }
                for (int h = y - 50; h > 0; h -= 50)
                {   // vertical antede de 0 pra cima
                    line novalinha = {0, width, h, h};
                    grid.push_back(novalinha);
                }

                SDL_SetRenderDrawColor(renderer, r, g, b, a);

                for (line linha : grid){
                    SDL_RenderLine(
                        renderer,
                        linha.x0,
                        linha.y0,
                        linha.x1,
                        linha.y1
                    );
                };
            };
        };

        int charToFonte(char letra)
        {
            letra = std::toupper(static_cast<unsigned char>(letra));

            switch (letra)
            {
                // Letras
                case 'A': return 0;
                case 'B': return 1;
                case 'C': return 10;
                case 'D': return 11;
                case 'E': return 2;
                case 'F': return 3;
                case 'G': return 12;
                case 'H': return 13;
                case 'I': return 4;
                case 'J': return 5;
                case 'K': return 14;
                case 'L': return 15;
                case 'M': return 6;
                case 'N': return 7;
                case 'O': return 16;
                case 'P': return 17;
                case 'Q': return 8;
                case 'R': return 9;
                case 'S': return 18;
                case 'T': return 19;
                case 'U': return 20;
                case 'V': return 21;
                case 'W': return 30;
                case 'X': return 31;
                case 'Y': return 22;
                case 'Z': return 23;

                // Números
                case '0': return 39;
                case '1': return 34;
                case '2': return 35;
                case '3': return 26;
                case '4': return 27;
                case '5': return 36;
                case '6': return 37;
                case '7': return 28;
                case '8': return 29;
                case '9': return 38;

                // Pontuação
                case '!': return 24;
                case '?': return 25;
                case ',': return 32;
                case '.': return 33;
                case '+': return 40;
                case '-': return 50;
                case '(': return 52;
                case ')': return 53;
                case '=': return 54;
                case '#': return 55;
                case '%': return 58;
                case '$': return 59;
                case '<': return 60;
                case '>': return 61;
                case ':': return 62;
                case ';': return 63;

                // Espaço
                case ' ': return -2;
            }

        return -1;
        };

        void Text( SDL_Renderer* renderer, string texto, RGBA corText, int sizeWidth, int sizeHeight, CoordScreen XY)
        {
            // Define a cor do texto
            SDL_SetRenderDrawColor(
                renderer,
                corText.Red,
                corText.Green,
                corText.Blue,
                corText.Alpha
            );

            int cursorX = XY.X;
            int cursorY = XY.Y;

            // Passa por cada letra do texto
            for (char letra : texto)
            {
                int simbolo = charToFonte(letra);

                // ESPAÇO
                if (simbolo == -2)
                {
                    cursorX += 11 * sizeWidth;
                    continue;
                }

                // Caractere que não existe na nossa fonte
                if (simbolo == -1)
                {
                    continue;
                }

                // Cada caractere possui 10 linhas
                for (int linha = 0; linha < 10; linha++)
                {
                    uint16_t bits = fonte[simbolo][linha];

                    // Cada linha possui 10 pixels
                    for (int coluna = 0; coluna < 10; coluna++)
                    {
                        // Descobre se aquele pixel é 0 ou 1
                        bool pixel = bits & (1 << (9 - coluna));

                        if (pixel)
                        {
                            SDL_FRect quadrado = {
                                static_cast<float>(
                                    cursorX + coluna * sizeWidth
                                ),

                                static_cast<float>(
                                    cursorY + linha * sizeHeight
                                ),

                                static_cast<float>(sizeWidth),
                                static_cast<float>(sizeHeight)
                            };

                            SDL_RenderFillRect(
                                renderer,
                                &quadrado
                            );
                        }
                    }
                }

                // Anda para a posição da próxima letra
                cursorX += 11 * sizeWidth;
            }
        };

        void Objeto(
            bool Show,
            Coord xyzObj,
            float Size,
            RGBA corObj,
            int Obj
        )
        {
            Aparece = Show;

            corObjeto = corObj;

            ObjV.clear();
            ObjF.clear();

            if (!Aparece)
            {
                return;
            }

            switch (Obj)
            {

                case 1:
                {
                    for (size_t i = 0; i < std::size(Quadrado_Vertices); i++)
                    {
                        Vertices novoPonto = {

                            xyzObj.X + Quadrado_Vertices[i].X * Size,

                            xyzObj.Y + Quadrado_Vertices[i].Y * Size,

                            xyzObj.Z + Quadrado_Vertices[i].Z * Size
                        };

                        ObjV.push_back(novoPonto);
                    }


                    for (size_t i = 0; i < std::size(Quadrado_Faces); i++)
                    {
                        ObjF.push_back(Quadrado_Faces[i]);
                    }

                    break;
                }

                case 2:
                {
                    for (size_t i = 0; i < std::size(Triangulo_Vertices); i++)
                    {
                        Vertices novoPonto = {

                            xyzObj.X + Triangulo_Vertices[i].X * Size,

                            xyzObj.Y + Triangulo_Vertices[i].Y * Size,

                            xyzObj.Z + Triangulo_Vertices[i].Z * Size
                        };

                        ObjV.push_back(novoPonto);
                    }

                    for (size_t i = 0; i < std::size(Triangulo_Faces); i++)
                    {
                        ObjF.push_back(Triangulo_Faces[i]);
                    }

                    break;
                };
            };
        };
    };