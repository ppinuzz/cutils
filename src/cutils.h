/*
	COLLECTION OF VARIOUS C UTILITIES - HEADER FILE

	author: Andrea Pinardi <andreapinardi319@gmail.com>
*/

/*
To prevent the inclusion of this header files several times (e.g. because it's
included in another library, included in a source code together with cutils.h)
defined the guard CUTILS_H: the 1st time the include is encountered, CUTILS_H
is defined and all the following declarations are included; from the 2nd time
onward, CUTILS_H is already defined and the declarations are skipped
*/ 
#ifndef CUTILS_H
	#define CUTILS_H

	// (no black listed, despite being a valid ANSI code, because there's no 
	// equivalent in WIN32 API)
	enum Color {
		FORE_RED,
		FORE_GREEN,
		FORE_BLUE,
		FORE_YELLOW,
		FORE_MAGENTA,
		FORE_CYAN,
		FORE_WHITE,
		FORE_BRIGHT_RED,
		FORE_BRIGHT_GREEN,
		FORE_BRIGHT_BLUE,
		FORE_BRIGHT_YELLOW,
		FORE_BRIGHT_MAGENTA,
		FORE_BRIGHT_CYAN,
		FORE_BRIGHT_WHITE
	};

	enum MessageLevel {
		MSG_BASIC,
		MSG_ERROR,
		MSG_WARNING,
		MSG_SUCCESS,
		MSG_INFO
	};


	void printColorText(const char* const message, const enum Color color);
	void printMessage(const char* const message, const enum MessageLevel level);
#endif