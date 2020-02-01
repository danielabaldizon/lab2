/* 
 * File:   Lab2.c
 * Author: Daniela Baldizon
 *
 * Created on 29 de enero de 2020, 02:13 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

uint8_t cont = 0;
uint8_t AR1 = 0;
uint8_t AR2 = 0;

// PROTOTIPO DE FUNCIONES
void botones(void);

void __interrupt() ISR(void){
    if (INTCONbits.RBIF  == 1){
         if (PORTBbits.RB7 == 0){
        AR1 = 1;
    }
         else{
             if (AR1 == 1){
                 cont++;
                 AR1 = 0;
                 __delay_ms(25);
             }
         }
    if (PORTBbits.RB6 == 0){
        AR2 = 1;
    }
         else{
             if (AR2 == 1){
                 cont = cont - 1;
                 AR2 = 0;
                 __delay_ms(25);
             }
    }
    INTCONbits.RBIF = 0;
    }
    
}

void main(void) {
    //CONFIGURACION
ANSELH = 0;
ANSEL = 0;
TRISD = 0;
TRISC = 0;
TRISBbits.TRISB7 = 1;
TRISBbits.TRISB6 = 1;
OPTION_REG = 0b11100111;


//INTERRUPCIÓN DE PUERTO B
IOCBbits.IOCB7 = 1;
IOCBbits.IOCB6 = 1; // ACTIVA LA INTERRUPCIÓN DE CAMBIO
INTCONbits.GIE = 1; // ACTIVA LAS INTERRUPCIONES GLOBALES
INTCONbits.RBIE = 1; // HABILITA LA INTERRUPCION DEL PUETO B
WPUBbits.WPUB7 = 1; // HABILITA EL PULL UP
WPUBbits.WPUB6 = 1;
OPTION_REGbits.nRBPU = 0;
INTCONbits.RBIF = 0;


//LIMPIEZA DE VARIABLES Y PUERTOS
PORTC = 0;
PORTD = 0;


//INICIO DEL LOOP INFINITO
while(1){
    PORTD = cont;
    
}

}


void botones (void){
    
    if (PORTBbits.RB7 == 0){
        PORTD++;
    }
    if (PORTBbits.RB6 == 0){
        PORTD--;
    }
    RBIF = 0;
}