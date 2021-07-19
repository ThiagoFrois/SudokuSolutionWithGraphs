#include"graph.h"

// Função que controla o laço para criar o grafo completo nas linha e colunas
int control(int var){
   int aux;
   if(var % TAM != 0){
      if(var > TAM){
         aux = var + TAM - var%TAM;
      }
      else{
         aux = TAM;
      }
   }
   else{
      aux = var + TAM;
   }
   return aux;
}

// Todos as subgrades do sudoku se tornam grafos completos
void completeSubgraphs(Graph G){
   int i, j, v;
   int l, c;
   int aux;
   for(v = 0; v < TAM*TAM; v++){
      l = v/TAM;
      c = v%TAM;
      l = l/sqrt(TAM);
      l = l*sqrt(TAM);
      for(i = l; i < l + sqrt(TAM); i++){
         c = c/sqrt(TAM);
         c = c*sqrt(TAM);
         for(j = c; j < c + sqrt(TAM); j++){
            if(v != i*TAM + j){
               insertEdge(G, v, i*TAM + j);
            }
         } 
      }
   }
}

void completeLineGraph(Graph G, int var){
   int i, aux;
   for(i = var; i < TAM*TAM; i += TAM){
      if(var != i){
         insertEdge(G, var, i);
      }
   }
   for(i = var - TAM; i >= 0; i -= TAM){
      insertEdge(G, var, i);
   }
   
   aux = control(var);
   for(i = var; i < aux; i++){
      if(var != i){
         insertEdge(G, var, i);
      }
   }
   for(i = var - 1; i >= aux - TAM; i--){
      insertEdge(G, var, i);
   }
}

// Todas as linha e colunas se tornam grafos completos
void completeLineGraphs(Graph G){
   int v;
   
   for(v = 0; v < TAM*TAM; v++){
      completeLineGraph(G, v);
   }
}

// Transforma a matriz do sudoku em um grafo por meio da matriz de adjacência
Graph matrixForGraph(int m[][TAM], Graph G){
   int i, j;
   G = initGraph(TAM*TAM);
   completeSubgraphs(G);
   completeLineGraphs(G);

   return G;
}

// Inicia a matriz
void matrixInit(int m[][TAM], int tam){
   int i, j;
   for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
         m[i][j] = 0;
      }
   }
}

// Mostra a matriz
void showSudoku(int m[][TAM]){
   int i, j;

   for(i = 0; i < TAM; i++){
      for(j = 0; j < TAM; j++){
         printf("%2d ", m[i][j]);
      }
      printf("\n");
   }
}

int main(){
   Graph sudokuGraph;
   int sudoku[TAM][TAM];
   int sudokuaux[TAM][TAM];
   int i, j;

   matrixInit(sudoku, TAM);
   
   sudoku[0][2] = 4;
   sudoku[0][6] = 3;
   sudoku[1][0] = 2;
   sudoku[1][3] = 7;
   sudoku[1][5] = 9;
   sudoku[1][8] = 8;
   sudoku[2][1] = 6;
   sudoku[2][3] = 5;
   sudoku[2][5] = 4;
   sudoku[2][7] = 7;
   sudoku[3][2] = 5;
   sudoku[3][4] = 7;
   sudoku[3][6] = 2;
   sudoku[4][0] = 4;
   sudoku[4][3] = 3;
   sudoku[4][5] = 5;
   sudoku[4][8] = 9;
   sudoku[5][2] = 7;
   sudoku[5][4] = 9;
   sudoku[5][6] = 5;
   sudoku[6][1] = 4;
   sudoku[6][3] = 9;
   sudoku[6][5] = 2;
   sudoku[6][7] = 5;
   sudoku[7][0] = 8;
   sudoku[7][3] = 6;
   sudoku[7][5] = 7;
   sudoku[7][8] = 2;
   sudoku[8][2] = 9;
   sudoku[8][6] = 1;

   // Cria uma matriz auxiliar
   for(i = 0; i < TAM; i++){
      for(j = 0; j < TAM; j++){
         sudokuaux[i][j] = sudoku[i][j];
      }
   }
   showSudoku(sudoku);
   sudokuGraph = matrixForGraph(sudoku, sudokuGraph);
   backtracking(sudokuGraph, sudoku, verticesColoureds(sudoku), sudokuaux);
   printf("\n");
   showSudoku(sudoku);

   return 0;
}
