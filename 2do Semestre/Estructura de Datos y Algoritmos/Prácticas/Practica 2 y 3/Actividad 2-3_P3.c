#include <stdio.h>
#define c 3
#define v 5
struct dE{
char nombre[30];
int edad;
char sexo[1];
int notas[v]; };

struct rE{
int numeroCuenta;
struct dE  estudiante;
};

void llenaDatos(struct rE *alum);
void imprimeDatos(struct rE *alum);
void mejorEstudiante(struct rE *alumn);

int main(){
 struct rE alumnos[c];
 llenaDatos(alumnos);
 imprimeDatos(alumnos);
 mejorEstudiante(alumnos);
 return 0; }
 
void llenaDatos(struct rE *alum){
int i,j; 
for(i=0;i<c;i++){
printf("Ingrese los datos del alumno %i:\n",i+1);
printf("Nombre:");
scanf("%s", alum[i].estudiante.nombre);
printf("Numero de cuenta:");
scanf("%d", &alum[i].numeroCuenta); 
printf("Edad:");
scanf("%d", &alum[i].estudiante.edad); 
printf("Sexo[M/F]:");
scanf("%s", alum[i].estudiante.sexo);
printf("\nIngrese las notas del alumno %d:\n", i+1);
for(j=0;j<v;j++){
printf("Nota %d: ", j+1);
scanf("%d" , &alum[i].estudiante.notas[j] ); }
printf("\n");}    
}

void imprimeDatos(struct rE *alum){
int i,j; 
for(i=0;i<c;i++){
printf("\nLos datos del alumno %i:\n",i+1);
printf("Nombre:%s\t", alum[i].estudiante.nombre);
printf("Numero de cuenta:%d\n",alum[i].numeroCuenta);
printf("Edad:%d \t \t", alum[i].estudiante.edad);
printf("Sexo:%s\n", alum[i].estudiante.sexo);
for(j=0;j<v;j++){
printf("Nota %d: %d", j+1, alum[i].estudiante.notas[j] ); }}}

void mejorEstudiante(struct rE *alumn){
	printf("\n MEJOR ESTUDIANTE\n");
	int indice_Mejor_alumn=-1;
	float alumn_mejorPromedio=0;
	int i,j;
	for(i=0;i<3;i++){
		float promedioEstudiante=0;
		for(j=0;j<5;j++){
			promedioEstudiante +=alumn[i].estudiante.notas[j];
		}
	promedioEstudiante=promedioEstudiante/5;
	if(promedioEstudiante>alumn_mejorPromedio){
		alumn_mejorPromedio=promedioEstudiante;
		indice_Mejor_alumn=i;
	}
	}
	printf("\n Estudiante con mejor promedio: %s",alumn[indice_Mejor_alumn].estudiante.nombre);
	printf("\n Promedio del mejor estudiante: %.2f", alumn_mejorPromedio);
	}
