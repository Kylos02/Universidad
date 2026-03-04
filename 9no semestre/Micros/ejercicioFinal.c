// Ejercicio Final

char recibe_dato(){
    // Esperar a que llegue un dato (RCIF se activa cuando el byte ha sido recibido)
    while(PIR1.RCIF == 0);
    return RCREG;            // Devolver caracter del registro de recepción
}

void envia_dato(char dato){
    // Esperar a que el buffer de transmisión esté vacío (TRMT se activa)
    while(TXSTA.TRMT == 0);
    TXREG = dato;            // Cargar el dato al registro de transmisión
}

void envia_cadena(char *txt){
    while(*txt != 0){        // Recorrer la cadena hasta encontrar el terminador nulo
        envia_dato(*txt);    // Enviar cada caracter
        txt++;
    }
}

// Enviar número 0–255 en ASCII (tres dígitos)
void envia_decimal(unsigned char v){
    envia_dato((v / 100) + '0');        // Cifra de las centenas
    envia_dato(((v / 10) % 10) + '0');  // Cifra de las decenas
    envia_dato((v % 10) + '0');         // Cifra de las unidades
}

// Programa principal
void main(){

    char canal_ascii;
    unsigned char canal_num;
    unsigned char valor;

    // CONFIGURACIÓN UART
    // Fosc = 4MHz, Baud Rate = 9600, BRGH = 1
    // SPBRG = (Fosc / (16 * Baud Rate)) - 1
    // SPBRG = (4000000 / (16 * 9600)) - 1 = 25.04... -> 25
    SPBRG = 25;          // Valor para 9600 bps a 4 MHz
    TXSTA.BRGH = 1;      // Velocidad alta
    TXSTA.SYNC = 0;      // Modo Asíncrono
    RCSTA.SPEN = 1;      // Habilitar pines seriales (RC6/TX, RC7/RX)
    TXSTA.TXEN = 1;      // Habilitar Transmisor
    RCSTA.CREN = 1;      // Habilitar Receptor continuo

    // CONFIGURACIÓN ADC
    TRISA = 0xFF;        // Puerto A como entrada (AN0-AN4)
    TRISE = 0xFF;        // Puerto E como entrada (AN5-AN7, solo RE0, RE1, RE2)

    // Configuración de pines analógicos
    // Bit 7 (ADFM) = 0 (Justificación Izquierda)
    ADCON1 = 0b00000000;

    // Mensaje de inicio
    envia_cadena("Sistema listo.\r\n");

    while(1){
        envia_cadena("Seleccione canal (0-7): ");

        // 1. Recibir canal desde la terminal
        canal_ascii = recibe_dato();
        envia_dato(canal_ascii); // Mostrar el caracter recibido (eco)
        envia_cadena("\r\n");

        // Convertir el caracter ASCII a número y validar
        if(canal_ascii >= '0' && canal_ascii <= '7'){
            canal_num = canal_ascii - '0';  // Convertir '0'-'7' a 0-7

            // 2. Configurar ADCON0 para el canal seleccionado
            ADCON0 = 0b01000001 | (canal_num << 3);

            // 3. Tiempo de Adquisición (Delay)
            // Esperar un tiempo mínimo para que el capacitor de hold cargue
            delay_us(50);

            // 4. Iniciar Conversión
            ADCON0.GO_DONE = 1; // Poner a 1 para iniciar la conversión

            // 5. Esperar fin de Conversión
            // El bit GO_DONE se limpia automáticamente a 0 cuando la conversión termina
            while(ADCON0.GO_DONE);

            // 6. Leer solo ADRESH (8 bits más significativos)
            valor = ADRESH;

            // 7. Enviar resultado en decimal
            envia_cadena("Valor ADC (8 bits, decimal): ");
            envia_decimal(valor);
            envia_cadena("\r\n------------------\r\n");
        }
        else {
            envia_cadena("Error: Canal invalido. Por favor, introduzca un numero entre 0 y 7.\r\n------------------\r\n");
        }
    }
}