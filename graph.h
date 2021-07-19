#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TAM 9

struct graph{
   int V;
   int E;
   int **adj; //Matriz de adjacência de um grafo
};
typedef struct graph *Graph;

Graph initGraph(int V);

static int **matrixInt(int r, int c, int val);

void insertEdge(Graph G, int v, int w);

void showGraph(Graph G);

int verticesColoureds(int m[][TAM]);

void backtracking(Graph G, int m[][TAM], int k, int maux[][TAM]);

