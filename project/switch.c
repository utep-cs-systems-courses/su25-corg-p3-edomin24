#include <msp430.h>
#include "switch.h"

char s1_state, s2_state, s3_state, s4_state;
char switch_state_changed = 0;
char current_state = -1;

static char
switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void
switch_init()
{
  P2REN |= SWITCHES;
  P2IE  |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  s1_state = (p2val & S1) ? 0 : 1;
  s2_state = (p2val & S2) ? 0 : 1;
  s3_state = (p2val & S3) ? 0 : 1;
  s4_state = (p2val & S4) ? 0 : 1;

  if(s1_state)
    current_state = 0;
  else if (s2_state)
    current_state = 1;
  else if (s3_state)
    current_state = 2;
  else if (s4_state)
    current_state = 3;
  else
    current_state = -1;  /* no switch activated */

  switch_state_changed = 1;
    
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
