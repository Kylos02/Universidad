/*
 * Pr�ctica 1 - Fundamentos de Sistemas Embebidos
 * Contador de 0 a 9 en display de 7 segmentos controlado por bot�n.
 * Silverio Mart�nez Andr�s
 */


#pragma config FOSC = XT        
#pragma config WDTE = OFF       
#pragma config PWRTE = ON       
#pragma config BOREN = ON       
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#include <xc.h>

// Definir frecuencia del oscilador para la funci�n __delay_msSi, 
#define _XTAL_FREQ 4000000

// C�digos del Display de 7 Segmentos
const unsigned char display_codes[10] = {
    0xFC, // 0 
    0x60, // 1 
    0xDA, // 2 
    0xF2, // 3 
    0x66, // 4 
    0xB6, // 5 
    0xBE, // 6 
    0xE0, // 7 
    0xFE, // 8 
    0xF6  // 9 
};

void main(void) {
    
    // Configurar pines anal�gicos como digitales 
    ADCON1 = 0x06; 

    // Configurar direcciones 
    TRISAbits.TRISA0 = 1;   // RA0 como entrada (Bot�n)
    TRISB = 0x00;           // Todo el Puerto B como salida (Display)

    // Inicializar variables
    unsigned char contador = 0; // Variable para guardar el n�mero actual (0-9)
    PORTB = display_codes[contador]; // Mostrar el 0 inicial 


    while(1) {
        
        // Mostrar el valor actual en el Puerto B
        PORTB = display_codes[contador];

        // Verificar si el bot�n (RA0) est� presionado
        if (PORTAbits.RA0 == 1) {
            
            // Retardo para observar el cambio y evitar rebotes excesivos 
            __delay_ms(1000); 
            
            // Incrementar contador 
            contador++;

            // Si el contador pasa de 9, reiniciar a 0
            if (contador > 9) {
                contador = 0;
            }
        }

    }
}
