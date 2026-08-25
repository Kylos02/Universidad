#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define n 7
#define pi 3.1416

struct complejos{
	
	double a;
	double b;

};

int comex(struct complejos); //Funciones prototipo
double multis(struct complejos);

struct complejos K[n]; //Variables globales
double Mod[n], Expo[n];

int main(){
		 
	int i;

	printf("\nArreglo de numeros complejos\n\n");
	
	for(i=0; i<n; i++){ //Genero numeros aleatorios para el arreglo
		K[i].a = rand()%12;
		K[i].b = rand()%12;
		printf("<%1.0lf> <%1.0lfi>\n", K[i].a, K[i].b); //Imprimo los numeros generados aleatoriamente del arreglo
	}
	
	printf("\nConvirtiendo numeros complejos a exponenciales\n\n");
	printf("Modulos\t\tForma exponencial\n\n");
	
	comex(K[n]);
	
	printf("Multiplicando los complejos en su forma exponencial\n");
	
	multis(K[n]);

return 0;
}

int comex(struct complejos l){ //Esta función convierte los numeros reales e imaginarios en modulo y forma exponencial respectivamente
	
	int i;
	double mod, argp, exp;
	
	for(i=0; i<n; i++){
		
		mod = pow(K[i].a, 2) + pow(K[i].b, 2);
		mod = sqrt(mod);
		argp = K[i].b;
		argp = argp / K[i].a; 
		exp = atan(argp);
		Mod[i] = mod; //Guardo los datos en otro arreglo para no influir en el original
		Expo[i] = exp;
		
	printf("<%1.2lf>\t\t<%1.2lf>\n\n", mod, exp);

	}

}

double multis(struct complejos l){ // Multiplica los modulos y suma los exponentes
	
	int i;
	double ress, resm = 1;
	
	for(i=0; i<n; i++){
		
		resm = Mod[i]*resm; //Cuando se multiplican numeros complejos en forma exponencial, solo el módulo se multiplica
		ress = Expo[i]+ress; //Cuando se multiplican numeros complejos en su forma exponencial, su exponente se suma

	}
	
	printf("\nLa multiplicación de todos los modulos es: %lf", resm);
	printf("\n\nLa suma de todas las formas exponenciales es: %lf", ress);

}
