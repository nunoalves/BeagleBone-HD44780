#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"
#include "beagle_hd44780.h"

/** 
 *  @brief     This program (example_03.c) describes how to interface with a 
 *             HD44780 display in a BeagleBone 
 *  @details   Compile, and run, this code on the beagleBone terminal with the 
 *             commands: 
 *			   rm -f a.out ; gcc -c beagle_gpio.c ; gcc -c beagle_hd44780.c 
 *    		   gcc beagle_gpio.o beagle_hd44780.o example_03.c ; ./a.out
 *  @author    Nuno Alves
 *  @version   0.1
 *  @date      23/March/2011
 *  @copyright GNU Public License.
 * @return Returns a 1 upon succesful program termination
 **/ 

int main()
{
	//specifies the pins that will be used
	int selectedPins[]={P8_14,P8_12,P8_11,P8_5,P8_4,P8_3};
	const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};

	struct gpioID enabled_gpio[6];    

	//initialized the screen
    initialize_Screen(enabled_gpio,selectedPins);
	
	//clear the screen from everything that may be in there
	clear_Screen(enabled_gpio);
	printf("... just cleared screen and now waiting for 5 secs.\n");
	sleep(5);

	//writes two characters	
	charToScreen('a',enabled_gpio);
	charToScreen('b',enabled_gpio);
	printf("... typed ab and now waiting for 5 secs.\n");
	sleep(5);

	clear_Screen(enabled_gpio);

	//enables the blinking cursor
	enableBlinkingCursor(enabled_gpio);  
	charToScreen('c',enabled_gpio);
	charToScreen('d',enabled_gpio);
	charToScreen('e',enabled_gpio);
	charToScreen('g',enabled_gpio);

	printf("... cleared screen, enabled blinking and wrote more stuff.\n");
	sleep(5);
	
	//this instruction must be added or the LCD may not work as expected next
	//time... unless you reboot it.
    terminate_Screen(enabled_gpio,selectedPins);

}