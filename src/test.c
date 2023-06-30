// Yesy program for bcm2835 library
// Blinks a pin on an off every 0.5 secs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2011 Mike McCauley
// $Id: test.c,v 1.1 2012/06/24 00:30:22 mikem Exp mikem $

#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (geteuid() == 0)
    {
	if (!bcm2835_init())
	    return 1;
    }
    else
    {
	fprintf(stderr, "****You need to be root to properly run this test program\n");
    }
    return 0;
}
