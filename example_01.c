#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"


#define DISPLAY_DATA_ON_SCREEN 1

/** 
 * @brief This program (example_01.c) shows how to write data into a
 * HD44780 LCD display using the manual process of setting up every 
 * single pin with a binary value. For a complete description of these
 * (and more) HD44780 commands, read the article by Julyan llett,
 * "How to use intelligent L.C.D.s - Part One".
 * 
 * @section Setup
 * Set-up the HD44780 screen as follows:
 * Pin 1 - VSS - Connect to ground 
 * Pin 2 - VCC - Connect to +5V (or lower voltage depending on your LCD)
 * Pin 3 - VO - Attach a potentiometer here to adjust contrast 
 * Pin 4 - Register Select (RS) - Connect to P8_4
 * Pin 5 - Read/Write (R/W) - Connect to ground
 * Pin 6 - Clock (Enable) - Connect to P8_3 
 * Pin 7 - Data Bit 0 - Do not connect anything to it
 * Pin 8 - Data Bit 1 - Do not connect anything to it
 * Pin 9 - Data Bit 2 - Do not connect anything to it
 * Pin 10 - Data Bit 3 - Do not connect anything to it
 * Pin 11 - Data Bit 4 - Connect to P8_5  
 * Pin 12 - Data Bit 5 - Connect to P8_11 
 * Pin 13 - Data Bit 6 - Connect to P8_12 
 * Pin 14 - Data Bit 7 - Connect to P8_14 
 * Pin 15 - Backlight Anode (+) - Connect to +5V (or lower)
 * Pin 16 - Backlight Cathode (-) - Connect to ground 
 *
 * @section Compilation
 * Compile, and run, this code on the beagleBone terminal with the command: 
 *
 * gcc -c beagle_gpio.c ; gcc beagle_gpio.o example_01.c ; ./a.out ; rm -f a.out ;
 * 
 * @return Returns a 1 upon succesful program termination
 **/ 
int main()
{

	//Specifies which pins we are going to use
	int selectedPins[]={P8_14,P8_12,P8_11,P8_5,P8_4,P8_3};
	//A little description for each of the selectedPins[]. 
	//This makes debugging a LOT easier...
	const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};

	int nbr_selectedPins=sizeof(selectedPins)/sizeof(*selectedPins);
    
	unsigned int data_to_write=0;
	
	//these two lines initalize all the selected pins
	struct gpioID enabled_gpio[nbr_selectedPins]; 
	initialize_each_enabled_gpio(enabled_gpio,selectedPins,nbr_selectedPins);
	
	//display some information on the beglebone screen 
	if (DISPLAY_DATA_ON_SCREEN) display_each_enabled_gpio(enabled_gpio,nbr_selectedPins,pinDescription);


	//========================================================================
	//START: Manually feeding commands into the HD44780 LCD
	//========================================================================
	//For example: the following command will type the letter 'hi' in the
	//LCD

	//RS ; DB7 ; DB6 ; DB5 ; DB4 ; Stop sending commands?   
	//0  ; 0   ; 0   ; 1   ; 1   ; No - (this command initializes the screen)
	//0  ; 0   ; 0   ; 1   ; 0   ; No - (this command send LCD to 4 bit mode)
	//0  ; 0   ; 0   ; 0   ; 0   ; No - (enable display with cursor part 1) 
	//0  ; 1   ; 1   ; 1   ; 1   ; No - (enable display with cursor part 2) 
	//1  ; 0   ; 1   ; 1   ; 0   ; No - (first part of character 'h')
	//1  ; 1   ; 0   ; 0   ; 0   ; No - (second part of character 'h')
	//1  ; 0   ; 1   ; 1   ; 0   ; No - (first part of character 'i')
	//1  ; 1   ; 0   ; 0   ; 1   ; No - (second part of character 'i')
	//0  ; 0   ; 0   ; 1   ; 1   ; Yes - (go back into 8 bit mode) 

 	int pinSelect, terminate_operation, i, pinData;

	terminate_operation=0;
   	while (terminate_operation==0)
	{
    	data_to_write=0; 
   	    printf("Write value for pin %s:\n",pinDescription[4]);
		scanf("%d",&pinData);
		data_to_write=bitWrite(data_to_write,pinData,i);
		turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,1,pinDescription);
		for (i=0; i<4; i++)
		{
   		    printf("Write value for pin %s:\n",pinDescription[i]);
			scanf("%d",&pinData);
			data_to_write=bitWrite(data_to_write,pinData,i);
			turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,1,pinDescription);
		}
		
		pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, 1);
   	    printf("Stop sending commands? (1=yes):\n");
		scanf("%d",&terminate_operation);
	}		
	//========================================================================
	//END: Manually feeding commands into the HD44780 LCD
	//========================================================================

 	//we should now tell the OS that we are done with the GPIOs
	cleanup_GPIO(enabled_gpio,selectedPins,nbr_selectedPins);
}