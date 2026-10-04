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