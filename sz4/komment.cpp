#include "komment.hpp"
#include "memtrace.h"
#include <string>

Komment::Komment() : Allapotgep(KommentAllapot::alap, tabla) {
    tabla[KommentAllapot::alap] = {
        {KommentInput::per, new Nop(KommentAllapot::per_volt)},
        {KommentInput::csillag, new Kiir(KommentAllapot::alap, *this)},
        {KommentInput::egyeb, new Kiir(KommentAllapot::alap, *this)}
    };
    tabla[KommentAllapot::per_volt] = {
        {KommentInput::per, new KiirKonst(KommentAllapot::per_volt, *this, '/')
        },
        {KommentInput::csillag, new Nop(KommentAllapot::komment)},
        {KommentInput::egyeb,
         new KiirKonstEsKiir(KommentAllapot::alap, *this, '/')}
    };
    tabla[KommentAllapot::komment] = {
        {KommentInput::per, new Nop(KommentAllapot::komment)},
        {KommentInput::csillag, new Nop(KommentAllapot::komment_csillag_volt)},
        {KommentInput::egyeb, new Nop(KommentAllapot::komment)}
    };
    tabla[KommentAllapot::komment_csillag_volt] = {
        {KommentInput::per, new Nop(KommentAllapot::alap)},
        {KommentInput::csillag, new Nop(KommentAllapot::komment_csillag_volt)},
        {KommentInput::egyeb, new Nop(KommentAllapot::komment_csillag_volt)}
    };
}
