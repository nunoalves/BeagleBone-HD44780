#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"
#include "beagle_hd44780.h"

/** 
 *  @brief     This program (example_04.c) describes how to interface with a 
 *             HD44780 display in a BeagleBone 
 *  @details   Compile, and run, this code on the beagleBone terminal with the 
 *             commands: 
 *			   rm -f a.out ; gcc -c beagle_gpio.c ; gcc -c beagle_hd44780.c 
 *    		   gcc beagle_gpio.o beagle_hd44780.o example_04.c ; ./a.out
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
	//adding a simple description for each pin
	const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};

	struct gpioID enabled_gpio[6];    
    initialize_Screen(enabled_gpio,selectedPins);	
	
	//clear screen
	clear_Screen(enabled_gpio);

	//types "hi!" to the screen
	stringToScreen("hi!",enabled_gpio);

	//go to the bottom line and write something else
	//note: goto_ScreenLine(0,enabled_gpio) will go to the top line.
	goto_ScreenLine(1,enabled_gpio);
	stringToScreen("there!",enabled_gpio);

	//really... don't forget to terminate the screen
    terminate_Screen(enabled_gpio,selectedPins);
}