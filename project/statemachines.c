#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "statemachines.h"
#include "switch.h"

unsigned char redrawScreen = 1;
unsigned char counter = 0;


char *symbols[] = {":)", ":(", ":D", ":|", ">:)"};
u_int colors[] = {COLOR_RED,
		  COLOR_ORANGE,
		  COLOR_YELLOW,
		  COLOR_GREEN,
		  COLOR_CYAN,
		  COLOR_BLUE,
		  COLOR_PURPLE,
		  COLOR_MAGENTA,};

short symbolIndex = 0;
short colorIndex = 0;

short posX = screenWidth  /2;
short posY = screenHeight /2;
short dx = 1;
short dy = 1;

static char prev_state = -1;

void state_machine_update() {
  counter++;

  if (current_state != prev_state) {
    switch (current_state) {
    case 0: // symbol++
      symbolIndex = (symbolIndex + 1) % (sizeof(symbols) / sizeof(symbols[0]));
      buzzer_set_period(1000);
      break;

    case 1: // symbol--
      symbolIndex--;
      if (symbolIndex < 0) symbolIndex = (sizeof(symbols) / sizeof(symbols[0])) - 1;
      buzzer_set_period(1500);
      break;

    case 2: // bg--
      colorIndex--;
      if (colorIndex < 0){
	colorIndex =  (sizeof(colors) / sizeof(colors[0])) - 1;
      }
      buzzer_set_period(1000);
      break;
      
    case 3: // bg++
      colorIndex = (colorIndex +1) % (sizeof(colors) / sizeof(colors[0]));
      buzzer_set_period(1500);
      break;

    default:
      buzzer_set_period(0);
      break;
    }
  }

  prev_state = current_state;
  posX += dx;
  posY += dy;

  if (posX <= 0) {
    posX = 0;
    dx = 1;
  }

  else if (posX >= screenWidth -11) {
    posX = screenWidth  - 11;
    dx = -1;
  }

  if (posY <= 0){
    posY = 0;
    dy = 1;
  }

  else if (posY >= screenHeight - 16){
    posY = screenHeight -16;
    dy = - 1;
  }
  redrawScreen = 1;
}

void draw_screen() {
  if (posX < 0) posX = 0;
  if (posX > screenWidth - 11) posX = screenWidth -11;
  if (posY < 0) posY = 0;
  if (posY > screenHeight - 16) posY = screenHeight - 16;
  
  clearScreen(colors[colorIndex]);
  drawString11x16(60, 60, symbols[symbolIndex], COLOR_WHITE, colors[colorIndex]);
}
