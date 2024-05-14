// from https://infoc.eet.bme.hu/megjelenites/

#ifndef ECONIO_H
#define ECONIO_H

#include "constants.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Send output to the terminal. To be called if many characters were
 * drawn to the terminal and there was no \n at the end.
 */
void econio_flush();

/** Set the title of the terminal window. */
void econio_set_title(char const* title);

/**
 * Switch the terminal to raw mode, to detect F1-F10, cursor keys and
 * other controlling keys. Use econio_getch() and econio_kbhit() afterwards.
 * Characters are not echoed to the screen when in raw mode.
 * Switching back to line-oriented mode is possible using econio_normalmode().
 */
void econio_rawmode();

/**
 * Switch the terminal back to normal, line-oriented mode. Characters
 * are echoed to the screen when in normal mode.
 */
void econio_normalmode();

/**
 * Detect if a key is pressed. If so, it can be read with econio_getch().
 * Only to be used after calling econio_rawmode().
 */
bool econio_kbhit();

/**
 * Get one raw character from terminal. This can detect F1-F10, cursor keys,
 * backspace and other controlling keys: see the keyboard constants.
 * ASCII code is returned for other keys. Non-ASCII keys probably won't work.
 * Characters are not echoed to the screen when in raw mode.
 * Only to be used after calling econio_rawmode().
 * Note that backspace will be code 8, regardless of terminal settings
 * (whether it sent BS or DEL char). Enter will always be 10, even on Windows.
 * On Windows, this function sometimes returns 0's, so just ignore them.
 * Also function keys are not supported on Windows.
 */
int econio_getch();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
