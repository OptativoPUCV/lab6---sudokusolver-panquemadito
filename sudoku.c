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
   int row_check[9][10] = {0};
   int col_check[9][10] = {0};
   int submatrix_check[9][10] = {0} ;
   for (int i = 0 ; i < 9 ; i++) {
      for (int j = 0 ; j < 9 ; j++) {
         int num = n->sudo[i][j] ;
         if (num != 0) {
            if (row_check[i][num] == 1 || col_check[j][num] == 1) {
               return 0 ;
            }
            row_check[i][num] = 1;
            col_check[j][num] = 1;
            
         }
      }
   }
   for (int i = 0 ; i < 9 ; i+=3) {
      for (int j = 0 ; j < 9 ; j+=3) {
         for (int k = i; k < i + 3; k++) {
            for (int l = j ; l < j + 3; l++) {
               int num = n->sudo[k][l] ;
               if (num != 0) {
                  if (submatrix_check[(i / 3)* 3 + (j / 3)][num] == 1) {
                     return 0 ;
                  }
                  submatrix_check[(i / 3)* 3 + (j / 3)][num] = 1;
               }
            }
         }
      }
   }
   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   for(int i = 0; i < 9 ; i++) {
      for (int j = 0; j < 9 ; j++) {
         if(n->sudo[i][j] == 0) {
            for (int num = 1 ; num <= 9; num++){
               Node* newNode = copy(n) ;
               newNode->sudo[i][j] = num;
               if (is_valid(newNode)) {
                  pushBack(list, newNode) ;
               } else {
                  free(newNode);
               }                  
            }
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n){
   for(int i = 0; i < 9 ; i++) {
      for(int j = 0; j < 9 ; j++) {
         if (n->sudo[i][j] == 0) {
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* s = createStack();
   push(s, initial) ;
   *cont = 0;

   while(!is_empty(s)) {
      Node* node = top(s);
      pop(s);
      (*cont)++;

      if (is_final(node)) {
         freeStack(s);
         return node;
      }

      List* adj_nodes = get_adj_nodes(node);
      Node* adj_node;
      while((adj_node = first(adj_nodes) != NULL)) {
         push(s, adj_node);
         popFront(adj_nodes);
      }
      free(node);
      freeList(adj_nodes);
   }
   
   freeStack(s);
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