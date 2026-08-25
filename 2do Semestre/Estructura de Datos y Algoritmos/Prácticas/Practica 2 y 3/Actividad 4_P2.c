#include <stdio.h>

void longCadena(char *ap, int *n);

int main(){
	char cadena[30];
	int nc;
	
	printf("Introducir cadena: ");
	//scanf("%s", cadena);
	gets(cadena);
	
	longCadena(cadena, &nc);
	
	printf("longitud = %d", nc);
	return 0;
}
char *gets(char *str);

void longCadena(char *ap, int *n){
	int res=0;
	*n=0;
	while(*ap != '\0'){
		res+=1;
		ap+=1;
	}
	*n=res;
}

