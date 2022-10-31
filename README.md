# Anteckningar 2022-10-31
Implementering av multipla PCI-avbrott på mikrodator ATmega328P, som används för att toggla lysdioder anslutna
till pin 8 - 10 (PORTB0 - PORTB2) via nedtryckning av tryckknappar anslutna till pin 11 - 13 (PORTB3 - PORTB5).

Filen header.h innehåller diverse definitioner och inkluderingsdirektiv för det inbyggt systemet.

Filen main.c innehåller implementeringen av programmet, där det inbyggda systemet initieras vid start. Här definieras också 
en togglingsfunktion för lysdioderna, som möjliggör toggling av specificerad lysdiod via ingående argument.

Filen setup.c innehåller initieringsrutiner för att konfigurera I/O-portar samt aktivera PCI-avbrott PCINT3 - PCINT5 på
tryckknapparnas pinnar 11 - 13 (PORTB3 - PORTB5).

Filen led.c innehåller en togglingsfunktion för lysdioderna, som möjliggör toggling av specificerad lysdiod.

Filen interrupts.c innehåller avbrottsrutiner för PCI-avbrott på I/O-port B (pin 8 - 13), som medför toggling av respektive lysdiod
beroende på vilken tryckknapp som trycks ned.

Filen door_fsm demonstrerar grundläggande implementering av en tillståndsmaskin för en dörr, vilket skall slutföras nästa lektion.