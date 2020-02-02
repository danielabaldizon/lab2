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
#include <pic16f887.h>
#include "ADC.h"
#include "7SEGMENTOS.h"

#define _XTAL_FREQ 4000000

// 7 SEGMENTOS
#define a PORTCbits.RC0
#define b PORTCbits.RC1
#define c PORTCbits.RC2
#define d PORTCbits.RC3
#define e PORTCbits.RC4
#define f PORTCbits.RC5
#define g PORTCbits.RC6
#define dp PORTCbits.RC7 


uint8_t cont = 0;
uint8_t AR1 = 0;
uint8_t AR2 = 0;
uint8_t madc;
uint8_t AL = 0;
uint8_t AH;
uint8_t AHM;
uint8_t AHL;

// PROTOTIPO DE FUNCIONES
void botones(void);
void adc(void);
void InitTimer0();
void Interrupt();

void __interrupt() ISR(void){
    if (INTCONbits.RBIF  == 1){
        botones();
    }
    if (PIR1bits.ADIF == 1){
        adc();
    }
    if (INTCONbits.T0IF == 1){ 
    Interrupt();
  }
    
}

void main(void) {
    //CONFIGURACION
ANSELH = 0;
ANSEL = 0;
TRISD = 0;
TRISC = 0;
TRISAbits.TRISA6 = 0; //TRANSISTORES
TRISAbits.TRISA7 = 0;
TRISAbits.TRISA5 = 0; //alrm
TRISBbits.TRISB7 = 1; // botones
TRISBbits.TRISB6 = 1;
OPTION_REG = 0b11100111;
OSCCONbits.IRCF = 7;
OSCCONbits.SCS = 1;

// CONFIGURACION DEL ADC
ADC_CONFIG(0, 0);
ADC_INTERRUPT();

//TMR0
InitTimer0();


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
PORTC = 255;
PORTD = 0;
PORTAbits.RA5 = 0;




//INICIO DEL LOOP INFINITO
while(1){
    PORTD = cont;
    ADCON0bits.GO = 1;         //INICIA EL ADC
    if (AH > cont){ //COMPARACION
        PORTAbits.RA5 = 1; //ENCENDER ALRM
    }
    else{
        PORTAbits.RA5 = 0; //APAGAR ALRM
    }
}

}


void botones (void){
    
    if (PORTBbits.RB7 == 0){ // BOTONES CON ANTIRREBOTE
        AR1 = 1;
    }
         else{
             if (AR1 == 1){
                 cont++;
                 AR1 = 0;
                 __delay_ms(20);
             }
         }
    if (PORTBbits.RB6 == 0){
        AR2 = 1;
    }
         else{
             if (AR2 == 1){
                 cont = cont - 1;
                 AR2 = 0;
                 __delay_ms(20);
             }
    }
    INTCONbits.RBIF = 0; //BANDERA PORTB
}

void adc(void){
  
    AH = ADRESH;
   // AL = ADRESL;
    PIR1bits.ADIF = 0;
}

//Timer0
//Prescaler 1:4; TMR0 Preload = 6; Actual Interrupt Time : 1 ms
 
//Place/Copy this part in declaration section
void InitTimer0(){
  OPTION_REGbits.T0CS = 0;
  OPTION_REGbits.PSA = 0;
  OPTION_REGbits.PS = 0;
  INTCONbits.T0IE = 1;
  TMR0 = 6;
  INTCONbits.T0IF	 = 0; // LIMPIAR BANDERA
  
}
 
void Interrupt(){
    AHM = AH >> 4; // CORRE 4 BITS PARA TOMAR LOS MAS SIGNIFICATIVOS
    AHL = AH & 0x0F; // AND PARA SOLO DEJAR LOS MENOS SIGNIFICATIVOS
    if (AL == 0){
        PORTAbits.RA7 = 1;
        SEG(AHM);
        __delay_ms(5);
        PORTC = 255; // ELIMINA SOMBRA
        __delay_ms(8);
        PORTAbits.RA7 = 0;
        AL = 1;
    }
    else {
        PORTAbits.RA6 = 1;
        SEG(AHL);
        __delay_ms(5);
        PORTC = 255;
       // __delay_ms(15);
        PORTAbits.RA6 = 0;
        AL = 0;
    }
    INTCONbits.T0IF	 = 0; // LIMPIAR BANDERA
    TMR0 = 6; // VALOR DEL TMR0
     
}
