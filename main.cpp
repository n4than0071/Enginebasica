#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>


#include "fonte.h"
#include "obj.h"

using namespace std;

bool isEven(int Integer)
{
    if (Integer % 2 == 0){
        return true;}
    return false;
};
// menor que < // maior que >



struct line{
    int x0, x1, y0, y1;
};
struct RGBA{
    int Red, Green, Blue, Alpha;
};
struct Coord{
    float X, Y, Z;
};
struct CoordScreen{
    float X, Y;
};
struct lines{
    CoordScreen a, b;
};

float Rad(float Angulo){return Angulo * M_PI / 180.0f;}
Coord CalcRot3D(Coord XYZ,float RadX,float RadY,float RadZ){
    float x = XYZ.X; float y = XYZ.Y; float z = XYZ.Z;

    float y1 = y * cos(RadX) - z * sin(RadX);
    float z1 = y * sin(RadX) + z * cos(RadX);

    y = y1;
    z = z1;

    // Y
    float x1 = x * cos(RadY) + z * sin(RadY);
    float z2 = -x * sin(RadY) + z * cos(RadY);

    x = x1;
    z = z2;

    // Z
    float x2 = x * cos(RadZ) - y * sin(RadZ);
    float y2 = x * sin(RadZ) + y * cos(RadZ);

    x = x2;
    y = y2;

return {x, y, z};};

class Fonte{
    private:
        SDL_Renderer* renderer;
        string texto;
        RGBA corText;
        int sizeWidth;
        int sizeHeight;
        CoordScreen XY;

    public:
        Fonte( SDL_Renderer* Renderer, string Texto, RGBA CorText, int SizeWidth, int SizeHeight, CoordScreen xY){
            renderer = Renderer;
            texto = Texto;
            corText = CorText;
            sizeWidth = SizeWidth;
            sizeHeight = SizeHeight;
            XY = xY;
        }
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

            void Text()
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
};

class Objeto{
    public:
        bool Aparece;

        vector<Vertices> ObjV;
        vector<Face> ObjF;

        RGBA corObjeto;

        void Criar( bool Show, Coord xyzObj, float RotacaoY, float RotacaoX, float RotacaoZ, float Size, RGBA corObj, int Obj)
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
                case 3:
                {
                    for (size_t i = 0; i < std::size(Cubo_vertices); i++)
                    {
                        Coord XYZV = CalcRot3D({Cubo_vertices[i].X, Cubo_vertices[i].Y, Cubo_vertices[i].Z},Rad(RotacaoX),Rad(RotacaoY),Rad(RotacaoZ));
                        Vertices novoPonto = {
                            xyzObj.X + XYZV.X * Size,

                            xyzObj.Y + XYZV.Y * Size,

                            xyzObj.Z + XYZV.Z * Size
                        };

                        ObjV.push_back(novoPonto);
                    };

                    for (size_t i = 0; i < std::size(Cubo_Faces); i++)
                    {
                        ObjF.push_back(Cubo_Faces[i]);
                    };
                    
                    break;
                };
            };
        };
    };

class Camera
    {
    private:
        Coord Posicao;
        int Fov;
        int Rotacao;
        int L;
        int A;

    public:
        Camera(Coord posicao, int fov, int rotacao, int l, int a)
        {
            Posicao = posicao;
            Fov = fov;
            Rotacao = rotacao;
            L = l;
            A = a;
        }
            
        CoordScreen Projetar(Coord object_Vertice){
            float aspect = static_cast<float>(L) / A;

            float limiteY = object_Vertice.Z * tan((Fov / 2.0f) * M_PI / 180.0f);

            float limiteX = limiteY * aspect;

            float porcentagemX = object_Vertice.X / limiteX;
            float porcentagemY = object_Vertice.Y / limiteY;

            float screenX = (L / 2.0f) + porcentagemX * (L / 2.0f);

            float screenY = (A / 2.0f) - porcentagemY * (A / 2.0f);

            return { screenX, screenY };

        };
    };


int main(int argc, char* argv[])
{
    int width = 1280;
    int height = 720;
    

    // 1. Inicializa o screenSize de vídeo da SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Erro ao iniciar SDL: %s", SDL_GetError());
        return 1;
    };

    // 2. Cria a janela
    SDL_Window* janela = SDL_CreateWindow(
        "Micro Engine",
        width,
        height,
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
    
    float rotX = 0;//provisorio
    float rotY = 0;//provisorio
    float rotZ = 0;//provisorio

    Objeto Objeto1;
    Camera Camera1({0,0,0}, 70, 0, width, height);
        
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

                if (evento.key.key == SDLK_V && !evento.key.repeat)
                {
                    Objeto1.Aparece = !Objeto1.Aparece;
                };
                if (evento.key.key == SDLK_KP_4 && !evento.key.repeat)
                {
                    rotX += 15;
                };
                if (evento.key.key == SDLK_KP_6 && !evento.key.repeat)
                {
                    rotX -= 15;
                }
                if (evento.key.key == SDLK_KP_8 && !evento.key.repeat)
                {
                    rotY += 15;
                };
                if (evento.key.key == SDLK_KP_2 && !evento.key.repeat)
                {
                    rotY -= 15;
                }
                if (evento.key.key == SDLK_KP_7 && !evento.key.repeat)
                {
                    rotZ += 15;
                };
                if (evento.key.key == SDLK_KP_9 && !evento.key.repeat)
                {
                    rotZ -= 15;
                }
                if (evento.key.key == SDLK_KP_5 && !evento.key.repeat)
                {
                    rotZ = 0;rotY = 0;rotX = 0;
                }

            }
        }

        Objeto1.Criar( true, {0, 0, 100}, rotX, rotY, rotZ, 10, {255, 255, 255, 255}, 3);

        // DESENHO

        // Cor do fundo
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Limpa a tela inteira usando a cor atual
        SDL_RenderClear(renderer);

        if (Objeto1.Aparece)
        {
            vector<SDL_Vertex> vertices;
            vector<int> indices;
            vector<float> distancia;

            // ==========================
            // CONVERTE NOSSOS VÉRTICES
            // PARA VÉRTICES DO SDL
            // ==========================

             

            for (Vertices ponto : Objeto1.ObjV)
            {
                CoordScreen tela = Camera1.Projetar(
                    {ponto.X,ponto.Y,ponto.Z}
                );

                SDL_Vertex vertice;

                vertice.position.x = tela.X;
                vertice.position.y = tela.Y;

                Objeto1.corObjeto.Red -= 31;
                Objeto1.corObjeto.Green -= 31;
                Objeto1.corObjeto.Blue -= 31;



                vertice.color = SDL_FColor{
                    Objeto1.corObjeto.Red   / 255.0f,
                    Objeto1.corObjeto.Green / 255.0f,
                    Objeto1.corObjeto.Blue  / 255.0f,
                    Objeto1.corObjeto.Alpha / 255.0f
                };


                vertice.tex_coord = {
                    0.0f,
                    0.0f
                };

                distancia.push_back(ponto.Z);
                vertices.push_back(vertice);
            }


            // ==========================
            // CONVERTE AS FACES
            // EM ÍNDICES
            // ==========================

            for (Face face : Objeto1.ObjF)
            {
                indices.push_back(face.a);
                indices.push_back(face.b);
                indices.push_back(face.c);
            }


            // ==========================
            // DESENHA
            // ==========================

            SDL_RenderGeometry(
                renderer,
                nullptr,

                vertices.data(),
                static_cast<int>(vertices.size()),

                indices.data(),
                static_cast<int>(indices.size())
            );
        }

        Fonte text1(renderer, "Engine 0.0.1", {255, 255, 255, 255}, 1, 1, {5, 5});

        text1.Text();


        // Muda a cor para desenhar o ponto 0
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        
        SDL_FRect ponto = {
        static_cast<float>((width / 2) - 2), 
        static_cast<float>((height / 2) - 2),
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