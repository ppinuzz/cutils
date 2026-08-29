/**
 * @file cutils.c
 * @brief Implementation of the cutils library.
 *
 * Contains the platform-specific implementation of the terminal
 * colour and message-printing utilities declared in cutils.h.
 *
 * @author Andrea Pinardi <andreapinardi319@gmail.com>
 */


#define VERSION "1.0.0"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#if defined(_WIN32) || defined(__CYGWIN__)
	#define OS_WINDOWS
#elif defined(__linux__) || defined(__APPLE__)
	#define OS_UNIX
#else
	#error "Unknown OS"
#endif

#ifdef OS_WINDOWS
	#include <windows.h>	// horrendous WIN32 API
#endif

#include "cutils.h"

/*
	PRINT COLOURED MESSAGES TO TERMINAL - WINDOWS AND UNIX-LIKE
*/

// these are "private" (static) functions => not available outside of this file,
// mustn't be put together with all the other prototypes in cutils.h
#ifdef OS_WINDOWS
	static bool getColorCodeWindows(const enum Color color, WORD* pWinColor);
#elif defined(OS_UNIX)
	static bool getColorCodeUnix(const enum Color color, char* const ANSIcolor);
#endif

#ifdef OS_WINDOWS
	/*
	This function shouldn't be used outside of this file => make it "private"
	using static
	
	WIN32 API colour constants listed in 
		https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
	are defined (according to the web page) in WinCon.h
	HOWEVER:
		- filename is wincon.h, not WinCon.h
		- wincon.h doesn't actually contain them, but includes consoleapi2.h,
		which defines them as
			#define FOREGROUND_BLUE      0x0001
			#define FOREGROUND_GREEN     0x0002
			#define FOREGROUND_RED       0x0004
			#define FOREGROUND_INTENSITY 0x0008
		They are bit masks written in base 16 and can be combined using the 
		bitwise OR operator '|' to create all other colours 
	Their type is WORD: see the signature of the function using them in
	https://learn.microsoft.com/en-us/windows/console/setconsoletextattribute
	*/
	
	/**
	 * @brief Convert a colour enumeration to its Windows console representation.
	 *
	 * @param[in]  color     Requested colour.
	 * @param[out] pWinColor Corresponding Windows colour attributes.
	 *
	 * @return true if @p color is valid, false otherwise.
	 */
	static bool getColorCodeWindows(const enum Color color, WORD* pWinColor){
		// assume no error
		bool status = true;
		// 3 RGB basic colours are provided + FOREGROUND_INTENSITY
		// all others colours are a combination of the 3 RGB
		// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
		switch (color){
			case FORE_RED:
				*pWinColor = FOREGROUND_RED;
				break;
			case FORE_BLUE:
				*pWinColor = FOREGROUND_BLUE;
				break;
			case FORE_GREEN:
				*pWinColor = FOREGROUND_GREEN;
				break;
			case FORE_YELLOW:
				*pWinColor = FOREGROUND_RED | FOREGROUND_GREEN;
				break;
			case FORE_CYAN:
				*pWinColor = FOREGROUND_GREEN | FOREGROUND_BLUE;
				break;
			case FORE_MAGENTA:
				*pWinColor = FOREGROUND_RED | FOREGROUND_BLUE;
				break;
			case FORE_WHITE:
				*pWinColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				break;
			case FORE_BRIGHT_RED:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_RED;
				break;
			case FORE_BRIGHT_BLUE:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
				break;
			case FORE_BRIGHT_GREEN:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
				break;
			case FORE_BRIGHT_YELLOW:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
				break;
			case FORE_BRIGHT_CYAN:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
				break;
			case FORE_BRIGHT_MAGENTA:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
				break;
			case FORE_BRIGHT_WHITE:
				*pWinColor = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				break;
			default:
				// unrecognised colour code, assume white (black terminal)
				*pWinColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				status = false;
				break;
		}
		return status;
	}
#elif defined(OS_UNIX)
	#define ANSI_RESET "\x1b[0m"
	/*
	From https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
	Generic format of the code is
		ESC[codeFG;codeBGm
	where
		ESC 	has escape sequence \x1b in C
		codeFG	code for foreground colour
		codeFG	code for background colour
	If you only need to change the foreground colour, use
		ESC[codeFGm
	*/

	/**
	 * @brief Convert a colour enumeration to an ANSI escape sequence.
	 *
	 * @param[in]  color     Requested colour.
	 * @param[out] ANSIcolor Buffer receiving the ANSI escape sequence.
	 *
	 * @return true if @p color is valid, false otherwise.
	 */
	static bool getColorCodeUnix(const enum Color color, char* const ANSIcolor){
		// assume no error
		bool status = true;
		switch (color){
			case FORE_RED:
				strcpy(ANSIcolor, "\x1b[31m");
				break;
			case FORE_GREEN:
				strcpy(ANSIcolor, "\x1b[32m");
				break;
			case FORE_YELLOW:
				strcpy(ANSIcolor, "\x1b[33m");
				break;
			case FORE_BLUE:
				strcpy(ANSIcolor, "\x1b[34m");
				break;
			case FORE_MAGENTA:
				strcpy(ANSIcolor, "\x1b[35m");
				break;
			case FORE_CYAN:
				strcpy(ANSIcolor, "\x1b[36m");
				break;
			case FORE_WHITE:
				strcpy(ANSIcolor, "\x1b[37m");
				break;
			case FORE_BRIGHT_RED:
				strcpy(ANSIcolor, "\x1b[91m");
				break;
			case FORE_BRIGHT_GREEN:
				strcpy(ANSIcolor, "\x1b[92m");
				break;
			case FORE_BRIGHT_YELLOW:
				strcpy(ANSIcolor, "\x1b[93m");
				break;
			case FORE_BRIGHT_BLUE:
				strcpy(ANSIcolor, "\x1b[94m");
				break;
			case FORE_BRIGHT_MAGENTA:
				strcpy(ANSIcolor, "\x1b[95m");
				break;
			case FORE_BRIGHT_CYAN:
				strcpy(ANSIcolor, "\x1b[96m");
				break;
			case FORE_BRIGHT_WHITE:
				strcpy(ANSIcolor, "\x1b[97m");
				break;
			default:
				// unrecognised colour code, assume white (black terminal)
				strcpy(ANSIcolor, "\x1b[97m");
				status = false;
				break;
		}
		return status;
	}
#endif

// neither the text of the message (const char*) nor to which string the pointer
// is pointing to (const message) should change
void printColorText(const char* const message, const enum Color color){
	#ifdef OS_WINDOWS
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;

		// save current attributes to restore the console back to normal
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;

		WORD textColour;
		getColorCodeWindows(color, &textColour);
		SetConsoleTextAttribute(hConsole, textColour);
		printf("%s", message);

		// restore original attributes (like ANSI reset)
		SetConsoleTextAttribute(hConsole, saved_attributes);
	#elif defined(OS_UNIX)
		// "\x1b[97m" has 5 characters: ESC (\x1b), [, 9, 7, m, plus the null
		// terminator \0 => array length is 6
		char ANSIcolor[6];
		getColorCodeUnix(color, ANSIcolor);
		printf("%s%s%s", ANSIcolor, message, ANSI_RESET);
	#endif
}


void printMessage(const char* const message, const enum MessageLevel level){
	enum Color textColor;
	switch (level){
		case MSG_BASIC:
			textColor = FORE_WHITE;
			break;
		case MSG_ERROR:
			textColor = FORE_RED;
			break;
		case MSG_WARNING:
			textColor = FORE_YELLOW;
			break;
		case MSG_SUCCESS:
			textColor = FORE_BRIGHT_GREEN;
			break;
		case MSG_INFO:
			textColor = FORE_BRIGHT_CYAN;
			break;
		default:
			// assume that the terminal has black background by default
			textColor = FORE_WHITE;
			break;
	}
	printColorText(message, textColor);
}