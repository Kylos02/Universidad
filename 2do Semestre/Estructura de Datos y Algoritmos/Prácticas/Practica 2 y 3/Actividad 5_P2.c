#include <stdio.h>
#include <stdlib.h>
#define n 8

void llena (float *p);
void suma (float *a, float *b, float *c);
void imprime (float *p, char C);

int main (){
  float A[n][n], B[n][n], C[n][n], *ap, *bp, *cp;
  ap = &A[0][0];
  bp = &B[0][0];
  cp = &C[0][0];

  llena (ap);
  llena (bp);

  suma (ap, bp, cp);

  imprime (ap,'A');
  imprime (bp, 'B');
  imprime (cp, 'C');

  return 0;
}

void
llena (float *p)
{
  int i;
  for (i = 0; i < n * n; i++)
    {
      *(p + i) = rand () % n;
    }
}

void suma (float *a, float *b, float *c)
{
  int i;
  for (i = 0; i < n * n; i++)
    {  *(c + i) = *(a + i) + *(b + i); }
}

void imprime (float *p,char c)
{
  int i, j;
  printf("\nMatriz %c\n\n", c);
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++){
	  printf ("  %.1f", *(p + n * i + j));
	}
      printf ("\n");
    }
    printf("\n"); 
}

