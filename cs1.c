#include "p30f3012.h"
_FOSC(CSW_FSCM_OFF & FRC); // Internal 7.37MHz clock
_FWDT(WDT_OFF); // Watchdog Timer OFF
_FBORPOR(MCLR_DIS & PBOR_OFF & BORV27 & PWRT_4); // Reset Condition
_FGS(CODE_PROT_OFF & GWRP_OFF); // Code protection OFF

void getNumber(int number) {
    int num[11][8] = {
        {0, 0, 1, 1, 1, 1, 1, 1}, //0
        {0, 0, 0, 0, 0, 1, 1, 0}, //1
        {0, 1, 0, 1, 1, 0, 1, 1}, //2
        {0, 1, 0, 0, 1, 1, 1, 1}, //3
        {0, 1, 1, 0, 0, 1, 1, 0}, //4
        {0, 1, 1, 0, 1, 1, 0, 1}, //5
        {0, 1, 1, 1, 1, 1, 0, 1}, //6
        {0, 0, 0, 0, 0, 1, 1, 1}, //7
        {0, 1, 1, 1, 1, 1, 1, 1}, //8
        {0, 1, 1, 0, 1, 1, 1, 1}, //9
		{1, 0, 0, 0, 0, 0, 0, 0} //"."
    };
    int i;
    int j;
    for (i = 0; i < 8; i++) {
        LATBbits.LATB5 = num[number][i];
        for (j = 0; j < 100; j++) {

        }
        LATBbits.LATB4 = 1;
        for (j = 0; j < 100; j++) {

        }
        LATBbits.LATB4 = 0;
        for (j = 0; j < 100; j++) {

        }
    }
	//select output
    LATBbits.LATB7 = 1;
    asm("nop");
    asm("nop");
    asm("nop");
    LATBbits.LATB7 = 0;
}
