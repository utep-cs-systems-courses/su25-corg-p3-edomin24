#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "statemachines.h"
#include "switch.h"
#include "buzzer.h"

#define LED_GREEN BIT6

void wdt_c_handler() {
  state_machine_update();
}

void main() {
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8); // enable interrupts

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      draw_screen();
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10); // sleep until next interrupt
    P1OUT |= LED_GREEN;
  }
}

