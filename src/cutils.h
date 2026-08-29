/**
 * @file cutils.h
 * @brief Collection of general-purpose C utilities.
 *
 * Provides utilities for printing coloured text and messages to a terminal.
 *
 * @author Andrea Pinardi <andreapinardi319@gmail.com>
 * @version 1.0.0
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

	/**
	 * @brief Available foreground text colours.
	 */
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

	/**
	 * @brief Message severity levels.
	 *
	 * Each level is associated with a predefined text colour.
	 */
	enum MessageLevel {
		MSG_BASIC,
		MSG_ERROR,
		MSG_WARNING,
		MSG_SUCCESS,
		MSG_INFO
	};


	/**
	 * @brief Print coloured text to the terminal.
	 *
	 * The text colour is temporarily changed to @p color and restored
	 * after the message has been printed.
	 *
	 * @param[in] message Text to print.
	 * @param[in] color   Foreground colour.
	 */
	void printColorText(const char* const message, const enum Color color);

	/**
	 * @brief Print a message using a predefined message level.
	 *
	 * @param[in] message Text to print.
	 * @param[in] level   Message severity level.
	 */
	void printMessage(const char* const message, const enum MessageLevel level);
#endif