/********************************************************************************
* setup.c: Innehåller initieringsrutiner för det inbyggda systemet.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static inline void init_ports(void);
static inline void init_interrupts(void);

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
********************************************************************************/
void setup(void)
{
   init_ports();
   init_interrupts();
   return;
}

/********************************************************************************
* init_ports: Sätter lysdiodernas pinnar till utportar och sätter tryckknapparnas
*             pinnar till aktiva inportar (insignalerna blir alltid 0 eller 1).
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   PORTB = (1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3);
   return;
}

/********************************************************************************
* init_interrupts: Aktiverar PCI-avbrott på pin 11 - 13 / PORTB3 - PORTB5.
********************************************************************************/
static inline void init_interrupts(void)
{
   asm("SEI");
   PCICR = (1 << PCIE0);
   PCMSK0 = (1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3);
   return;
}