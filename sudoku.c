#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node* n){
  int numrep[10];
  int i,j,k,h,p;

  //inicializa numrep en 0s
  for(h=0;h<10;h++) numrep[h]=0;

  //validez por fila
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
      numrep[n->sudo[i][j]]++;
    for(k=1;k<10;k++)
      if(numrep[k]>1) return 0;
    for(h=0;h<10;h++)
      numrep[h]=0;
  }

  //validez por columna
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
      numrep[n->sudo[j][i]]++;
    for(k=1;k<10;k++)
      if(numrep[k]>1) return 0;
    for(h=0;h<10;h++)
      numrep[h]=0;
  }

  //validez por submatriz 3x3
  for(k=0;k<9;k++){
    for(p=0;p<9;p++){
      i=3*(k/3)+(p/3);
      j=3*(k%3)+(p%3);
      numrep[n->sudo[i][j]]++;
    }
    for(i=1;i<10;i++)
      if(numrep[i]>1) return 0;
    for(h=0;h<10;h++)
      numrep[h]=0;
  }
  
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list=createList();
  int i,j,k=0;
  
  //recorre el tablero por cada posición que tiene (i,j)
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
      //si la posición está vacía (=0) entonces lo rellena 
      //con el número que corresponde por tablero
      if(n->sudo[i][j]==0){
        //crea 9 versiones del tablero (1,2,...,9)
        for(k=0;k<9;k++){
          Node* adjn = createNode();
          adjn = copy(n);
          adjn->sudo[i][j] = k+1;
          if(is_valid(adjn)) pushBack(list, adjn);
        }
        return list;
      }
  //si entra a este return es porque no había valor nulo
  return list;
}


int is_final(Node* n){
  int i,j;

  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
      if(n->sudo[i][j]==0) return 0;

  return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/