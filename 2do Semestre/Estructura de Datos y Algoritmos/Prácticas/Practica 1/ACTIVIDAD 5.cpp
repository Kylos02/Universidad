// Romero Pizano Christian Gustavo //
// ACTIVIDAD 5 //
#include <stdio.h>
#define y 4
#define z 4
int main(){
		
int arr[3][4][4],i,j,k;
    
	for(j=0;j<y;j++){
     for(k=0;k<z;k++){
    arr[0][j][k]= k+1 ;}}
      
	for(j=0;j<y;j++){
     for(k=0;k<z;k++){
    arr[1][j][k]= 0; }}
 
    for(j=0;j<y-1;j++){
     for(k=0;k<z;k++){
    arr[1][j][k]= 1; }}    
	
	printf("Matriz 1:\n");
 	 for(j=0;j<y;j++){
     for(k=0;k<z;k++){
    printf(" %d", arr[0][j][k]);}
	printf("\n");}
      
    
    printf("\nMatriz 2:\n");
     for(j=0;j<y;j++){
     for(k=0;k<z;k++){
    printf(" %d", arr[1][j][k]); }
	printf("\n");}
    
    for(i=0;i<y;i++){
     for(j=0;j<z;j++){
     	arr[2][i][j]=0; 
		 for(k=0;k<z;k++){
    arr[2][i][j]+= arr[0][i][k]* arr[1][k][j]; }}}
   
    printf("\nResultado \n");
    for(j=0;j<y;j++){
     for(k=0;k<z;k++){
     printf(" %d", arr[2][j][k]); }
	 printf("\n");}
    
return 0;
}

