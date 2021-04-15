/*==============================================================================
 Project: Intro-2-Variables
 Date:    April 15, 2021
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (bool, or Boolean) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world toggle button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-FFF' under "Memory model" pull-down.
// TODO Set linker code offset to '1000' under "Additional options" pull-down.

// Program constant definitions
const unsigned char maxCount = 50;

// Program variable definitions
unsigned char p1Count = 0;
bool p1Pressed = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        // Count SW2 button presses
        if(SW2 == 0)
        {
            LED3 = 1;
            p1Count = p1Count + 1;
        }
        else
        {
            LED3 = 0;
        }
        
        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            p1Pressed = false;
        }
        
        if(p1Count >= maxCount)
        {
            LED4 = 1;
        }
        
        // Reset count and turn off LED D4
        if(SW3 == 0)
        {
            LED4 = 0;
            p1Count = 0;
        }
        
        // Add a short delay to the main while loop.
        __delay_ms(10);
        
        // Connect to USB and press and release SW1 to start the USB bootloader.
        // After LED D1 flashes, UBMP4 will appear as USB drive 'PIC16F145X'.
        if(SW1 == 0)
        {
            asm("reset");
        }
    }
}

/* Program Analysis
 * 
 * 1. The 'p1Count' variable is created within RAM as an 8-bit memory location
 *    by the 'unsigned char p1Count = 0;' declaration. What is the the maximum
 *    value an 8-bit variable can store? What are some benefits of using 8-bit
 *    variables in an 8-bit microcontroller?
 * 
 * 2. The constant 'maxCount' is defined using a declaration similar to that
 *    used for the p1Count variable, but with the 'const' prefix added in the
 *    declaration. Can you think of some advantages of declaring a constant like
 *    this, using a separate statement above the main code, rather than just
 *    embedding the value of the constant into the code where it is used?
 * 
 * 3. This program should light LED D3 every time SW2 is pressed, and light
 *    LED D4 once the count reaches 50. Try it, and count how many times you
 *    have to press the button until LED D4 turns on. SW3 resets the count so
 *    you can perform repeated attempts.
 * 
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: try pressing and releasing the button at different rates of speed.)
 * 
 * 4. Modify the second 'if' structure to add the else block, as shown below:

        if(p1Count >= maxCount)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D4. LED D4 should stay on continuously when the value of p1Count is
 *    higher than maxCount. If LED D4 turns off, what can be inferred about the
 *    value of the p1Count variable? Can you explain what happens to the
 *    p1Count variable as the SW2 button is held?
 * 
 * 5. We can set a limit on the p1Count variable by encapsulating its increment
 *    statement inside a conditional statement. In your program, replace the
 *    line 'p1Count = p1Count + 1;' with the code, below:
 
            if(p1Count < 255)
            {
                p1Count += 1;
            }

 *    This code demonstrates the use of the assignment operator '+=' to shorten
 *    the statement 'p1Count = p1Count + 1;' The same operation is performed,
 *    namely 1 bing added to the current p1Count value, but in a more compact
 *    form. Adding this code, what is the maximum value that p1Count will reach?
 *    How does this affect LED D4 when SW2 is held?
 *
 * 6. The fundamental problem with this program is that pushbutton SW2 is sensed
 *    each cycle through the loop and, if its state is read as pressed, another
 *    count is added to the p1Count variable. Rather than responding to state,
 *    the program needs to be made to respond only to each new press -- in other
 *    words, a *change* of SW2 state, from not pressed to pressed. Doing this
 *    requires the use of another variable to store the prior state of SW2, so
 *    that its current state can be evaluated as being the same, or different
 *    from its state in the previous loop. Replace the initial if-else condition 
 *    with the following two if conditions:

        // Count new SW2 button presses
        if(SW2 == 0 && p1Pressed == false)
        {
            LED3 = 1;
            if(p1Count < 255)
            {
                p1Count = p1Count + 1;
            }
            p1Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            p1Pressed = false;
        }
        
 *    These two if conditions make use of the Boolean p1Pressed variable to
 *    store the current state of SW2 for the next cycle of the main while loop.
 *    Boolean variables can store 0/false or 1/true, interchangeably. The first
 *    if condition, above, compares the current SW2 state with the previously
 *    stored p1Pressed variable so that a new count is only added when the SW2
 *    button is pressed and p1Pressed is false. At the end of this if structure,
 *    p1Pressed is set to true. The next if structure resets p1Pressed to false
 *    whenever the button is released. Try the code to make sure it works.
 * 
 *    The conditional statement in the first if condition can also be written:

        if(SW2 == 0 && !p1Pressed)

 *    The '!p1Pressed' expression is read as 'not p1Pressed' and is equivalent
 *    to false. Using just the variable name (eg. p1Pressed) in a condition is
 *    equivalent to true.
 * 
 * Programming Activities
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Duplicate p1Count and p1Pressed to create p2Count and
 *    p2Pressed variables. Then, duplicate the required if condition structures
 *    and change the variable names to the second player's set. Use SW5 for the 
 *    second player's pushbutton so that the two players can face each other
 *    from across the board. LED D4 can still light if player 1 is the first to
 *    reach the maxCount. To be able to tell which player wins, have the game
 *    light LED D5 if player 2 is the first one to reach maxCount. Use a logical
 *    condition statement to reset the game by clearing the count and turning
 *    off the LEDs if either SW3 or SW4 is pressed.
 * 
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button will 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)
 * 
 * 3. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in your room light is not a
 *    big concern, but can be an issue in the toggle button because the speed of
 *    a microcontroller lets it see each bounce as a separate event. Use a 
 *    variable to count the number of times a pushbutton is pressed and display
 *    the count on the LEDs. Use a separate pushbutton to reset the count and 
 *    turn off the LEDs so that the test can be repeated. To see if your
 *    switches bounce, try pressing them at various speeds and using different
 *    amounts of force.
 * 
 * 4. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just like the first
 *    program did, by poor design, before it was modified). Make a multifunction
 *    button that lights one LED when a button is pressed, and a second LED
 *    after the button is held for more that one second.
 * 
 * 5. Did your pushbuttons bounce? Think of a technique similar to the multi-
 *    function button that could be implemented to ignore switch bounce in
 *    your program.
 */
