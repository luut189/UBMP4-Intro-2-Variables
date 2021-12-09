#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions
#include    "Throne.h"

void NOTE_PLAYER(long duration, int length) {
    for(int i = length; i != 0; i--) {
		BEEPER = !BEEPER;
		for(int j = duration; j != 0; j--);
	}
}