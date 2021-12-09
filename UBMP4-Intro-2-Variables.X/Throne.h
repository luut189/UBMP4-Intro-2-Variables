#define BUTTON_PRESSED(n)   SW##n == 0
#define LED_ON(n)           LED##n = 1
#define LED_OFF(n)          LED##n = 0

void NOTE_PLAYER(long, int);
void DELAY(long);

#define ND4     1702
#define B4      1012
#define A4      1136
#define G4      1275
#define E4      1516
#define C5      955
#define F4      1431
#define D5      851
#define E5      758