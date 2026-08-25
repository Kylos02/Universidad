#include <stdio.h>
#include <stdlib.h>
int main(){
    short arr[5], *apArr, i;
    printf("Direccion del primer elemento del arreglo arr: %p \n", &arr[0]);
    printf("Direccion asignada a arr: %p \n", &arr);
    
    apArr=&arr[0];
    
    printf("Direccion asignada a la variable apuntador apArr: %p \n",&apArr);
    printf("Direccion almacenada en la variable apuntador apArr: %p \n",apArr);
    
    for(i=0;i<5;i++){ 
    *(apArr+i)= i+1;} //Llena el arreglo a través del apuntador
    
       for(i=0;i<5;i++){
    *(apArr+i)+= 2;}  //Se le suma 2 a cada elemento del arreglo
    
    for(i=0;i<5;i++){ 
    printf("\nElemento %d: %d*",i+1, *(apArr+i));} //Imprime los elementos del arreglo
    
    
    
    return 0;
}

