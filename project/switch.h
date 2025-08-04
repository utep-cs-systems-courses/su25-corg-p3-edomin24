#ifndef switches_included
#define switches_included

#define S1 BIT0 
#define S2 BIT1 
#define S3 BIT2 
#define S4 BIT3

#define SWITCHES (S1 | S2 | S3 | S4)

void switch_init();
void switch_interrupt_handler();

extern char s1_state, s2_state, s3_state, s4_state;
extern char switch_state_changed;
extern char current_state;

#endif //included
