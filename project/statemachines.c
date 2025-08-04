#include "statemachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switch.h"
#include <msp430.h>

unsigned char redrawScreen = 1;
unsigned char sm_state = 0;
unsigned char counter = 0;


char *symbols[] = {":)", ":(", ":D", ":|", ">:)"};
u_int colors[] = {COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_ORANGE, COLOR_RED};
short symbolIndex = 0;
short colorIndex = 0;

short posX = 10;
short posY = 50;
short dx = 2;

void state_machine_update() {
  counter++;
  if (s1_state) { // Switch 1: symbol++
    symbolIndex = (symbolIndex + 1) % (sizeof(symbols) / sizeof(symbols[0]));
  }
  if (s2_state) { // Switch 2: symbol--
    symbolIndex--;
    if (symbolIndex < 0) symbolIndex = (sizeof(symbols) / sizeof(symbols[0])) - 1;
  }
  if (s3_state) { // Switch 3: bg++
    colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
  }
  if (s4_state) { // Switch 4 bg--
    colorIndex--;
    if (colorIndex < 0) colorIndex = (sizeof(colors) / sizeof(colors[0])) - 1;
  }

  posX += dx;
  if (posX > screenWidth - 11 || posX < 0) {
    dx = -dx; // bounce at edges
  }
  redrawScreen = 1;
}

void draw_screen() {
  clearScreen(colors[colorIndex]);
  drawString11x16(posX, posY, symbols[symbolIndex], COLOR_WHITE, colors[colorIndex]);
}
