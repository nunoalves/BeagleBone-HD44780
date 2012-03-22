#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"


#define DISPLAY_DATA_ON_SCREEN 1
#define MAX_DELAY 0.25

/** 
 * @brief Another sample test program that turns ON/OFF LEDS.
 * Compile, and run, this code on the beagleBone terminal with the command: 
 *
 * rm -f a.out ; gcc -c beagle_gpio.c ; gcc beagle_gpio.o test4.c ; ./a.out
* 
 * @return Returns a 1 upon succesful program termination
 **/ 
int main()
{

	//5=DB7, 4=DB6, 3=DB5, 2=DB4, 1=RS, 0=E 	
	int selectedPins[]={P8_14,P8_12,P8_11,P8_5,P8_4,P8_3};

	const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};

	int nbr_selectedPins=sizeof(selectedPins)/sizeof(*selectedPins);
    
	unsigned int data_to_write=0;
	
	struct gpioID enabled_gpio[nbr_selectedPins];
    
	initialize_each_enabled_gpio(enabled_gpio,selectedPins,nbr_selectedPins);
	if (DISPLAY_DATA_ON_SCREEN) display_each_enabled_gpio(enabled_gpio,nbr_selectedPins,pinDescription);
	int pinSelect;
	
	int terminate_operation;
	int i;
	int pinData;

    data_to_write=12; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

    data_to_write=4; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

    data_to_write=0; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

    data_to_write=15; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//type all the numbers 0 to 9

	//0 in ASCII is 48
	//
  	for (i=0; i<10; i++)
  	{
	data_to_write=28; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
  	
  	data_to_write=16; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
	}

	//put the display back in 8 bit mode to allow to re-run program
	data_to_write=12; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
	
 	//we should now tell the OS that we are done with the GPIOs
	cleanup_GPIO(enabled_gpio,selectedPins,nbr_selectedPins);
}