/* 
 * File:   ADC.c
 * Author: Daniela Baldizon
 *
 * Created on 1 de febrero de 2020, 01:06 AM
 */

#include <pic16f887.h>
#include "ADC.h"
#include <stdint.h>

void ADC_CONFIG(uint8_t canal){
    ADCON0bits.ADON = 1;
    ADCON0bits.ADCS = 1;
    switch(canal){
        case 0:
            ANSELbits.ANS0 = 1;
            ADCON0bits.CHS = 0;
            TRISAbits.TRISA0 = 1;
            break;
            
        case 1:
            ANSELbits.ANS1 = 1;
            ADCON0bits.CHS = 1;
            TRISAbits.TRISA1 = 1;
            break;
            
        case 2:
            ANSELbits.ANS2 = 1;
            ADCON0bits.CHS = 2;
            TRISAbits.TRISA2 = 1;
            break;
            
        case 3:
            ANSELbits.ANS3 = 1;
            ADCON0bits.CHS = 3;
            TRISAbits.TRISA3 = 1;
            break;
            
        case 4:
            ANSELbits.ANS4 = 1;
            ADCON0bits.CHS = 4;
            TRISAbits.TRISA5 = 1;
            break;
            
        case 5:
            ANSELbits.ANS5 = 1;
            ADCON0bits.CHS = 5;
            TRISEbits.TRISE0 = 1;
            break;
            
        case 6:
            ANSELbits.ANS6 = 1;
            ADCON0bits.CHS = 6;
            TRISEbits.TRISE1 = 1;
            break;
            
        case 7:
            ANSELbits.ANS7 = 1;
            ADCON0bits.CHS = 7;
            TRISEbits.TRISE2 = 1;
            break;
            
        case 8:
            ANSELHbits.ANS8 = 1;
            ADCON0bits.CHS = 8;
            TRISBbits.TRISB2 = 1;
            break;
            
        case 9:
            ANSELHbits.ANS9 = 1;
            ADCON0bits.CHS = 9;
            TRISBbits.TRISB3 = 1;
            break;
            
        case 10:
            ANSELHbits.ANS10 = 1;
            ADCON0bits.CHS = 10;
            TRISBbits.TRISB1 = 1;
            break;
            
        case 11:
            ANSELHbits.ANS11 = 1;
            ADCON0bits.CHS = 11;
            TRISBbits.TRISB4 = 1;
            break;
            
        case 12:
            ANSELHbits.ANS12 = 1;
            ADCON0bits.CHS = 12;
            TRISBbits.TRISB0 = 1;
            break;
            
        case 13:
            ANSELHbits.ANS13 = 1;
            ADCON0bits.CHS = 13;
            TRISBbits.TRISB5 = 1;
            break;
    }
}
