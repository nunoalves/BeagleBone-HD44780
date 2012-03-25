#include "beagle_hd44780.h"

/** 
 * @brief Converts a character in two bitstreams the LCD can understand.
 * @param character The character we want to write.
 * @param part This can be either 0 or 1. Part 0 correspond to DB7..DB4, 
 * while part 1 corresponds to DB3..DB0 on 8 bit mode. Since we are doing
 * 4 bit mode, we need to split the bitstream in two parts.
 **/
unsigned int write_character (char character, int part)
{
	assert(part==0 || part==1);

	char acB[2];
	sprintf(acB, "%x", character);

	unsigned int return_value = 0;
	
	switch (acB[part])
	{
		case '0': return_value = 16; break; 	
		case '1': return_value = 24; break;
		case '2': return_value = 20; break;
		case '3': return_value = 28; break;
		case '4': return_value = 18; break;
		case '5': return_value = 26; break;
		case '6': return_value = 22; break;
		case '7': return_value = 30; break;
		case '8': return_value = 17; break;
		case '9': return_value = 25; break;
		case 'a': return_value = 21; break;
		case 'b': return_value = 29; break;
		case 'c': return_value = 19; break;
		case 'd': return_value = 27; break;
		case 'e': return_value = 23; break;
		case 'f': return_value = 31; break;
	}
	
	return(return_value);
}

/** 
 * @brief Puts a single character onto the screen.
 * @param characterToWrite The character we want to write.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void charToScreen(char characterToWrite, struct gpioID enabled_gpio[])
{
	unsigned int data_to_write=0;
	const char *pinDescription[] = {"","","","","",""};

	data_to_write=write_character (characterToWrite,0);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,6,0.10,pinDescription);
	pulsePin(enabled_gpio,data_to_write,6,0, pinDescription, 5, 0.10);
  	sleep(0.10);

	data_to_write=write_character (characterToWrite,1);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,6,0.10,pinDescription);
	pulsePin(enabled_gpio,data_to_write,6,0, pinDescription, 5, 0.10);
  	sleep(0.10);

}
/** 
 * @brief Initializes the screen so we can use it.
 * @param selected_GPIOs[] An initialized array of gpioID. 
 * @param selectedPins[] The user defined pins.
 **/
void initialize_Screen(struct gpioID enabled_gpio[],int selectedPins[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	initialize_each_enabled_gpio(enabled_gpio,selectedPins,nbr_selectedPins);
	if (DISPLAY_DATA_ON_SCREEN) display_each_enabled_gpio(enabled_gpio,nbr_selectedPins,pinDescription);

	//E RS DB4 DB5 DB6 DB7
	//0 0  1   1   0   0 	(base 2) which equals 12 (base 10)
    data_to_write=12; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//E RS DB4 DB5 DB6 DB7
	//0 0  0   1   0   0 	(base 2) which equals 4 (base 10) : 4 bit mode
    data_to_write=4; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//enable display part 1 - Display ON/OFF & Cursor
	//E RS DB4 DB5 DB6 DB7 = 000000 (2) == 0 (10)
    data_to_write=0; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//enable display part 2 - Display ON/OFF & Cursor
	//E RS DB4 DB5 DB6 DB7 = 000011 (2) == 3 (10)
    data_to_write=3; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
  	
  	//two line mode 5x7 part 1 
	//E RS DB4 DB5 DB6 DB7 = 000100 (2) == 4  (10)
    data_to_write=4; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

  	//two line mode 5x7 part 2 (the 0 next to the 1 specifies the 5x7)
	//E RS DB4 DB5 DB6 DB7 = 000001 (2) == 1 (10)
    data_to_write=1; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

}

/** 
 * @brief Enables the blinking cursor with an underline.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void enableBlinkingCursor(struct gpioID enabled_gpio[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	//enable cursor part 1
	//E RS DB4 DB5 DB6 DB7 = 000000 (2) == 0 (10)
    data_to_write=0; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//enable cursor part 2
	//E RS DB4 DB5 DB6 DB7 = 001111 (2) == 15 (10)
    data_to_write=15; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
}

/** 
 * @brief Disables the blinking cursor with an underline.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void disableBlinkingCursor(struct gpioID enabled_gpio[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	//enable cursor part 1
	//E RS DB4 DB5 DB6 DB7 = 000000 (2) == 0 (10)
    data_to_write=0; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//enable display part 2 - Display ON/OFF & Cursor
	//E RS DB4 DB5 DB6 DB7 = 000011 (2) == 3 (10)
    data_to_write=3; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
}

/** 
 * @brief Clears the LCD from anything thats in there.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void clear_Screen(struct gpioID enabled_gpio[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	//E RS DB4 DB5 DB6 DB7 = 000000 (2) == 0 (10)
	data_to_write=0; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	//E RS DB4 DB5 DB6 DB7 = 001000 (2) == 8 (10)
	data_to_write=8; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
}


/** 
 * @brief After you are done using the LCD you should terminate it properly. 
 * Failure to do so will guarantee that next time you use LCD it will be on 8 bit
 * mode... and you will must turn ON/OFF the screen.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void terminate_Screen(struct gpioID enabled_gpio[],int selectedPins[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	//put the display back in 8 bit mode to allow to re-run program
	//E RS DB4 DB5 DB6 DB7 = 001100 (2) == 12 (10)
	data_to_write=12; 
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
	
 	//we should now tell the OS that we are done with the GPIOs
	cleanup_GPIO(enabled_gpio,selectedPins,nbr_selectedPins);
}

/** 
 * @brief Prints a string to the screen.
 * @param full_string  String that needs to be printed on the LCD
 * @param selected_GPIOs[] Initialized array of gpioID. 
 **/
void stringToScreen(const char *full_string, struct gpioID enabled_gpio[])
{
	int i;
	int length = strlen(full_string);

	for (i=0; i<length; i++)
	{
		charToScreen(full_string[i],enabled_gpio);
		//printf("%c\n",full_string[i]);
	}
}

/** 
 * @brief Sets the cursor to either the first or second line.
 * @param line If line==0, cursor will be placed on top line. If line==1, the
 * the cursor will be placed on the bottom line.
 * @param selected_GPIOs[] initialized array of gpioID. 
 **/
void goto_ScreenLine(int line, struct gpioID enabled_gpio[])
{
	assert(line==0 || line==1);
	goto_ScreenLocation(line,0,enabled_gpio);
}

/** 
 * @brief This function is still not working correctly. Technically the
 * function should set the cursor to a well defined position in the LCD, but
 * it is not doing so for the second line. I think my LCD is broken. Until, I 
 * fix this function (or at least test it with different LCDs) do not use it.
 * @param line Line number; where 0 is the top line and 1 is the bottom line.
 * @param position Position; where the initial position is 0.
 * @param selected_GPIOs[] Initialized array of gpioID. 
 **/
void goto_ScreenLocation(int line, int position,struct gpioID enabled_gpio[])
{
	int nbr_selectedPins=6;
	const char *pinDescription[] = {"","","","","",""};
	unsigned int data_to_write;

	//printf("position: %d\n",position);
	//printf("line: %d\n\n",line);
	
	if (line==1) position=position+40;
	data_to_write=return_address_in_bitform(position,0);
	//printf("data_to_write: %d\n",data_to_write);
	data_to_write=bitWrite(data_to_write,1,0);
	//printf("<%d>\n",data_to_write);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);

	data_to_write=return_address_in_bitform(position,1); 
	//printf("data_to_write: %d\n",data_to_write);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,MAX_DELAY,pinDescription);
	pulsePin(enabled_gpio,data_to_write,nbr_selectedPins,DISPLAY_DATA_ON_SCREEN, pinDescription, 5, MAX_DELAY);
  	sleep(MAX_DELAY);
}

/** 
 * @brief Returns the address in a split format such that we can send it to
   the screen position functions.
 * @param address This is the position we want to set the cursor to.
 * @param part This can be either 0 or 1. Part 0 correspond to DB7..DB4, 
 * @param selected_GPIOs[] Initialized array of gpioID. 
 **/

unsigned int return_address_in_bitform (unsigned int address, int part)
{
	assert(part==0 || part==1);

	unsigned int return_value=0;
	
	if (part==1) 
	{
		return_value=bitWrite(return_value,bitRead(address,3),0);
		return_value=bitWrite(return_value,bitRead(address,2),1);
		return_value=bitWrite(return_value,bitRead(address,1),2);
		return_value=bitWrite(return_value,bitRead(address,0),3);
	}

	if (part==0) 
	{
		return_value=bitWrite(return_value,bitRead(address,4),3);
		return_value=bitWrite(return_value,bitRead(address,5),2);
		return_value=bitWrite(return_value,bitRead(address,6),1);
		return_value=bitWrite(return_value,bitRead(address,7),0);
	}

	return(return_value);	
}
