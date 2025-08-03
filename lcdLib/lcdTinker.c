/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();

  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  u_char cRow = height/2, cCol = width/2;
  int col = 0, row = 0;

  u_char i = 0;
  while (i < 40){
    drawPixel(cCol + 40, cRow + i, COLOR_WHITE);
    drawPixel(cCol + 40, cRow - i, COLOR_WHITE);

    drawPixel(cCol - 40, cRow + i, COLOR_WHITE);
    drawPixel(cCol - 40, cRow - i, COLOR_WHITE);
    i++;
  }
}
