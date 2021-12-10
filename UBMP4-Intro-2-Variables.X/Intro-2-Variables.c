/*==============================================================================
 Project: Intro-2-Variables
 Date:    May 16, 2021
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (Boolean, or bool) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world toggle button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions
#include    "Throne.h"

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
const unsigned char maxCount = 50;

// Program variable definitions
bool SW2Pressed = false;
unsigned char count = 0;

int jingle_bell[20] = {ND4, B4, A4, G4, ND4,
                       ND4, B4, A4, G4, E4,
                       E4, C5, B4, A4, F4,
                       D5, D5, C5, A4, B4};
        
int jingle_bell_1[24] = {ND4, B4, A4, G4, ND4,
                         ND4, B4, A4, G4, E4,
                         E4, C5, B4, A4, D5, D5, D5, D5,
                         E5, D5, C5, A4, G4, D5};

int jingle_bell_2[6] = {B4, B4, B4, B4, B4, B4};

int jingle_bell_3[19] = {B4, D5, G4, A4, B4,
                        C5, C5, C5, C5, C5, B4, B4, B4,
                        B4, A4, A4, B4, A4, D5};

int jingle_bell_4[5] = {D5, D5, C5, A4, G4};

void JingleBell(char loop) {
    for(char c = 0; c < loop; c++) {
        for(char i = 0; i < 20; i++) {
            if(i < 4 || (i > 4 && i < 9) || (i > 9 && i < 14) || (i > 14 && i < 19)) NOTE_PLAYER(jingle_bell[i], 250);
            else if(i == 4 || i == 9 || i == 14 || i == 19) NOTE_PLAYER(jingle_bell[i], 350);
        }
        __delay_ms(200);
        for(char i = 0; i < 25; i++) {
            if(i < 4 || (i > 4 && i < 9) || (i >= 10 && i <= 13) || (i >= 18 && i <= 21)) NOTE_PLAYER(jingle_bell_1[i], 250);
            else if(i == 4 || i == 9 || i == 21 || i == 22) NOTE_PLAYER(jingle_bell_1[i], 350);
            else if(i >= 14 && i <= 17) {
                NOTE_PLAYER(jingle_bell_1[i], 250);
                __delay_ms(20);
            }
        }
        __delay_ms(200);

        NOTE_PLAYER(jingle_bell_2[0], 250);
        __delay_ms(10);
        NOTE_PLAYER(jingle_bell_2[1], 250);
        __delay_ms(30);
        NOTE_PLAYER(jingle_bell_2[2], 350);
        __delay_ms(50);
        NOTE_PLAYER(jingle_bell_2[3], 250);
        __delay_ms(10);
        NOTE_PLAYER(jingle_bell_2[4], 250);
        __delay_ms(30);
        NOTE_PLAYER(jingle_bell_2[5], 350);
        for(char i = 0; i < 19; i++) {
            if(i < 4) NOTE_PLAYER(jingle_bell_3[i], 250);
            else if(i == 4) NOTE_PLAYER(jingle_bell_3[i], 350);
            else if(i > 4 && i < 9) {
                NOTE_PLAYER(jingle_bell_3[i], 250);
                __delay_ms(20);
            } else if(i > 9 && i < 13) {
                NOTE_PLAYER(jingle_bell_3[i], 250);
                __delay_ms(20);
            } else if(i > 12 && i < 17) {
                if(i == 13 || i == 16) NOTE_PLAYER(jingle_bell_3[i], 250);
                else if(i > 13 && i < 16) {
                    NOTE_PLAYER(jingle_bell_3[i], 250);
                    __delay_ms(20);
                } 
            } else if(i >= 17) {
                NOTE_PLAYER(jingle_bell_3[i], 350);
            }
        }
        __delay_ms(200);

        NOTE_PLAYER(jingle_bell_2[0], 250);
        __delay_ms(10);
        NOTE_PLAYER(jingle_bell_2[1], 250);
        __delay_ms(30);
        NOTE_PLAYER(jingle_bell_2[2], 350);
        __delay_ms(50);
        NOTE_PLAYER(jingle_bell_2[3], 250);
        __delay_ms(10);
        NOTE_PLAYER(jingle_bell_2[4], 250);
        __delay_ms(30);
        NOTE_PLAYER(jingle_bell_2[5], 350);
        for(char i = 0; i < 13; i++) {
            if(i < 4) NOTE_PLAYER(jingle_bell_3[i], 250);
            else if(i == 4) NOTE_PLAYER(jingle_bell_3[i], 350);
            else if(i > 4 && i < 9) {
                NOTE_PLAYER(jingle_bell_3[i], 250);
                __delay_ms(20);
            } else if(i > 9 && i < 13) {
                NOTE_PLAYER(jingle_bell_3[i], 250);
                __delay_ms(20);
            }
        }
        for(char i = 0; i < 5; i++) {
            if(i < 2) {
                NOTE_PLAYER(jingle_bell_4[i], 250);
                __delay_ms(20);
            } else if(i > 1 && i < 4) NOTE_PLAYER(jingle_bell_4[i], 250);
            else if(i == 4) NOTE_PLAYER(jingle_bell_4[i], 350);
        }
        __delay_ms(300);
    }
}

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
       /*
        if(SW2 == 0 && !SW2Pressed) {
            SW2Pressed = true;
            LED3 = 1;
            SW2Count++;
        } else {
            LED3 = 0;
            SW2Pressed = false;
        }

        if(SW5 == 0 && !SW5Pressed) {
            SW5Pressed = true;
            LED6 = 1;
            SW5Count++;
        } else {
            LED6 = 0;
            SW5Pressed = false;
        }

        if(SW2Count >= maxCount) {
            LED4 = 1;
        } else if(SW5Count >= maxCount) {
            LED5 = 1;
        }

        if(SW3 == 0 || SW4 == 0) {
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            SW2Count = 0;
            SW5Count = 0;
        }
        */
        
        /*
        if(SW2 == 0 && !SW2Pressed) {
            LED3 = 1;
            SW2Pressed = true;
        } else if(SW2 == 0 && SW2Pressed) {
            LED3 = 0;
            SW2Pressed = false;
        }
        */

        /*
        if(SW2 == 0) {
            LED3 = 1;
            __delay_ms(1000);
            count++;
        }
        
        if(count > 5) {
            LED3 = 0;
            LED4 = 1;
        }

        if(SW3 == 0) {
            LED4 = 0;
            LED3 = 0;
            count = 0;
        }
        */

        // if(!SW2Pressed && SW2 == 0) {
        //     SW2Pressed = true;
        //     LED2 = !LED2;
        //     __delay_ms(50);
        // }
        
        // if(SW2Pressed && SW2 == 1) {
        //     SW2Pressed = false;
        //     __delay_ms(50);
        // }

        //Current last note: Finished

        if(BUTTON_PRESSED(3)) {
            JingleBell(2);
        }

        // Add a short delay to the main while loop.
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Program Analysis
 * 
 * 1. The 'SW2Count' variable is created within RAM as an 8-bit memory location
 *    by the declaration: 'unsigned char SW2Count = 0;'
 *    What is the the maximum value an 8-bit variable can store?
 *    What are some benefits and drawbacks of using 8-bit variables in an 8-bit
 *    microcontroller?
 *    256
 *    The microcontroller would run faster and easier for the microcontroller to process. (Benefit)
 * 
 * 2. The constant 'maxCount' is defined using a declaration similar to that
 *    used for the SW2Count variable, but with the 'const' prefix added in the
 *    declaration. Can you think of some advantages of declaring a constant like
 *    this, using a separate statement above the main code, rather than just
 *    embedding the value of the constant where it is needed in the code?
 *    The advantage is that you can use this variable everywhere inside your file.
 *
 * 3. This program should light LED D3 every time SW2 is pressed, and light
 *    LED D4 once the count reaches 50. Try it, and count how many times you
 *    have to press the button until LED D4 turns on. SW3 resets the count so
 *    you can perform repeated attempts.
 * 
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: try pressing and releasing the button at different rates of speed.)
 *    The number of times that you have to press until LED D4 turns on are different with
 *    different rates of speed. Because the program increase the count by one every time the
 *    code executed, and the SW2 is pressed.
 * 
 * 4. Modify the second 'if' structure to add the else block, as shown below:

        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D4. LED D4 should stay on continuously while the value of SW2Count is
 *    higher than maxCount. If LED D4 turns off, what can you infer about the
 *    value of the SW2Count variable? Can you explain what happens to the
 *    SW2Count variable as the SW2 button is held?
 *    The SW2Count variable is less than the maxCount variable if LED D4 turns off.
 *    As the SW2 button is held, the SW2Count is continuously increased.
 * 
 * 5. We can set a limit on the SW2Count variable by encapsulating its increment
 *    statement inside a conditional statement. In your program, replace the
 *    line 'SW2Count = SW2Count + 1;' with the code, below:
 
            if(SW2Count < 255)
            {
                SW2Count += 1;
            }

 *    This code demonstrates the use of the assignment operator '+=' to shorten
 *    the statement 'SW2Count = SW2Count + 1;' The same operation is performed,
 *    but in a more compact form. After adding this code, what is the maximum
 *    value that the SW2Count variable will reach? How does this affect the
 *    operation of LED D4 when SW2 is held?
 *    The maximum value that SW2Count can reach is 254.
 *    It doesn't seem to affect the operation of LED D4 when SW2 is held.
 *
 * 6. The fundamental problem with this program is that pushbutton SW2 is sensed
 *    in each cycle of the loop and if its state is read as pressed, another
 *    count is added to the SW2Count variable. Rather than responding to state,
 *    the program needs to be made to respond only to each new press -- in other
 *    words, a *change* of SW2 state, from not-pressed to pressed. Doing this
 *    requires the use of another variable to store the prior state of SW2, so
 *    that its current state can be evaluated as being the same, or different
 *    from its state in the previous loop. Replace the initial if-else condition 
 *    with the following two if conditions:

        // Count new SW2 button presses
        if(SW2 == 0 && SW2Pressed == false)
        {
            LED3 = 1;
            SW2Pressed = true;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
        }

        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 *    These two if conditions make use of the Boolean SW2Pressed variable to
 *    store the current state of SW2 for the next cycle of the main while loop.
 *    Boolean variables can store 0/false or 1/true, interchangeably. The first
 *    if condition, above, compares the current SW2 state with the previously
 *    stored SW2Pressed variable so that a new count is only added when the SW2
 *    button is pressed and SW2Pressed is false. In the if structure, SW2Pressed
 *    is set to true before a count is added. The following if structure resets
 *    SW2Pressed to false when the button is released. Try the code to verify
 *    that it works.
 * 
 *    The conditional statement in the first if condition can also be written:

        if(SW2 == 0 && !SW2Pressed)

 *    The '!SW2Pressed' expression is read as 'not SW2Pressed' and is equivalent
 *    to SW2Pressed being false. Similarly, using the variable name by itself
 *    (eg. SW2Pressed) in a condition is equivalent to SW2Pressed being true.
 * 
 * 7. A pushbutton's logic state can also be defined as a word in a similar way
 *    to a variable (eg. the way SW2Pressed represents 1 or 0, or true or false)
 *    which can help to make the code more readable. Add the following lines to
 *    the 'Program constant definitions' section at the top of the code:
 
 #define pressed 0
 #define notPressed 1

 *    Now, instead of comparing the state of the button to 0 or 1, the button
 *    input can be compared with the named definition for 0 or 1, making the
 *    program more readable at the expense of hiding the actual switch value in
 *    the definition statement instead of making it obvious in the if structure.
 *    Try it in your code, and modify the SW3 reset button to work with the same
 *    pressed adn notPressed definitions.
 
        // Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 * 
 * Programming Activities
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Let's use SW5 for the second player's pushbutton so that
 *    the two players can face each other from across the UBMP4 circuit board.
 *    Duplicate SW2Count and SW2Pressed to create SW5Count and SW5Pressed
 *    variables. Then, duplicate the required if condition structures and modify
 *    the variable names to represent the second player. LED D4 can still light
 *    if player 1 is the first to reach maxCount. Use LED D5 to show if the
 *    second palyer wins. Use a logical condition statement to reset the game
 *    by clearing the count and turning off the LEDs if either SW3 or SW4 is
 *    pressed.
 *    Done
 * 
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button will 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)
 *    Done
 * 
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just as the first
 *    program unitentionally did, because of the loop structure). Make a
 *    multifunction button that lights one LED when a button is pressed, and
 *    lights a second LED after the button is held for more that one second.
 *    Done
 * 
 * 4. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, but switch bounce can be an issue in a toggle button
 *    because the speed of a microcontroller lets it see each bounce as a new,
 *    separate event. Use a variable to count the number of times a pushbutton
 *    is pressed and display the count on the LEDs. Use a separate pushbutton
 *    to reset the count and turn off the LEDs so that the test can be repeated.
 *    To determine if your switches bounce, try pressing them at various speeds
 *    and using different amounts of force.
 *    They seem to bounce.
 * 
 * 5. Did your pushbuttons bounce? Can you think of a technique similar to the
 *    multi-function button that could be implemented to make your program
 *    ignore switch bounces. Multiple switch activations within a 50ms time span
 *    might indicate switch bounce and can be safely ignored.
 *    We can prevent that by adding a delay, I guess.
 */
