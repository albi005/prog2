#include <cstring>
#include <cctype>
#include "nem_oo.h"

/**
 * \file nem_oo_teszt.cpp
 * (UTF-8 kodolasu fajl. Allitsa at a kodolast,
 *  ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * FELADATOK:
 *  1. Ebben a fájlban valósítsa meg a nem_oo.h állományban deklarált függvényeket!
 *
 * Ügyeljen a helyes névtér használatra!
 *   Tipp: Használja a scope operátort, vagy nyisson névteret!
 */

namespace sajat {	/// saját névtér

    /**
     * Saját atoi.
     * Számjegyeket tartalmazó karaktersorozat átalakítása int-re.
     * Helyes számjegysorozat végét white space, vagy sztring vége ('\0') jelzi.
     *   Ha a számjegysorozatban olyan számjegy, vagy betű fordul elő,
     *   ami nem érvényes az adott számrendszerben, az hiba.
     *   Pl. hármas számrendszerben nem fordulhat elő a 3-as számjegy, de az A betű sem.
     * Hiba esetén egy const char* típusú kivételt kell dobni, melynek értéke
     * az Ön neptun azonosítója!
     * @param p    - pointer a sztringre
     * @param base - számrendszer alapja (0-10)
     * @return     - base számrendszerben értelmezett szám
     */
    int atoi(const char *p, int base) {
        int n = 0;
        for (int i = 0; p[i] != ' ' && p[i] != 0; i++) {
            char c = tolower(p[i]);
            bool isNumberCharacter = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z');
            if (!isNumberCharacter) throw "GL6IFB";

            int x;
            if (c >= '0' && c <= '9') x = c - '0';
            else x = c - 'a' + 10;

            if (x >= base) throw "GL6IFB";

            n *= base;
            n += x;
        }
        return n;
    }

    /**
     * Sajat strcat.
     * Két C stílusú sztring (nullával lezárt karaktersorozat) összefűzése
     * A függvény dinamikusan foglal helyet az eredménynek.
     * @param p1   - pointer az első sztringre
     * @param p2   - pointer az másik sztringre
     * @return     - dinamikusan foglalt terület címe, ahova az eredmény kerül (hívónak kell felszabadítania)
     */
    char *strcat(const char *p1, const char *p2) {
        size_t len = strlen(p1) + strlen(p2);
        char* res = new char[len + 1];
        strcpy(res, p1);
        std::strcat(res, p2);
        return res;
    }

    /**
     * unique
     * A paraméterként kapott két pointer közötti karaktersorozatból kihagyja az egymás után ismétlődő
     * karaktereket (char). A sorozatot az eredeti helyén hagyja!
     * @param first - pointer az adatok kezdetére
     * @param last  - pointer, ami az utolsó adat után mutat
     * @return      - pointer, ami az új sorozat utolsó adata után mutat (a kihagyással rövidült a sorozat)
     */
    char *unique(char *first, char *last) {
        char prev = 0;
        char* src = first;
        char* dst = first;
        while (src != last) {
            if (*src != prev) {
                prev = *src;
                *dst = *src;
                dst++;
            }
            src++;
        }
        *dst = 0;
        return dst;
    }


}
