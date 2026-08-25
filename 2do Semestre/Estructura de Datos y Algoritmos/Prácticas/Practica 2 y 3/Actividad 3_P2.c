#include <stdio.h>
#include <stdlib.h>
#define n 10
#define m 20

void llena(int *p);
void llenaC(int *a, int *b, int *c);
void imprime(int *p, int ne);

int main(){
    int A[n], B[n], C[m];
    int *ap, *bp, *cp;
  
   ap = A;
   bp = B;
   cp = C;
   
   llena(ap);
   llena(bp);
   llenaC(ap,bp,cp);
   printf("Arreglo 1:\n\n");
   imprime(ap,n);
   printf("\nArreglo 2:\n\n");
   imprime(bp,n);
   printf("\nArreglo 3:\n\n");
   imprime(cp,m);

return 0;
}

 void llena(int *p){
 int i;
     for(i=0;i<n;i++){
      *(p+i)=rand()%n;
     }
 }

 void imprime(int *p, int ne){ 
 int i;
     for(i=0;i<ne;i++){
      printf(" %d ", *(p+i));}
      printf("\n");
}

void llenaC(int *a, int *b, int *c){
    int i;
    for(i=0;i<n;i++){
     *c=*a;
      a++;
      c++;
     *c=*b;
      b++;
      c++;}
	  }
