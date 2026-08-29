/*
	COLLECTION OF VARIOUS C UTILITIES - HEADER FILE

	author: Andrea Pinardi <andreapinardi319@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>			// EXIT_SUCCESS
#include "../src/cutils.h"

int main(void){
	printColorText("Coloured text: RED\n", 		FORE_RED);
	printColorText("Coloured text: YELLOW\n", 	FORE_YELLOW);
	printColorText("Coloured text: BLUE\n", 		FORE_BLUE);
	printColorText("Coloured text: GREEN\n", 	FORE_GREEN);
	printColorText("Coloured text: CYAN\n", 		FORE_CYAN);
	printColorText("Coloured text: MAGENTA\n", 	FORE_MAGENTA);
	printColorText("Coloured text: WHITE\n", 	FORE_WHITE);
	printColorText("Coloured text: BRIGHT RED\n", 		FORE_BRIGHT_RED);
	printColorText("Coloured text: BRIGHT YELLOW\n", 	FORE_BRIGHT_YELLOW);
	printColorText("Coloured text: BRIGHT BLUE\n", 		FORE_BRIGHT_BLUE);
	printColorText("Coloured text: BRIGHT GREEN\n", 		FORE_BRIGHT_GREEN);
	printColorText("Coloured text: BRIGHT CYAN\n", 		FORE_BRIGHT_CYAN);
	printColorText("Coloured text: BRIGHT MAGENTA\n", 	FORE_BRIGHT_MAGENTA);
	printColorText("Coloured text: BRIGHT WHITE\n", 		FORE_BRIGHT_WHITE);
	
	printMessage("Basic message\n", 	MSG_BASIC);
	printMessage("Error message\n", 	MSG_ERROR);
	printMessage("Warning message\n", 	MSG_WARNING);
	printMessage("Success message\n", 	MSG_SUCCESS);
	printMessage("Info message\n", 		MSG_INFO);
	return EXIT_SUCCESS;
}