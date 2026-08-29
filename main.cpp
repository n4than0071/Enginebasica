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
}
// menor que < // maior que >

struct line{
    int x0, x1, y0, y1;
};//  int x0, x1, y0, y1
struct Obj{
    bool Aparece;
    int x, y, z;
    int size;
    int r,g,b;
};

class Sys{
    public:
        int width;
        int height;
        int x, y, z;
        int r, g, b, a;
        bool criarGrid;
        vector<line> grid;
        

        void screenResolution(int L,int A)// largura / altura
        {
            width = L;
            height = A;
        };

        void Ui(bool Grid,int Red,int Green,int Blue,int Alpha)
        {
            criarGrid = Grid;
            r = Red;
            g = Green;
            b = Blue;
            a = Alpha;

            if(isEven(height)){
                y = height / 2;
            };
            if(isEven(width)){
                x = width / 2;
            };

            //grid
            if (criarGrid){
                for (int i = x; i < width; i += 50)
                {   // horizontal depois do 0 pra direita + ->
                    line novalinha = {i, i, 0, height};
                    grid.push_back(novalinha);
                }
                for (int t = x; t > 0; t -= 50)
                {   // horizontal antes do 0 pra esquerda <- +
                    line novalinha = {t, t, 0, height};
                    grid.push_back(novalinha);
                }
                for (int d = y; d < height; d += 50)
                {   // vertical depois de  0 pra baixo 
                    line novalinha = {0, width, d, d};
                    grid.push_back(novalinha);
                }
                for (int h = y; h > 0; h -= 50)
                {   // vertical antede de 0 pra cima
                    line novalinha = {0, width, h, h};
                    grid.push_back(novalinha);
                }
            };

        };

};


int main(int argc, char* argv[])
{

    Sys Sistema;

    Sistema.screenResolution(1000,800);
    Sistema.Ui(true, 0, 0, 255, 255);
    

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