

#ifndef HAZI_AUTO_KEZEL_H
#define HAZI_AUTO_KEZEL_H
#include "legfontosabb.h"

void osszes_autot_listaz(gepjarmu *lista);
void auto_passzival(gepjarmu *lista, char *szemelyszam);
void autok_listaz_tulaj(gepjarmu *lista,char *szemelyszam);
void a_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat);
int meglevo_auto_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat, gepjarmu *adot_auto);
void atruhaz_auto(ugyfel **ugyfel_lista, gepjarmu *adot);
void auto_torol(gepjarmu *adtod, gepjarmu **auto_lista);
void auto_modosit(gepjarmu *adot_auto, gepjarmu *auto_lista);
void auto_hozzaad(gepjarmu **a_lista, char *uj_rendszam, ugyfel **u_lista);
void auto_lista_bovit(gepjarmu **adat, char *uj_rendszam, char tulaj[9]);
gepjarmu *keres_rendszam_alapjan(char *rendszm, gepjarmu *autok_lista);
void autok_szemely_mod(char *regi, char *uj, gepjarmu* autok);
void atok_torles_szemelyszam(char *szemely,gepjarmu **autok);
void muszaki_modosit(gepjarmu *adot_auto);

#endif //HAZI_AUTO_KEZEL_H
