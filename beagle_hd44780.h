#ifndef BEAGLE_HD44780_H_GUARD
#define BEAGLE_HD44780_H_GUARD

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

#include "beagle_gpio.h"

#define DISPLAY_DATA_ON_SCREEN 0
#define MAX_DELAY 0.10

void goto_ScreenLine(int line, struct gpioID enabled_gpio[]);
void goto_ScreenLocation(int line, int position,struct gpioID enabled_gpio[]);
unsigned int return_address_in_bitform (unsigned int address, int part);
unsigned int write_character (char character, int part);
void charToScreen(char characterToWrite, struct gpioID enabled_gpio[]);
void initialize_Screen(struct gpioID enabled_gpio[],int selectedPins[]);
void terminate_Screen(struct gpioID enabled_gpio[],int selectedPins[]);
void clear_Screen(struct gpioID enabled_gpio[]);
void enableBlinkingCursor(struct gpioID enabled_gpio[]);
void disableBlinkingCursor(struct gpioID enabled_gpio[]);
void stringToScreen(const char *full_string, struct gpioID enabled_gpio[]);
#endif