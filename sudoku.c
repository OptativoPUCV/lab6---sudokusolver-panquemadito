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

    return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   int emptyFound = 0;
   int row, col ;

   //Busca la primera casilla vacia
   for(row = 0 ; row < 9  && !emptyFound ; row++) {
      for (col = 0 ; col < 9 && !emptyFound ; col++) {
         if (n->sudo[row][col] == 0) {
            emptyFound = 1;
            break;
         }
      }
   }
   // si la encontramos  disminuimos el col por el incremento del bucle
   if (emptyFound) {
      col--;

      for (int num = 1 ; num<= 9 ; num++) {
         n->sudo[row][col] = num;
         if (is_valid(n)) {
            Node* newNode = copy(n) ;
            pushBack(list,newNode) ;
         }
         n->sudo[row][col] = 0;
         
      }
   }
    return list;
}


int is_final(Node* n){
    return 0;
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