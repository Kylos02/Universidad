#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define n 20

char impdata(FILE *archivo);
int maxlin(FILE *archivo);

char PER[n];
int i;

int main(int argc, char *argv[]){

	FILE *archivo;
	archivo = fopen("INFO.txt", "r");

	if(archivo == NULL){
		printf("El archivo no existe D:");
		
	}else{
		printf("El archivo abrio con exito :D");
		
	}

	printf("\n\n");	

	//maxlin(archivo);
	impdata(archivo);
	
	fclose(archivo);
	
	free(archivo);
	
return 0;	
}

char impdata(FILE *archivo){

 while (fgets(PER, n, archivo)){
        printf("%s", PER);

    }
} 

int maxlin(FILE *archivo){


}



