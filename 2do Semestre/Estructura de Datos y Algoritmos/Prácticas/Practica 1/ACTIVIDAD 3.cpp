// Silverio Martínez Andrés //
// ACTIVIDAD 3 //
#include<stdio.h>
#include<stdlib.h>
// Estos son los valores que se utilizaron para el arreglo principal TRM //
#define N 5 // Numero de filas //
#define M 6 // Numero de columnas //

 // Para esta actividad, se definieron las siguientes funciones: //
void llenado(int y, int z); // LLena el arreglo principal TRM //
void imprimir(int y, int z); // Imprime el arreglo principal TRM //
void suma(int y, int z); // Suma las 6 columnas del arreglo y las guarda en el arreglo ASM //
void apareceX(int y, int z); // Calcula las apariciones de un numero "x" //

int TRM[N][M], ASM[M], i, j, k, S, x = 2; // Decidií declarar variables globales, porque se me hacen más practicas //

int main(){

	printf("-------------------------------- Actividad 3 -----------------------------------\n\n"); // Texto para dar un poco más de formato //
	
	llenado(N, M); // Se llama a la funcion llenado, para llenar el arreglo TRM //
	printf("El arreglo TRM, queda de la siguiente manera:\n\n"); // Texto para dar formato //
	imprimir(N, M); // Imprime el como quedó el arreglo TRM tras el llenado //
	
	suma(N, M); // Llama a la funcion suma para sumar las columnas del arreglo TRM y guardar los resultados en ASM //

	printf("<-- Suma total de cada una de las columnas\n\n\n"); // Texto para dar formato //
	
	apareceX(N, M); // Llama a la funcion apareceX para saber cuantas veces es que aparece "x" en el arreglo principal TRM ((
	
return 0;	
}

void llenado(int y, int z){ // Funciom llenado definida //
	
	for(i=0;i<N;i++){ // Se recorre el arreglo principal TRM para así poder llenar cada uno de sus espacios vacios //
		for(j=0;j<M;j++){
			
			TRM[i][j] = rand()%7;	// Aleatoriamente se llena el arreglo principal TRM, con numeros de entre 0 y 6 //
		}
	}
}

void imprimir(int y, int z){ // Funcion imprimir definida //
	
	for(i=0;i<N;i++){ // Se recorre todo el arreglo principal TRM para imprimir cada uno de sus espacios //
		for(j=0;j<M;j++){
			printf(" %d ", TRM[i][j]); // Imprime cada uno de los espacios del arreglo principal TRM //
		}
	printf("\n"); // Enter para dar más presentación //
	}
printf("\n"); // Otro enter para dar mäs presentación //
}

void suma(int y, int z){ // Funcion suma definida //
	
	for(i=0;i<M;i++){ // Se recorre el arreglo principal TRM para poder sumar sus elementos //
	S = 0; // Sirve para que la próxima vez que se ejecute el for, la suma de la columna anterior no se quede guardada y den datos erroneos //
		for(j=0;j<N;j++){ // Se recorre el arreglo principal TRM para poder sumar sus elementos //
		S = S + TRM[j][i]; // Suma las columnas del arreglo principal TRM y los guarda en una variable S
	
		} 
		
	ASM[i] = S;	// Guarda los resultados de la suma en el arreglo ASM //

	}
	
	for(i=0;i<M;i++){	// Recorre el arreglo ASM para mostrar todos los resultados obtenidos de la suma //
		printf("%d ", ASM[i]); // Imprime los resultados guardados en el arreglo ASM //
		
	}
}

void apareceX(int y, int z){ // Funcion apareceX definida //
	
int apariciones = 0; // Se declara una variable local, que servira como contador //
	
	for(i=0;i<N;i++){ // Se recorre el arreglo principal TRM para poder analizar cada uno de los elementos guardados //
		for(j=0;j<M;j++){
		 if(x == TRM[i][j]){ // Condición, si un numero guardado en el arreglo principal TRM es igual a x ....... //
		 apariciones++; // ......... aumenta el contador //
			}	
		}
	
	}
	printf("El numero %d aparece %d veces en el arreglo TRM", x,  apariciones); // Imprime cuantas veces aparece "x" en el arreglo principal TRM //
}


