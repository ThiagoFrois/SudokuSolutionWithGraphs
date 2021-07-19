#include"graph.h"

// Inicia o grafo
Graph initGraph(int V){
   Graph G = malloc(sizeof *G);
   G->V = V;
   G->E = 0;
   G->adj = matrixInt(V, V, 0);
   return G;
}

// Inicia a matriz
static int **matrixInt(int r, int c, int val){
   int **m = malloc(r*sizeof(int*));
   for(int i = 0; i < r; ++i){
      m[i] = malloc(c * sizeof(int));
   }
   for(int i = 0; i < r; ++i){
      for(int j = 0; j < c; ++j){
         m[i][j] = val;
      }
   }
   return m;
} 

// Inseri uma aresta no grafo
void insertEdge(Graph G, int v, int w){
   if(G->adj[v][w] == 0){
      G->adj[v][w] = 1;
      G->adj[w][v] = 1;
      G->E++;
   }
}

// Mostra o grafo
void showGraph(Graph G){
   for(int v = 0; v < G->V; ++v){
      printf("%d: ", v);
      for(int w = 0; w < G->V; ++w){
         if(G->adj[v][w] == 1){
            printf("%d ", w);
         }
      }
      printf("\n");
   }
}

// Conta o número de vértice coloridos no grafo
int verticesColoureds(int m[][TAM]){
   int i, j, k = 0;
   for(i = 0; i < TAM; i++){
      for(j = 0; j < TAM; j++){
         if(m[i][j] != 0){
            k++;
         }
      }
   }
   return k;
}

// Realiza a coloração no grafo
void backtracking(Graph G, int m[][TAM], int k, int maux[][TAM]){
   int i, j;
   int v[TAM];
   for(i = 0; i < TAM; i++){
      v[i] = 1;
   }
   if(k != TAM*TAM){ // Enquanto todos não estão coloridos realiza o backtracking
      for(i = 0; i < TAM*TAM; i++){
         if(maux[i/TAM][i%TAM] == 0){
            for(j = 0; j < TAM*TAM; j++){ // Cria um vetor v para indicando quais as cores disponíveis para colorir a aresta 
               if(G->adj[i][j] == 1){
                  if(maux[j/TAM][j%TAM] != 0){
                     v[maux[j/TAM][j%TAM] - 1] = 0;
                  }
               }
            }
            for(j = 0; j < TAM; j++){ // Parte recursiva do algorítmo, chamando backtracking após colorir a aresta
               if(v[j] == 1){
                  maux[i/TAM][i%TAM] = j + 1;
                  backtracking(G, m, k + 1, maux);
                  maux[i/TAM][i%TAM] = 0;
               }
            }
            if(maux[i/TAM][i%TAM] == 0){
               break;
            }
         }
      }
   }
   else{ // Se todo os vértices estão coloridos copia a matriz para a a função main
      for(i = 0; i < TAM; i++){
         for(j = 0; j < TAM; j++){
            m[i][j] = maux[i][j];
         }
      }
   }
}


