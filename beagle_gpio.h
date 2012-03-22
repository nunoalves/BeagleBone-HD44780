#ifndef BEAGLE_GPIO_H_GUARD
#define BEAGLE_GPIO_H_GUARD

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

//The following #defines make it easier for the user to add differnt pins
#define P8_3  0
#define P8_4  1
#define P8_5  2
#define P8_11 3
#define P8_12 4
#define P8_14 5
#define P8_15 6
#define P8_16 7
#define P8_17 8
#define P8_20 9
#define P8_21 10

/** @brief Contains all elements which we need to pass into the beagleboard 
 * to specify which GPIO pin we want to turn ON/OFF **/ 
struct gpioID
{
	char *PINNAME;  //eg. P8_3
	char * GPIOID; 	//e.g: gpio1[6] 
	int GPIONUMBER; //e.g: 38
	char *GPIOMUX;  //e.g: gpmc_ad6; 
};

void pulsePin(struct gpioID enabled_gpio[],unsigned int data_to_write,int nbr_selectedPins, int print_to_screen, const char *pinDescription[], int pinID, int delay);
void write_GPIO_value(int GPIONUMBER, int value);
void cleanup_GPIO(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins);
void initialize_each_enabled_gpio(struct gpioID selected_GPIOs[],int selectedPins[], int nbr_selectedPins);
void display_each_enabled_gpio(struct gpioID selected_GPIOs[],int nbr_selectedPins,const char *pinDescription[]);
void turn_ON_OFF_pins(struct gpioID selected_GPIOs[],unsigned int data_to_write,int nbr_selectedPins, int print_to_screen, const char *pinDescription[]);
//void turn_ON_OFF_pins(struct gpioID selected_GPIOs[],unsigned int data_to_write,int nbr_selectedPins, int print_to_screen);
unsigned int bitWrite(unsigned int groupOfBits, int bitVal, int bitLoc);
int bitRead(unsigned int groupOfBits, int bitLoc);

#endif