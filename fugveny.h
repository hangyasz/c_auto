//
// Created by Zoli on 2023. 10. 24..
//

#ifndef HAZI_FUGVENY_H
#define HAZI_FUGVENY_H

#include "legfontosabb.h"

char *hozzafuz(char *jelenlegi, char karrakte);
javitas* lancol_javitas(javitas* elso, char *hibba, int ara, datum idopont, float gari);
gepjarmu *lancol_autok(gepjarmu *adat, char tulaj[9], char *rendszam, char *tipus, datum muszaki, javitas *javitasok, bool aktiv);
void felszabadit_ugyfel(ugyfel* adat);
void felszabadit_auto(gepjarmu *adat);
char *hosszu_sort_olvas();
bool karakter_ellenoriz(char *szoveg);
bool email_ellenoriz(char *email);

#endif //HAZI_FUGVENY_H
