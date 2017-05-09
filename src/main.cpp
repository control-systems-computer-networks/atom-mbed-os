#include "mbed.h"
#include "C12832.h"
#include "MMA7660.h"

// examples lifted from
// https://developer.mbed.org/cookbook/mbed-application-shield
void print_char(char c = '*') {
    printf("%c", c);
    fflush(stdout);
}

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut red_led(D5);
DigitalOut blue_led(D8);
DigitalOut green_led(D9);

DigitalIn up(A2);
DigitalIn down(A3);
DigitalIn left(A4);
DigitalIn right(A5);
DigitalIn fire(D4);

void led2_thread(void) {
    led2 = !led2;
}

// Using Arduino pin notation
// lcd library lifted from https://developer.mbed.org/users/chris/code/C12832/
C12832 lcd(D11, D13, D12, D7, D10);
MMA7660 MMA(D14,D15);//in platform IO libraries, the same as
    // https://developer.mbed.org/users/Sissors/code/MMA7660/



AnalogIn pot1 (A0);
AnalogIn pot2 (A1);
PwmOut spkr(D6);

void sweep(void){
    for (float i=2000.0; i<10000.0; i+=100) {
        spkr.period(1.0/i);
        spkr=0.5;
        wait(0.02);
    }
    spkr=0.0;
}
void js(void)
{
    red_led =  !up;
    blue_led = !down;
    green_led= !left ;
    if(right) sweep();
}

int main() {
    Ticker thread, jsa;
    thread.attach(led2_thread, 1);
    jsa.attach(js,0.1);

    lcd.cls();
    lcd.rect(0,0, 127,31, 1);
    lcd.locate(1,3);
    lcd.printf("mbed application shield!");


    while (true) {
        lcd.locate(1,3);
        lcd.printf("Pots = %.2f  %.2f", (float)pot1, (float)pot2);
        led1 = !led1;
        lcd.locate(2,14);
        lcd.printf("x=%.2f y=%.2f z=%.2f",MMA.x(), MMA.y(), MMA.z());
        wait(0.5);

    }
}
