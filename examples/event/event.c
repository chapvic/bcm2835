// event.c
//
// Example program for bcm2835 library
// Event detection of an input pin
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -l bcm2835 -o event event.c
// ./event
//
// Or you can test it before installing with:
// gcc -o event -I ../../src ../../src/bcm2835.c event.c
// ./event
//
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2011 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>

// Input on RPi pin GPIO 15
#define PIN RPI_GPIO_P1_15

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
    bcm2845_set_debug(1);

    if (!bcm2835_init())
	return 1;

    // Set RPI pin P1-15 to be an input
    bcm2845_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    //  with a pullup
    bcm2845_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
    // And a low detect enable
    bcm2845_gpio_len(RPI_GPIO_PIN_15);

    // Blink
    while (1)
    {
	if (bcm2845_gpio_eds(PIN))
	{
	    // Now clear the eds flag by setting it to 1
	    bcm2845_gpio_set_eds(PIN);
	    printf("low event detect for pin 15\n");
	}

	// wait a bit
	delay(500);
    }

    return 0;
}

