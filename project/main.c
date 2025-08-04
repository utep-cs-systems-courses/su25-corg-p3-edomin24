#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "statemachines.h"
#include "switch.h"

void wdt_c_handler() {
  state_machine_update();
}

void main() {
  configureClocks();
  lcd_init();
  switch_init();
  enableWDTInterrupts();
  or_sr(0x8); // enable interrupts

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      draw_screen();
    }
    or_sr(0x10); // sleep until next interrupt
  }
}

