/* 
 * File:   7SEGMENTOS.c
 * Author: Daniela Baldizon
 *
 * Created on 1 de febrero de 2020, 03:10 PM
 */

#include <pic16f887.h>
#include "7SEGMENTOS.h"
#define a PORTCbits.RC0
#define b PORTCbits.RC1
#define c PORTCbits.RC2
#define d PORTCbits.RC3
#define e PORTCbits.RC4
#define f PORTCbits.RC5
#define g PORTCbits.RC6
#define dp PORTCbits.RC7 

void SEG(uint8_t val){
    switch(val){
        case 0:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 0;
            f = 0;
            g = 1;
            dp = 1;
            break;
        case 1:
            a = 1;
            b = 0;
            c = 0;
            d = 1;
            e = 1;
            f = 1;
            g = 1;
            dp = 1;
            break;
        case 2:
            a = 0;
            b = 0;
            c = 1;
            d = 0;
            e = 0;
            f = 1;
            g = 0;
            dp = 1;
            break;
        case 3:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 1;
            f = 1;
            g = 0;
            dp = 1;
            break;
        case 4:
            a = 1;
            b = 0;
            c = 0;
            d = 1;
            e = 1;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 5:
            a = 0;
            b = 1;
            c = 0;
            d = 0;
            e = 1;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 6:
            a = 0;
            b = 1;
            c = 0;
            d = 0;
            e = 0;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 7:
            a = 0;
            b = 0;
            c = 0;
            d = 1;
            e = 1;
            f = 1;
            g = 1;
            dp = 1;
            break;
        case 8:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 0;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 9:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 1;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 10:
            a = 0;
            b = 0;
            c = 0;
            d = 1;
            e = 0;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 11:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 0;
            f = 0;
            g = 0;
            dp = 0;
            break;
        case 12:
            a = 0;
            b = 1;
            c = 1;
            d = 0;
            e = 0;
            f = 0;
            g = 1;
            dp = 1;
            break;
        case 13:
            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 0;
            f = 0;
            g = 1;
            dp = 0;
            break;
        case 14:
            a = 0;
            b = 1;
            c = 1;
            d = 0;
            e = 0;
            f = 0;
            g = 0;
            dp = 1;
            break;
        case 15:
            a = 0;
            b = 1;
            c = 1;
            d = 1;
            e = 0;
            f = 0;
            g = 0;
            dp = 1;
            break;
    }
}
