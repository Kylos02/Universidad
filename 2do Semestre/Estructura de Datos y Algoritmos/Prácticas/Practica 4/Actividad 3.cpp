#include <stdio.h>
#include <stdlib.h>
#define m 2
#define n 4

void llenav(int *vector);
void llenamat(int **matriz);
void mult(int *vec, int **mat, int *resultado);

int main(){
    int *vec,**mat,*res;
    llenav(vec);
    printf("\n");
    llenamat(mat);
    mult(vec,mat,res);
    return 0;
	 }

void llenav(int *vector){
    int i;
    vector= (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++){
    vector[i]=i+1;}
    printf("\nElementos del vector:\n");
    for(i=0;i<n;i++){
    printf("%d  ", vector[i]);}}


void llenamat(int **matriz){
	int i,j,k;
matriz=	(int **)malloc(n*sizeof(int*));
 for(i=0;i<n;i++){
 matriz[i]=(int*)malloc(m*sizeof(int));	
 }
 for(j=0;j<n;j++){
 for(k=0;k<m;k++){
 matriz[j][k]= k+1;	
 }}
 printf("Matriz: \n");
  for(j=0;j<n;j++){
 for(k=0;k<m;k++){
 printf("%d  ",matriz[j][k]);} printf("\n");}}


void mult(int *vec, int **mat, int *resultado){
	int i,j,k;
	resultado= (int *)malloc(m*sizeof(int));
	
	printf("\nResultado:\n");

for(i=0; i<m; i++){
  for(int j=0; j<n; j++){  	
    resultado[i] += vec[j]*mat[j][i];  }}   
    for(int i=0; i<m; i++){
  	printf("%d  ",resultado[i]); }}
  
