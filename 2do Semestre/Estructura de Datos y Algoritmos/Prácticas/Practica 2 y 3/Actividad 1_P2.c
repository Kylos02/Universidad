#include <stdio.h>

int main(){
    double a, *ap;
    a=7.5;
    ap=&a;
    printf("Direccion asignada a la variable a: %p \n", &a);
    printf("Direccion asignada a la variable ap: %p \n", &ap);
    printf("Valor asignado a la variable 'a': %.3lf \n", a);
    printf("Valor asignado a la variable ap o direccion a la que apunta:  %p \n", ap);
    *ap=2;
    printf("Nuevo valor de la variable: %.3lf", *ap);
    

    return 0;
}

