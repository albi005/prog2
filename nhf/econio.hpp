#pragma once

// based on https://github.com/czirkoszoltan/c-econio

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