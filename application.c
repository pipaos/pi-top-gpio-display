/*
 * gpio-display for pi-top
 *
 */
 
#include <math.h>
#include <stdio.h>
#include <wiringPi.h>

#include "main.h"
#include "application.h"

// configuration data for each Pin

struct pinConfig_t {
	char *name;
	int raspiPin;
	int wiringPiPin;
	int value;
} pinConfig[35];

void pin_c(int number, char *name, int raspiPin, int wiringPiPin)
{
	if ((number >= 0) && (number <= 34)) {
		pinConfig[number].name = name;
		pinConfig[number].raspiPin = raspiPin;
		pinConfig[number].wiringPiPin = wiringPiPin;
		pinConfig[number].value = 0;
	}
}

void application_init()
// put any code here to initialize the application
{
	// printf("application_init called\n");
	
	wiringPiSetup();
	
	pin_c( 1, "PWR 12-18V",		 0, -1);
	pin_c( 2, "5V / max 3A",	 0, -1);
	pin_c( 3, "3.3 V PRST",		 0, -1);
	pin_c( 4, "3.3 V",			 0, -1);
	pin_c( 5, "GND",			 0, -1);
	pin_c( 6, "SPDIF_OUT",		 0, -1);
	pin_c( 7, "SDA1 (IC2)",		 3, -1);    // wiringPi pin 8, but used for I2C
	pin_c( 8, "SDC1 (IC2)",		 5, -1);    // wiringPi pin 9, but used for I2C
	pin_c( 9, "CPLCK0",			 7,  7);
	pin_c(10, "TDX (UART)", 	 8, -1);     // wiringPi pin 15, but used for UART
	pin_c(11, "RDX (UART)",		10, -1);     // wiringPi pin 16, but used for UART
	pin_c(12, "BCM-17",			11,  0);
	pin_c(13, "PCM_C_BCM-18",	12,  1);
	pin_c(14, "PCM_D_BCM-27",	13,  2);
	pin_c(15, "BCM-22"		,	15,  3);
	pin_c(16, "BCM-23"		,	16,  4);
	pin_c(17, "BCM-24"		,	18,  5);
	pin_c(18, "MOSI_BCM-10"	,	19, -1);     // wiringPi pin 12, but used for SPI
	pin_c(19, "MIS_BCM-9"	,	21, -1);     // wiringPi pin 13, but used for SPI
	pin_c(20, "BCM-25"		,	22,  6);
	pin_c(21, "SCLK-BCM-25"	,	23, -1);     // wiringPi pin 14, but used for SPI
	pin_c(22, "CE0-BCM-0"	,	24, -1);     // wiringPi pin 10, but used for SPI
	pin_c(23, "CE1-BCM-1"	,	26, -1);     // wiringPi pin 11, but used for SPI
	pin_c(24, "ID_SD-BCM-0"	,	27, -1);
	pin_c(25, "ID_S-BCM-1"	,	28, -1);
	pin_c(26, "BCM-5"		,	29, 21);
	pin_c(27, "BCM-6"		,	31, 22);
	pin_c(28, "BCM-12"		,	32, 26);
	pin_c(29, "BCM-13"		,	33, 23);
	pin_c(30, "MISO_BCM-19"	,	35, 24);
	pin_c(31, "BCM-16"		,	36, 27);
	pin_c(32, "BCM-26"		,	37, 25);
	pin_c(33, "MOSI_BCM-20"	,	38, 28);
	pin_c(34, "CLK-BCM-16"	,	40, 29);
	
	
}

int application_on_timer_event()
// if TIMER_INTERVAL in application.h is larger than zero, this function
// is called every TIMER-INTERVAL milliseconds
// if the function returns 1, the window is redrawn by calling applicatin_draw
{
	//  printf("application_on_timer_event called\n");
	int redraw = 0;
	int pin, wiringPiPin, newValue;
	
	for (pin = 1; pin <= 34; pin++) {
		wiringPiPin = pinConfig[pin].wiringPiPin;
		if (wiringPiPin >= 0) {
			newValue = digitalRead(wiringPiPin);
			// printf("pin %d, wiringPi = %d, value = %d\n", pin, wiringPiPin, newValue);
			if(newValue != pinConfig[pin].value) {
				// printf("pin %d change, new value = %d\n", pin, newValue);
				redraw = 1;
				pinConfig[pin].value = newValue;
			}
		}
	}
	
	return redraw;
}
 
int application_clicked(int button, int x, int y)
// is called if a mouse button is clicked in the window
// button = 1: means left mouse button; button = 3 means right mouse button
// x and y are the coordinates
// if the function returns 1, the window is redrawn by calling applicatin_draw
{
	printf("application_clicked called, button %d, x = %d, y= %d\n", button, x, y);	
	return 1;
}

void application_quit()
// is called if the main window is called bevore the application exits
// put any code here which needs to be called on exit
{
	// printf("application quit called\n");
}

void application_draw(cairo_t *cr, int width, int height)
// draw onto the main window using cairo
// width is the actual width of the main window
// height is the actual height of the main window

#define FIELD_SIZE		20
#define CIRCLE_RADIUS	6

{	
	int x, y, pin, xNum, xLabel, xWiringPi;
	char str[16];
	
	// printf("application_draw called\n");
	
	// set the backgrond color
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_set_source_rgb(cr, 0.93, 0.93, 0.93);
	cairo_fill(cr);
	
	cairo_set_font_size(cr, 11);
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	cairo_set_line_width (cr, 1);
	cairo_rectangle (cr, width / 2 - (9 * FIELD_SIZE),
		12, 18 * FIELD_SIZE, 19 * FIELD_SIZE);
		
	y = 26;
	x = (width / 2) - ((3 * FIELD_SIZE) / 2);
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pi-top hub");
	
	x = (width / 2) - ((18 * FIELD_SIZE) / 2) + 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "wirPi");

	x = (width / 2) - ((11 * FIELD_SIZE) / 2) - 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pin name");
	
	x = (width / 2) + ((7 * FIELD_SIZE) / 2) - 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pin name");
	
	x = (width / 2) + ((14 * FIELD_SIZE) / 2) + 4;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "wirPi");
		
	cairo_move_to(cr, width / 2 - (9 * FIELD_SIZE), 12 + FIELD_SIZE);
	cairo_line_to(cr, width / 2 + (9 * FIELD_SIZE), 12 + FIELD_SIZE);
	
	cairo_move_to(cr, width / 2 - (7 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 - (7 * FIELD_SIZE), 12 + (19 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 - (2 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 - (2 * FIELD_SIZE), 12 + (19 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 + (2 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 + (2 * FIELD_SIZE), 12 + (19 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 + (7 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 + (7 * FIELD_SIZE), 12 + (19 * FIELD_SIZE));
		
	for (pin = 1; pin <= 34; pin++) {
		
		if (pin % 2) {
			x = (width / 2) + (FIELD_SIZE / 2);
			xNum = x + FIELD_SIZE - 8;
			xLabel = x + (2 * FIELD_SIZE) - 2;
			xWiringPi = (width / 2) + ((14 * FIELD_SIZE) / 2) + 12;
		}
		else {
			x = (width / 2) - (FIELD_SIZE / 2);
			xNum = x - FIELD_SIZE - 6;
			xLabel = x - (6 * FIELD_SIZE) - 6;
			xWiringPi = (width / 2) - ((18 * FIELD_SIZE) / 2) + 12;
		}
		
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_move_to(cr, xNum, y + 4);
		sprintf(str, "%2d", pin);
		cairo_show_text(cr, str);
		
		cairo_stroke (cr);
		
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);    // black
		y = FIELD_SIZE + 12 + (((pin + 1) / 2) * FIELD_SIZE);
		cairo_move_to(cr, x + CIRCLE_RADIUS, y);
		cairo_arc(cr, x, y, CIRCLE_RADIUS, 0, 2 * M_PI);
		if (pinConfig[pin].value) {
			cairo_stroke_preserve(cr);
			cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);    // fill red
			cairo_fill(cr);
		}
		else if (pinConfig[pin].wiringPiPin >= 0) {
			cairo_stroke_preserve(cr);
			cairo_set_source_rgb(cr, 0.5, 0.0, 0.0);    // fill dark red
			cairo_fill(cr);
		}
		cairo_stroke (cr);
		
		
		if (pinConfig[pin].wiringPiPin >= 0)
			cairo_set_source_rgb(cr, 0.0, 0.5, 0.0);    // dark green
		else
			cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);    // black
		
		cairo_move_to(cr, xLabel, y + 4);
		cairo_show_text(cr, pinConfig[pin].name);
		if (pinConfig[pin].wiringPiPin >= 0) {
			sprintf(str, "%2d", pinConfig[pin].wiringPiPin);
			cairo_move_to(cr, xWiringPi, y + 4);
		    cairo_show_text(cr, str);
		}
	}
	cairo_stroke (cr);

}
