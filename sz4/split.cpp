/**
 *    @file split.cpp
 *    Be kell adni!
 *    Ide kerül a Split osztály megvalósítása
 */

#include "split.hpp"
#include "memtrace.h"

Split::Split(char sep)
    : Allapotgep<SplitAllapot, SplitInput, char>(SplitAllapot::alap, tabla),
      sep(sep) {
    kov();
    tabla[SplitAllapot::alap] = {
        {SplitInput::elvalaszto, new Nop(SplitAllapot::elvalaszto_volt)},
        {SplitInput::egyeb, new Kiir(SplitAllapot::alap, *this)}
    };
    tabla[SplitAllapot::elvalaszto_volt] = {
        {SplitInput::elvalaszto, new Nop(SplitAllapot::elvalaszto_volt)},
        {SplitInput::egyeb, new UjDarab(SplitAllapot::alap, *this)}
    };
}
