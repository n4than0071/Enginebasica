#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include <iostream>
#include <vector>

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

        void screenResolution(int L,int A)// largura / altura
        {
            width = L;
            height = A;
        };

        void Ui(bool Grid,RGBA corGrid)
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
            };
        };

        void Text(RGBA corText,int sizeWidth,int sizeHeight,int Zbuffer,CoordScreen XY)// Cor do texto, Tamanho largura, tamanho altura, posição na camada, x,y
        {
            r = corText.Red;
            g = corText.Green;
            b = corText.Blue;
            a = corText.Alpha;

            sizeW  = sizeWidth;
            sizeH  = sizeHeight;
            zbuffer  = Zbuffer;

            x = XY.X;
            y = XY.Y;
   

        };

        void Objeto(bool Show,Coord xyzObj ,int Size ,RGBA corObj)// mostra objeto, coordenadas x,y,z, tamanho, cor R,G,B,A
        {   
            Aparece = Show;
            size = Size;

            r = corObj.Red;
            g = corObj.Green;
            b = corObj.Blue;
            a = corObj.Alpha;

            x = xyzObj.X;
            y = xyzObj.Y;
            z = xyzObj.Z;

            

        };

};


int main(int argc, char* argv[])
{

    Sys Sistema;

    Sistema.screenResolution(1000,800);
    Sistema.Ui(true, {0, 0, 255, 255});
    

    // 1. Inicializa o sistema de vídeo da SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Erro ao iniciar SDL: %s", SDL_GetError());
        return 1;
    };

    // 2. Cria a janela
    SDL_Window* janela = SDL_CreateWindow(
        "Micro Roguelike",
        Sistema.width,
        Sistema.height,
        0
    );

    if (!janela)
    {
        SDL_Log("Erro ao criar janela: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    };

    // 3. Cria o renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(janela, nullptr);

    if (!renderer)
    {
        SDL_Log("Erro ao criar renderer: %s", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 1;
    };

    bool rodando = true;
        
    while (rodando)
    {
        // EVENTOS
        SDL_Event evento;

        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_EVENT_QUIT)
            {
                rodando = false;
            }

            // presionar para desativar grid

            if (evento.type == SDL_EVENT_KEY_DOWN)
            {
                if (evento.key.key == SDLK_G && !evento.key.repeat)
                {
                    Sistema.criarGrid = !Sistema.criarGrid;
                }
            }
        }


        // DESENHO

        // Cor do fundo
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Limpa a tela inteira usando a cor atual
        SDL_RenderClear(renderer);
    
        // Cria grid caso true
        if (Sistema.criarGrid)
        {
            SDL_SetRenderDrawColor(renderer, Sistema.r, Sistema.g, Sistema.b, Sistema.a);

            for (line linha : Sistema.grid)
            {
                
                SDL_RenderLine(
                    renderer,
                    linha.x0,
                    linha.y0,
                    linha.x1,
                    linha.y1);
            };
        };
        
        // Muda a cor para desenhar o ponto 0
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        SDL_FRect ponto = {
        static_cast<float>(Sistema.x - 2), 
        static_cast<float>(Sistema.y - 2),
        5, 5
        };

        SDL_RenderFillRect(renderer, &ponto);

        // Mostra na tela tudo que desenhamos
        SDL_RenderPresent(renderer);

    }
    // LIMPEZA
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}