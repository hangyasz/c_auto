
#ifndef HAZI_UGYFEL_KEZEL_H
#define HAZI_UGYFEL_KEZEL_H

#include "legfontosabb.h"
#include "fugveny.h"

void u_kezel(ugyfel **ugygelek, gepjarmu **autok);
void listaz_ugyfel(ugyfel *ugyfelek);
void torol_ugyfel(ugyfel **ugyfelk, gepjarmu **autok);
void uj_u_hozzaad(ugyfel **ugyfelek, char *szemelysz);
void uj_ugyfel(ugyfel **ugyfelek_lista,gepjarmu **autok);
ugyfel *u_keres(ugyfel *ugyfelek, char *szemely_szam);
void kezel_ugyfel(ugyfel **ugyfelek, gepjarmu *autok);


#endif //HAZI_UGYFEL_KEZEL_H
