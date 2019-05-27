#include "p30f3012.h"
_FOSC(CSW_FSCM_OFF & FRC); // Internal 7.37MHz clock
_FWDT(WDT_OFF); // Watchdog Timer OFF
_FBORPOR(MCLR_DIS & PBOR_OFF & BORV27 & PWRT_4); // Reset Condition
_FGS(CODE_PROT_OFF & GWRP_OFF); // Code protection OFF

int deside;
int reflect;
int winer;
int waitTime;
int countReflect;
int gameWave;
int leave;
int push;
int countPush;
int speed;

void Wait1S(void)
// Just wait for a single second (really?)
{
    int i, j;

    for (i = 0; i < 125; i++) {
        for (j = 0; j < waitTime; j++) {
            if (!(PORTBbits.RB6) || !(PORTDbits.RD0)) {
                deside = 1;
                WaitM();
            }
            if (!(PORTDbits.RD0)) {
                winer = 1;
            } else if (!(PORTBbits.RB6)) {
                winer = 0;
            }


        }
    }
}

void Wait1SR1(void)
{
    int i, j;
    reflect = 1;
    //?????????????????
    for (i = 0; i < 125; i++) {
        for (j = 0; j < waitTime; j++) {
            //if??swich???????????
            //????????????waitTime?????
            if (!(PORTBbits.RB6)) {
                reflect = 0;
                deside = 0;
                switch (leave) {
                    case 0:
                        push = 1;
                        break;
                    case 1:
                        push = 2;
                        break;
                    case 2:
                        push = 3;
                        break;
                    default:
                        break;

                }
                if (countPush == 0) {
                    WaitM();
                    countPush = 1;
                }
            }
            if (PORTBbits.RB6) {
                switch (push) {
                    case 1:
                        leave = 1;
                        break;
                    case 2:
                        leave = 2;
                        break;
                    default:
                        break;
                }
                if (countPush == 1) {
                    WaitM();
                    countPush = 0;
                }
            }
            if (reflect == 1) {
                deside = 1;
                winer = 0;
            }
        }
    }
    if (waitTime == 30) {
        push = 3;
    }
    switch (push) {
        case 1:
            waitTime = 120;
            speed = 1;
            break;
        case 2:
            waitTime = 60;
            speed = 2;
            break;
        case 3:
            waitTime = 30;
            speed = 3;
            break;
        default:
            break;
    }
    if (deside == 0) {
        Wait1SC5();
    }
    push = 0;
    leave = 0;
}

void Wait1SR2(void)
// Just wait for a single second (really?)
{
    int i, j;
    reflect = 1;

    for (i = 0; i < 125; i++) {
        for (j = 0; j < waitTime; j++) {
            if (!(PORTDbits.RD0)) {
                reflect = 0;
                deside = 0;
                switch (leave) {
                    case 0:
                        push = 1;
                        break;
                    case 1:
                        push = 2;
                        break;
                    case 2:
                        push = 3;
                        break;
                    default:
                        break;

                }
                if (countPush == 0) {
                    WaitM();
                    countPush = 1;
                }
            }
            if (PORTDbits.RD0) {
                switch (push) {
                    case 1:
                        leave = 1;
                        break;
                    case 2:
                        leave = 2;
                        break;
                    default:
                        break;
                }
                if (countPush == 1) {
                    WaitM();
                    countPush = 0;
                }
            }
            if (reflect == 1) {
                deside = 1;
                winer = 1;
            }
        }
    }
    if (waitTime == 30) {
        push = 3;
    }
    switch (push) {
        case 1:
            waitTime = 120;
            speed = 1;
            break;
        case 2:
            waitTime = 60;
            speed = 2;
            break;
        case 3:
            waitTime = 30;
            speed = 3;
            break;
        default:
            break;
    }
    if (deside == 0) {
        Wait1SC5();
    }
    push = 0;
    leave = 0;
}

void Wait1SSolo(void)
// Just wait for a single second (really?)
{
    int i, j;
    reflect = 1;

    for (i = 0; i < 125; i++) {
        for (j = 0; j < waitTime; j++) {
            if (!(PORTDbits.RD0)) {
                reflect = 0;
                deside = 2;
                WaitM();
            }
            if (reflect == 1) {
                deside = 1;
            }
        }
    }
    if (deside == 2) {
        Wait1SC5();
    }
}

void WaitM() {
    int i;

    for (i = 0; i < 5000; i++) {
    }
}

void waitC4() {
    int i;
    for (i = 0; i < 585; i++) {

    }
}

void Wait1SC4(void)
// Just wait for a single second (really?)
{
    int i, j;

    for (i = 0; i < 40; i++) {
        for (j = 0; j < 1; j++) {
            LATCbits.LATC14 = 1; // RC13 = 1, LED ON
            waitC4();
            LATCbits.LATC14 = 0; // RC13 = 0, LED OFF
            waitC4();
        }
    }
}

void waitE() {
    int i;
    for (i = 0; i < 463; i++) {
    }
    asm("nop");
}

void Wait1SE(void)
// Just wait for a single second (really?)
{
    int i, j;

    for (i = 0; i < 40; i++) {
        for (j = 0; j < 1; j++) {
            LATCbits.LATC14 = 1; // RC13 = 1, LED ON
            waitE();
            LATCbits.LATC14 = 0; // RC13 = 0, LED OFF
            waitE();
        }
    }
}

void waitC5() {
    int i;
    for (i = 0; i < 291; i++) {

    }
}

void Wait1SC5(void)
// Just wait for a single second (really?)
{
    int i, j;

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 1; j++) {
            LATCbits.LATC14 = 1; // RC13 = 1, LED ON
            waitC5();
            LATCbits.LATC14 = 0; // RC13 = 0, LED OFF
            waitC5();
        }
    }
}

void getNumber(int wave) {
    int num[10][8] = {
        {0, 0, 1, 1, 1, 1, 1, 1}, //0
        {0, 0, 0, 0, 0, 1, 1, 0}, //1
        {0, 1, 0, 1, 1, 0, 1, 1}, //2
        {0, 1, 0, 0, 1, 1, 1, 1}, //3
        {0, 1, 1, 0, 0, 1, 1, 0}, //4
        {0, 1, 1, 0, 1, 1, 0, 1}, //5
        {0, 1, 1, 1, 1, 1, 0, 1}, //6
        {0, 0, 0, 0, 0, 1, 1, 1}, //7
        {0, 1, 1, 1, 1, 1, 1, 1}, //8
        {0, 1, 1, 0, 1, 1, 1, 1} //9
    };
    int i;
    int j;
    for (i = 0; i < 8; i++) {
        LATBbits.LATB5 = num[wave][i];
        for (j = 0; j < 100; j++) {

        }
        LATBbits.LATB4 = 1;
        for (j = 0; j < 100; j++) {

        }
        LATBbits.LATB4 = 0;
        for (j = 0; j < 100; j++) {

        }
    }
    LATBbits.LATB7 = 1;
    asm("nop");
    asm("nop");
    asm("nop");
    LATBbits.LATB7 = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;
}

void mot() {
    int i;
    int j;
    for (i = 0; i < 80; i++) {
        for (j = 0; j < 1; j++) {

        }
    }
}

void rit() {
    int i;
    int j;
    for (i = 0; i < 397; i++) {
        for (j = 0; j < 1; j++) {

        }
    }
}

void judge() {
    if (winer == 0) {
        int i;
        int j;
        for (i = 0; i < 42; i++) {
            for (j = 0; j < 1; j++) {
                LATBbits.LATB2 = 1;
                mot();
                LATBbits.LATB2 = 0;
                mot();
            }
        }
        for (i = 0; i < 3000; i++) {
            for (j = 0; j < 200; j++) {

            }
        }
        for (i = 0; i < 17; i++) {
            for (j = 0; j < 1; j++) {
                LATBbits.LATB2 = 1;
                rit();
                LATBbits.LATB2 = 0;
                rit();
            }
        }
    } else if (winer = 1) {
        int i;
        int j;
        for (i = 0; i < 17; i++) {
            for (j = 0; j < 1; j++) {
                LATBbits.LATB2 = 1;
                rit();
                LATBbits.LATB2 = 0;
                rit();
            }
        }
        for (i = 0; i < 3000; i++) {
            for (j = 0; j < 200; j++) {

            }
        }
        for (i = 0; i < 42; i++) {
            for (j = 0; j < 1; j++) {
                LATBbits.LATB2 = 1;
                mot();
                LATBbits.LATB2 = 0;
                mot();
            }
        }
    }
}

int main(void) {
    TRISB = 0x0040; // RB7 - RB0 all for output
    LATB = 0x0000; // RB7 - RB0 output '0'
    ADPCFG = 0x00ff; // RB7 - RB0 digital input enabled
    TRISC = 0x0000; // RC13 - RC15 all for output
    LATC = 0x0000; // RC13 - RC15 output '0'
    TRISD = 0x0001; // RD0 for input

    T1CON = 0x0030; // TMR1 prescaler 1:256 selected
    PR1 = (7197 - 1); // About 1sec
    TMR1 = 0;
    IFS0bits.T1IF = 0; // Flag clear
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1; // TMR1 start

    gameWave = 0;
    judge();
    push = 0;
    leave = 0;
    countPush = 0;
    speed = 0;
    while (1) {
        waitTime = 120;
        deside = 1;
        countReflect = 0;
        while (1) {
            WaitM();
            getNumber(gameWave);
            while (!(PORTBbits.RB6)) {
                gameWave = 1;
                deside = 0;
                speed = 2;
                WaitM();
            }
            while (!(PORTDbits.RD0)) {
                gameWave = 1;
                deside = 2;
                WaitM();
            }
            while (deside == 0) {
                getNumber(speed);

                if (deside == 0) {
                    LATBbits.LATB3 = 1;
                    Wait1S();
                    LATBbits.LATB3 = 0;
                }

                if (deside == 0) {
                    LATBbits.LATB1 = 1;
                    Wait1S();
                    LATBbits.LATB1 = 0;
                }
                if (deside == 0) {
                    LATBbits.LATB0 = 1;
                    Wait1SR2();
                    LATBbits.LATB0 = 0;
                }

                getNumber(speed);
                if (deside == 0) {
                    LATBbits.LATB1 = 1;
                    Wait1S();
                    LATBbits.LATB1 = 0;
                }
                if (deside == 0) {
                    LATBbits.LATB3 = 1;
                    Wait1S();
                    LATBbits.LATB3 = 0;
                }
                if (deside == 0) {
                    LATCbits.LATC13 = 1; // RC13 = 1, LED ON
                    Wait1SR1();
                    LATCbits.LATC13 = 0; // RC13 = 0, LED OFF
                }

                if (deside == 1) {
                    Wait1SE();
                    Wait1SC4();
                    waitTime = 120;
                    judge();
                }
            }
            while (deside == 2) {
                if (deside == 2) {
                    LATBbits.LATB1 = 1;
                    Wait1S();
                    LATBbits.LATB1 = 0;
                }
                if (deside == 2) {
                    LATBbits.LATB3 = 1;
                    Wait1S();
                    LATBbits.LATB3 = 0;
                }
                if (deside == 2) {
                    LATCbits.LATC13 = 1; // RC13 = 1, LED ON
                    Wait1S();
                    LATCbits.LATC13 = 0; // RC13 = 0, LED OFF
                }

                if (deside == 2) {
                    LATBbits.LATB3 = 1;
                    Wait1S();
                    LATBbits.LATB3 = 0;
                }
                if (deside == 2) {
                    LATBbits.LATB1 = 1;
                    Wait1S();
                    LATBbits.LATB1 = 0;
                }
                if (deside == 2) {
                    LATBbits.LATB0 = 1;
                    Wait1SSolo();
                    LATBbits.LATB0 = 0;
                }
                getNumber(gameWave);
                countReflect++;
                if (deside == 1) {
                    Wait1SE();
                    Wait1SC4();
                    waitTime = 120;
                    countReflect = 0;
                }

                if (countReflect >= 5 && waitTime > 40) {
                    gameWave++;
                    waitTime -= 20;
                    countReflect = 0;
                } else if (countReflect >= 5) {
                    gameWave = 6;
                    waitTime = 20;
                    countReflect = 5;
                    int i;
                    for (i = 0; i < 10; i++) {
                        Wait1SE();
                        Wait1SC4();
                    }
                    for (i = 0; i < 10; i++) {
                        Wait1SC5();
                    }
                    getNumber(gameWave);
                    while ((PORTDbits.RD0) || (PORTBbits.RB6)) {
                        if (deside == 2) {
                            LATBbits.LATB1 = 1;
                            Wait1S();
                            LATBbits.LATB1 = 0;
                        }
                        if (deside == 2) {
                            LATBbits.LATB3 = 1;
                            Wait1S();
                            LATBbits.LATB3 = 0;
                        }
                        if (deside == 2) {
                            LATCbits.LATC13 = 1; // RC13 = 1, LED ON
                            Wait1S();
                            LATCbits.LATC13 = 0; // RC13 = 0, LED OFF
                        }

                        if (deside == 2) {
                            LATBbits.LATB3 = 1;
                            Wait1S();
                            LATBbits.LATB3 = 0;
                        }
                        if (deside == 2) {
                            LATBbits.LATB1 = 1;
                            Wait1S();
                            LATBbits.LATB1 = 0;
                        }
                        if (deside == 2) {
                            LATBbits.LATB0 = 1;
                            Wait1SSolo();
                            LATBbits.LATB0 = 0;
                        }
                        getNumber(gameWave);
                        if (deside == 1) {
                            Wait1SE();
                            Wait1SC4();
                            countReflect = 0;
                            while (deside == 1) {
                                while (!(PORTDbits.RD0) && (PORTBbits.RB6)) {
                                    deside = 2;
                                    WaitM();
                                }
                                if (!(PORTDbits.RD0) && !(PORTBbits.RB6)) {
                                    deside = 3;
                                    WaitM();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0; // will never be performed...
}

