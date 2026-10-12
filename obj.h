#pragma once
#include <array>

struct Vertices
{
    float X, Y, Z;
};

struct Aresta
{
    int a, b;
};

struct Face
{
    int a, b, c;
};


// ==========================
// QUADRADO
// ==========================

Vertices Quadrado_Vertices[4] = {
    {0, 0, 0}, // 0 ----- 1
    {1, 0, 0}, // |       |
    {0, 1, 0}, // |       |
    {1, 1, 0}  // 2 ----- 3
};

Aresta Quadrado_Aresta[4] = {
    {0, 1},
    {0, 2},
    {2, 3},
    {1, 3}
};

// Quadrado = 2 triângulos
Face Quadrado_Faces[2] = {
    {0, 1, 2},
    {1, 3, 2}
};


// ==========================
// TRIÂNGULO
// ==========================

Vertices Triangulo_Vertices[3] = {
    {0.5f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 0.0f}
};

Aresta Triangulo_Aresta[3] = {
    {0, 1},
    {0, 2},
    {1, 2}
};

Face Triangulo_Faces[1] = {
    {0, 1, 2}
};


//cubo

Vertices Cubo_vertices[8] = {
    {1,1,1},
    {1,1,-1},
    {1,-1,1},
    {1,-1,-1},
    {-1,1,1},
    {-1,1,-1},
    {-1,-1,1},
    {-1,-1,-1}
};

Face Cubo_Faces[11] = {
    {5,1,3},
    {3,7,5},
    {1,0,2},
    {2,3,1},
    {2,0,6},
    {0,4,6},
    {6,4,7},
    {4,0,1},
    {1,5,4},
    {3,2,7},
    {7,6,2}
};