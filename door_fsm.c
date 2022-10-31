/********************************************************************************
* door_fsm.c: Demonstration av tillståndsmaskin för implementering nästa lektion.
********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>

/* Bogusmakron för demonstrationen (ersätt med riktiga vid implementering): */
#define OPEN_BUTTON_IS_PRESSED 0
#define CLOSE_BUTTON_IS_PRESSED 1 
#define LOCK_BUTTON_IS_PRESSED 2 
#define RESET_BUTTON_IS_PRESSED 3

/********************************************************************************
* door_state: Datatyp för lagring av dörrens aktuella tillstånd.
********************************************************************************/
enum door_state
{
   DOOR_STATE_OPEN,
   DOOR_STATE_CLOSED,
   DOOR_STATE_LOCKED,
   DOOR_STATE_ERROR 
};

static enum door_state state = DOOR_STATE_CLOSED; /* Lagrar dörrens tillstånd. */

/********************************************************************************
* ISR (INT0_vect): Avbrottsrutin, som anropas vid nedtryckning av reset-knappen
*                  ansluten till pin 2 (PORTD2). Vid reset återställs dörrens
*                  tillstånd till startläget (stängt tillstånd).
********************************************************************************/
ISR (INT0_vect) 
{
   fsm_reset();
   return;
}

/********************************************************************************
* ISR (PCINT0_vect): Avbrottsrutin för PCI-avbrott på I/O-port B, som anropas 
*                    vid uppsläppning eller nedtryckning av tryckknappar
*                    anslutna till pin 11 - 13 (PORTB3 - PORTB5). Om någon av 
*                    dessa knappar trycks ned så uppdateras dörrens tillstånd.
********************************************************************************/
ISR (PCINT0_vect)
{
   if (OPEN_BUTTON_IS_PRESSED || CLOSE_BUTTON_IS_PRESSED || LOCK_BUTTON_IS_PRESSED)
   {
      fsm_update();
   }
}

/********************************************************************************
* fsm_reset: Återställer dörren till startläget, vilket är stängd.
********************************************************************************/
void fsm_reset(void)
{
   state = DOOR_STATE_CLOSED;
   return;
}

/********************************************************************************
* fsm_uppdate: Uppdaterar dörrens tillstånd utefter aktuellt tillstånd samt
*              vilken tryckknapp som trycks ned. 
*
*              I feltillstånd sker ingen uppdatering oavsett nedtryckning av
*              tryckknappar för att öppna, stänga eller låsa dörren. Dörren
*              måste återställas innan uppdatering kan ske i vanlig ordning.
*
*              Om dörrens tillstånd försätts i ett icke definierat tillstånd
*              så återställs dörren direkt. 
********************************************************************************/
void fsm_update(void)
{
    switch (state) 
    {
       case DOOR_STATE_OPEN:
       {
          if (CLOSE_BUTTON_IS_PRESSED)
          {
             state = DOOR_STATE_CLOSED;
          }
          else if (LOCK_BUTTON_IS_PRESSED)
          {
             state = DOOR_STATE_ERROR;
          }
          
          break;
       }
       
       case DOOR_STATE_CLOSED:
       {
          if (OPEN_BUTTON_IS_PRESSED)
          {
             state = DOOR_STATE_OPEN;
          }
          else if (LOCK_BUTTON_IS_PRESSED)
          {
              state = DOOR_STATE_LOCKED;
          }
          
          break;
       }
       
       case DOOR_STATE_LOCKED:
       {
           if (CLOSE_BUTTON_IS_PRESSED)
           {
              state = DOOR_STATE_CLOSED;
           }
           else if (OPEN_BUTTON_IS_PRESSED)
           {
              state = DOOR_STATE_ERROR;
           }
           
           break;
       }
       
       case DOOR_STATE_ERROR: 
       {
          break;
       }
       
       default: 
       {
          fsm_reset();
          break;
       }
    }
    
    return;
}

int main(void)
{
    /* Konfigurera I/O-portar samt aktivera avbrott vid start. */
    return 0;
}
