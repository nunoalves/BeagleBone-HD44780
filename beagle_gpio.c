#include "beagle_gpio.h"

/** 
 * @brief Writes a value to a particular GPIO, logic-HIGH or logic-LOW.
 * @param GPIONUMBER The GPIO number (e.g. 38 for gpio1[6])
 * @param value The logic value we want to write to the GPIO (0 or 1)
 **/ 
void write_GPIO_value(int GPIONUMBER, int value)
{
	char export_filename[50]; 
	FILE *f = NULL; 
    
	sprintf(export_filename, "/sys/class/gpio/gpio%d/value",GPIONUMBER); 
	f = fopen(export_filename,"w");
	assert(f!=NULL);    
	fprintf(f , "%d",value); 
	pclose(f); 
}

/** 
 * @brief Tells the OS that we are done with using GPIOs
 * @param selected_GPIOs[] initialized array of gpioID.
 * @param selectedPins[] Array with the user specified pins
 * @param nbr_selectedPins Number of pins that were specified by the user
 **/ 
void cleanup_GPIO(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins)
{
	char export_filename[50]; 
	FILE *f = NULL; 
	int i;
	
	for (i=0; i<nbr_selectedPins;i++)
	{
		//unexport the pin
		f = fopen("/sys/class/gpio/unexport","w");
		assert(f!=NULL);   
        fprintf(f, "%d",selected_GPIOs[i].GPIONUMBER); 
        pclose(f); 
        
    }
}

/** 
 * @brief Initializes all the user specified pins  
 * @param selected_GPIOs[] Un-initialized array of gpioID. At the end of this 
 * function, the selected_GPIOs[] array will be initialized.
 * @param selectedPins[] Array with the user specified pins
 * @param nbr_selectedPins Number of pins that were specified by the user
 **/ 
void initialize_each_enabled_gpio(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins)
{
	int i;
	//this variable will contain the location of the file that we need to 
	//set to mode 7
	char export_filename[50]; 
    
    FILE *f = NULL; 
	//You are not allowed to use more than 32 active pins. This is not a 
	//beagleboard limitation, but a limitation of this code.
	assert (nbr_selectedPins<=32);
	
	//cycles every userdefined pin, and inializes its contents in the 
	//selected_GPIOs[] array.
	for (i=0; i<nbr_selectedPins;i++)
	{
		switch (selectedPins[i])
		{
			case P8_3:
				selected_GPIOs[i].PINNAME="P8_3";
				selected_GPIOs[i].GPIOID="gpio1[6]";
				selected_GPIOs[i].GPIONUMBER=38;
				selected_GPIOs[i].GPIOMUX="gpmc_ad6";
				break;
                
			case P8_4:
				selected_GPIOs[i].PINNAME="P8_4";
				selected_GPIOs[i].GPIOID="gpio1[7]";
				selected_GPIOs[i].GPIONUMBER=39;
				selected_GPIOs[i].GPIOMUX="gpmc_ad7";
				break;
                
			case P8_5:
				selected_GPIOs[i].PINNAME="P8_5";
				selected_GPIOs[i].GPIOID="gpio1[2]";
				selected_GPIOs[i].GPIONUMBER=34;
				selected_GPIOs[i].GPIOMUX="gpmc_ad2";
				break;
                
			case P8_11:
				selected_GPIOs[i].PINNAME="P8_11";
				selected_GPIOs[i].GPIOID="gpio1[13]";
				selected_GPIOs[i].GPIONUMBER=45;
				selected_GPIOs[i].GPIOMUX="gpmc_ad13";
				break;
                
			case P8_12:
				selected_GPIOs[i].PINNAME="P8_12";
				selected_GPIOs[i].GPIOID="gpio1[12]";
				selected_GPIOs[i].GPIONUMBER=44;
				selected_GPIOs[i].GPIOMUX="gpmc_ad12";
				break;

			case P8_14:
				selected_GPIOs[i].PINNAME="P8_14";
				selected_GPIOs[i].GPIOID="gpio0[26]";
				selected_GPIOs[i].GPIONUMBER=26;
				selected_GPIOs[i].GPIOMUX="gpmc_ad10";
				break;
           
   	  		case P8_15:
				selected_GPIOs[i].PINNAME="P8_15";
				selected_GPIOs[i].GPIOID="gpio1[15]";
				selected_GPIOs[i].GPIONUMBER=47;
				selected_GPIOs[i].GPIOMUX="gpmc_ad15";
				break;
 
 			case P8_16:
				selected_GPIOs[i].PINNAME="P8_16";
				selected_GPIOs[i].GPIOID="gpio1[14]";
				selected_GPIOs[i].GPIONUMBER=46;
				selected_GPIOs[i].GPIOMUX="gpmc_ad14";
				break;

 			case P8_17:
				selected_GPIOs[i].PINNAME="P8_17";
				selected_GPIOs[i].GPIOID="gpio0[27]";
				selected_GPIOs[i].GPIONUMBER=27;
				selected_GPIOs[i].GPIOMUX="gpmc_ad11";
				break;

 			case P8_20:
				selected_GPIOs[i].PINNAME="P8_20";
				selected_GPIOs[i].GPIOID="gpio1[31]";
				selected_GPIOs[i].GPIONUMBER=63;
				selected_GPIOs[i].GPIOMUX="gpmc_csn2";
				break;

 			case P8_21:
				selected_GPIOs[i].PINNAME="P8_21";
				selected_GPIOs[i].GPIOID="gpio1[30]";
				selected_GPIOs[i].GPIONUMBER=62;
				selected_GPIOs[i].GPIOMUX="gpmc_csn1";
				break;
           
			default:
				//This statement should never be reached... since
				//the program won't even compile if the user 
				//specified a bad pin specification.
				break;
		}
	}
    
    //set the each mux pin to mode 7
    for (i=0; i<nbr_selectedPins;i++)
	{
		//set mux to mode 7 
	 	sprintf(export_filename, "/sys/kernel/debug/omap_mux/%s", selected_GPIOs[i].GPIOMUX); 
		f = fopen(export_filename,"w");
        
		if (f == NULL)
		{
         	printf( "\nERROR: There was a problem opening /sys/kernel/debug/omap_mux/%s\n", selected_GPIOs[i].GPIOMUX); 
			printf("\n%s\t%s\t%s\t%d\n\n", selected_GPIOs[i].PINNAME, selected_GPIOs[i].GPIOID, selected_GPIOs[i].GPIOMUX, selected_GPIOs[i].GPIONUMBER);
            
			assert(f!=NULL);
        } 
        fprintf(f, "7"); 
        pclose(f); 
        
		//export the pin
		f = fopen("/sys/class/gpio/export","w");
        
		if (f == NULL)
		{
         	printf( "\nERROR: There was a problem opening /sys/kernel/debug/omap_mux/%s\n", selected_GPIOs[i].GPIOMUX); 
			printf("\n%s\t%s\t%s\t%d\n\n", selected_GPIOs[i].PINNAME,selected_GPIOs[i].GPIOID,selected_GPIOs[i].GPIOMUX,selected_GPIOs[i].GPIONUMBER);
            
			assert(f!=NULL);
        } 
        fprintf(f, "%d",selected_GPIOs[i].GPIONUMBER); 
        pclose(f); 
        
        //set the appropriate io direction (out)
	 	sprintf(export_filename, "/sys/class/gpio/gpio%d/direction", selected_GPIOs[i].GPIONUMBER); 
		f = fopen(export_filename,"w");
        
		if (f == NULL)
		{
         	printf( "\nERROR: There was a problem opening /sys/class/gpio/gpio%d/direction\n", selected_GPIOs[i].GPIONUMBER); 
			printf("\n%s\t%s\t%s\t%d\n\n",selected_GPIOs[i].PINNAME,selected_GPIOs[i].GPIOID,selected_GPIOs[i].GPIOMUX,selected_GPIOs[i].GPIONUMBER);
            
			assert(f!=NULL);
        } 
        fprintf(f , "out" ); 
        pclose(f); 
        
        write_GPIO_value(selected_GPIOs[i].GPIONUMBER,0);
	}
}


/** 
 * @brief Displays all information for each of the user specified pins. 
 * This function has no purpose besides live debugging.
 * @param selected_GPIOs[] An valid (initialized) array of gpioID
 * @param nbr_selectedPins Number of pins that were specified by the user
 * @param pinDescription[] A constant array containing the description of each pin
 **/ 
void display_each_enabled_gpio(struct gpioID selected_GPIOs[],int nbr_selectedPins,const char *pinDescription[])
{
	int i;
	printf("\n");
	printf("PINNAME\tGPIOID\t\tGPIOMUX\t\tGPIONBR\tDESCRIPTION\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
	for (i=0; i< nbr_selectedPins; i++)
	{
		printf("%s\t%s\t%s\t%d\t%s\n",selected_GPIOs[i].PINNAME,selected_GPIOs[i].GPIOID,selected_GPIOs[i].GPIOMUX,selected_GPIOs[i].GPIONUMBER,pinDescription[i]);
	}
	printf("\n");
}

/** 
 * @brief Cycles through the entire array of selected_GPIOs[] and turns ON/OFF
 * each associated GPIO.
 * @param selected_GPIOs[] An valid (initialized) array of gpioID
 * @param data_to_write An unsigned integer (32 bits), where each bit contains the 
 * information regarding the status of each pin: 1=turn pin ON, 0=turn pin OFF
 * @param nbr_selectedPins Number of pins that were specified by the user
 * @param print_to_screen This specifies if some extra information is to be displayed in the 
 * user screen. It has no other purpose than debugging your code. If print_to_screen == 1, data will
 * be displayed on the terminal window; otherwise it will not.
 * @param pinDescription[] A constant array containing the description of each pin
 **/ 
void turn_ON_OFF_pins(struct gpioID selected_GPIOs[],unsigned int data_to_write,int nbr_selectedPins, int print_to_screen, const char *pinDescription[])
{
	int i;
	
	for (i=0;i<nbr_selectedPins;i++)
	{
		//code that turns ON/OFF a pin
		write_GPIO_value(selected_GPIOs[i].GPIONUMBER,bitRead(data_to_write,i));
        
		//this is just for debugging purposes
		if (print_to_screen)
		{ 
			if (bitRead(data_to_write,i) == 1) printf("turning ON");	
			else printf("turning OFF");	
			printf(	"\t%s (%s %d %s) - %s\n",selected_GPIOs[i].PINNAME,selected_GPIOs[i].GPIOID,selected_GPIOs[i].GPIONUMBER,selected_GPIOs[i].GPIOMUX,pinDescription[i]);				
		}
	}
	if (print_to_screen) printf("\n");
}

/** 
 * @brief Writes a bit into a particular location in an unsigned int variable (32 bits)
 * @param groupOfBits Some data resides in these 32 bits 
 * @param bitVal The bitVal is wither a 1 or a 0
 * @param bitLoc Where in the groupOfBits, the value of bitVal will be written. 
 * Keep in mind that the bitLoc values ranges 0 to 31
 * @return Returns the updated groupOfBits
 **/ 
unsigned int bitWrite(unsigned int groupOfBits, int bitVal, int bitLoc)
{
    if (bitVal==1) groupOfBits |= 1 << bitLoc;
    else groupOfBits &= ~(1 << bitLoc);     
    return(groupOfBits);
}

/** 
 * @brief Returns the bit value of a particular location in an unsigned int variable (32 bits)
 * @param groupOfBits Some data resides in these 32 bits 
 * @param bitLoc Where in the groupOfBits, the value of bitVal will be written 
 * @return Retuns an integer with the bit value (1 or 0) that resides in bitLoc
 **/ 
int bitRead(unsigned int groupOfBits, int bitLoc)
{
    unsigned int bit = groupOfBits & (1 << bitLoc);
    if (bit!=0) bit=1;
    
    return(bit);
}

/** 
 * @brief Pulses a particular bit (goes HIGH then LOW) with a specify delay
 * @param selected_GPIOs[] An valid (initialized) array of gpioID
 * @param data_to_write An unsigned integer (32 bits), where each bit contains the 
 * information regarding the status of each pin: 1=turn pin ON, 0=turn pin OFF
 * @param nbr_selectedPins Number of pins that were specified by the user
 * @param print_to_screen This specifies if some extra information is to be displayed in the 
 * user screen. It has no other purpose than debugging your code. If print_to_screen == 1, data will
 * be displayed on the terminal window; otherwise it will not.
 * @param pinDescription[] A constant array containing the description of each pin
 * @param pinID ID of pin we want to pulse
 * @param delay Delay in seconds that will define the interval between signal states
 **/ 
void pulsePin(struct gpioID enabled_gpio[],unsigned int data_to_write,int nbr_selectedPins, int print_to_screen, const char *pinDescription[], int pinID, int delay)
{
	if (print_to_screen) printf("========== START: PULSING PIN %d ==========\n",pinID);
	data_to_write=bitWrite(data_to_write,1,pinID);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,print_to_screen,pinDescription);
	sleep(delay);
	data_to_write=bitWrite(data_to_write,0,pinID);
	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins,print_to_screen,pinDescription);
	sleep(delay); 
	if (print_to_screen) printf("========== END: PULSING PIN %d ==========\n",pinID);
}