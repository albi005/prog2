// based on https://github.com/czirkoszoltan/c-econio

#include "econio.hpp"
#include "constants.hpp"

#if defined(_WIN32) || defined(_WIN64)

#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

static WORD bgcolor = COL_BLACK;
static WORD fgcolor = COL_LIGHTGRAY;
static bool rawmode = false;

#define STDOUT GetStdHandle(STD_OUTPUT_HANDLE)

void econio_rawmode() { rawmode = true; }

void econio_normalmode() { rawmode = false; }

int econio_getch() {
    static struct {
        int code;
        EconioKey key;
    } windowskeycodes[] = {
        {72, KEY_UP},          {80, KEY_DOWN},
        {75, KEY_LEFT},        {77, KEY_RIGHT},
        {73, KEY_PAGEUP},      {81, KEY_PAGEDOWN},
        {71, KEY_HOME},        {79, KEY_END},
        {82, KEY_INSERT},      {83, KEY_DELETE},
        {141, KEY_CTRLUP},     {145, KEY_CTRLDOWN},
        {115, KEY_CTRLLEFT},   {116, KEY_CTRLRIGHT},
        {134, KEY_CTRLPAGEUP}, {118, KEY_CTRLPAGEDOWN},
        {119, KEY_CTRLHOME},   {117, KEY_CTRLEND},
        {146, KEY_CTRLINSERT}, {147, KEY_CTRLDELETE},
        {-1, KEY_UNKNOWNKEY},
    };

    assert(rawmode);
    int code = _getch();
    if (code == 0x7F)
        return KEY_BACKSPACE;
    if (code == 0x0D)
        return KEY_ENTER;
    if (code != 0xE0)
        return code;
    code = _getch();

    for (int i = 0; windowskeycodes[i].code != -1; ++i)
        if (code == windowskeycodes[i].code)
            return windowskeycodes[i].key;
    return KEY_UNKNOWNKEY;
}

#else // defined _WIN32

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>

void econio_flush() { fflush(stdout); }

void econio_rawmode() {
    int fd = fileno(stdin);
    struct termios attr;
    tcgetattr(fd, &attr);
    attr.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(fd, TCSADRAIN, &attr);
    setvbuf(stdin, NULL, _IONBF, BUFSIZ);
}

void econio_normalmode() {
    int fd = fileno(stdin);
    struct termios attr;
    tcgetattr(fd, &attr);
    attr.c_lflag |= ICANON | ECHO;
    tcsetattr(fd, TCSADRAIN, &attr);
    setvbuf(stdin, NULL, _IOLBF, BUFSIZ);
}

static bool inrawmode() {
    int fd = fileno(stdin);
    struct termios attr;
    tcgetattr(fd, &attr);
    return (attr.c_lflag & (ICANON | ECHO)) == 0;
}

bool econio_kbhit() {
    assert(inrawmode());
    econio_flush();

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(fileno(stdin), &rfds);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    int retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select()");
        return false;
    }
    return retval != 0;
}

static int rawgetch() { return fgetc(stdin); }

int econio_getch() {
    static struct {
        char const* escape;
        char key;
    } unixkeycodes[] = {
        {"\033OP", KEY_F1},
        {"\033OQ", KEY_F2},
        {"\033OR", KEY_F3},
        {"\033OS", KEY_F4},
        {"\033[15~", KEY_F5},
        {"\033[17~", KEY_F6},
        {"\033[18~", KEY_F7},
        {"\033[19~", KEY_F8},
        {"\033[20~", KEY_F9},
        {"\033[21~", KEY_F10},
        {"\033[23~", KEY_F11},
        {"\033[24~", KEY_F12},
        {"\033[A", KEY_UP},
        {"\033[B", KEY_DOWN},
        {"\033[D", KEY_LEFT},
        {"\033[C", KEY_RIGHT},
        {"\033[5~", KEY_PAGEUP},
        {"\033[6~", KEY_PAGEDOWN},
        {"\033[H", KEY_HOME},
        {"\033[F", KEY_END},
        {"\033[2~", KEY_INSERT},
        {"\033[3~", KEY_DELETE},
        {"\033[1;5A", KEY_CTRLUP},
        {"\033[1;5B", KEY_CTRLDOWN},
        {"\033[1;5D", KEY_CTRLLEFT},
        {"\033[1;5C", KEY_CTRLRIGHT},
        {"\033[5;5~", KEY_CTRLPAGEUP},
        {"\033[6;5~", KEY_CTRLPAGEDOWN},
        {"\033[1;5H", KEY_CTRLHOME},
        {"\033[1;5F", KEY_CTRLEND},
        {"\033[3;5~", KEY_CTRLDELETE},
        {NULL, KEY_UNKNOWNKEY},
    };

    assert(inrawmode());
    econio_flush();

    enum { bufsize = 10 };

    char s[bufsize];
    int i = 0;
    s[i++] = rawgetch();
    if (s[i - 1] == 0x7F)
        return KEY_BACKSPACE;
    if (s[i - 1] != 0x1B ||
        !econio_kbhit()) // only an escape sequence if other chars can be read
        return s[i - 1];

    // read following chars and concatenate to see the escape sequence
    s[i++] = rawgetch();
    if (s[i - 1] == 'O') { // VT100 f1-f4: OP-OS
        s[i++] = rawgetch();
    } else if (s[i - 1] ==
               '[') { // other: always delimited by uppercase char or tilde
        s[i++] = rawgetch();
        while (!(isupper(s[i - 1]) || s[i - 1] == '~') && (i < bufsize - 1))
            s[i++] = rawgetch();
    } else { // unknown sequence, return verbatim
        ungetc(s[i - 1], stdin);
        return s[0];
    }
    s[i] = '\0';
    for (i = 0; unixkeycodes[i].escape != NULL; ++i)
        if (strcmp(unixkeycodes[i].escape, s) == 0)
            return unixkeycodes[i].key;
    return KEY_UNKNOWNKEY;
}

#endif // defined _WIN32
