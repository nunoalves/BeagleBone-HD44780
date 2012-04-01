#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"
#include "beagle_hd44780.h"

/** 
 *  @brief     This program (example_02.c) cycles every single character on the
 *  LCD display.
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

	int i;
	struct gpioID enabled_gpio[6];    

	//initialized the screen
    initialize_Screen(enabled_gpio,selectedPins);
	
	//clear the screen from everything that may be in there

	for (i=65; i<122;i++)
	{
		//type every single character  characters	
    	clear_Screen(enabled_gpio);
	    charToScreen((char)i,enabled_gpio);
	    sleep(1);
	}
	//this instruction must be added or the LCD may not work as expected next
	//time... unless you reboot it.
    terminate_Screen(enabled_gpio,selectedPins);

}