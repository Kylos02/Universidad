// Ramírez Jiménez Arám //
// ACTIVIDAD 6 //
#include <stdio.h> 
#define n 6 

int main () {
  int A[n][n], i, j; 
  
  for (i=0; i<n; i++) 
  {
    for (j=0; j<n; j++)
    {  
      A[0][j]=i+j;
      printf ("%d ", A[0][j]);            
    }
    printf("\n");
  }
    
}

