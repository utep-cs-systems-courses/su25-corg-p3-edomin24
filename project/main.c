#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define S1 BIT1
#define S2 BIT2
#define S3 BIT3
#define S4 BIT4

#define SWITCHES (S1 | S2 | S3 | S4)

#define LED_GREEN BIT6
#define BUZZER BIT6

char redrawScreen = 0;

char *symbols[] = {":)", ":(",":D",":|",">:)"};
u_int colors[] = {COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_ORANGE, COLOR_RED};

short symbolIndex = 0;
short colorIndex = 0;
short posX = 60;
short posY = 60;

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  P2IES |= SWITCHES;
  P2IFG &= ~SWITCHES;
}

void led_init(){
  P1DIR |= LED_GREEN;
  P1OUT &= ~LED_GREEN;
}

void buzzer_init(){
  P2DIR |= BUZZER;
  P2SEL &= ~BUZZER;
  P2OUT &= ~BUZZER;
}

void buzzer_beep(){
  P2OUT |= BUZZER;
  __delay_cycles(5000);
  P2OUT &= ~BUZZER;
}

void wdt_c_handler(){
  static char debounce = 0;
  if (++debounce < 25) return;
  debounce = 0;

  char p2val = P2IN ^ SWITCHES;

  if(p2val & S1){
    symbolIndex = (symbolIndex+1) % (sizeof(symbols) / sizeof(symbols[0]));
    buzzer_beep();
  }
  if (p2val & S2){
    colorIndex = (colorIndex +1) % (sizeof(colors) / sizeof(colors[0]));
    buzzer_beep();
  }

  if(p2val & S3){
    if (posX > 0) posX -= 6;
    buzzer_beep();
  }

  if (p2val & S4){
    if(posX < screenWidth -11) posX += 6;
    buzzer_beep();
  }

  redrawScreen = 1;
}
  

void main(){
  configureClocks();
  lcd_init();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8);
  
  u_char colorIndex = 0;

  u_int colors[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_ORANGE};

  while(1){
    P1OUT |= LED_GREEN;
    if(redrawScreen){
      redrawScreen = 0;
      clearScreen(colors[colorIndex]);
      drawString11x16(posX, posY, symbols[symbolIndex], COLOR_WHITE, colors[colorIndex]);
    }

    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
  }
  
}
