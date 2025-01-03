//
// Created by Zoli on 2023. 11. 07..
//

#ifndef HAZI_SZERVIZ_KEZEL_H
#define HAZI_SZERVIZ_KEZEL_H

#include "legfontosabb.h"

void sz_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat);
int talalt_auto(gepjarmu *adot_auto);
void javitas_torles(javitas **adat);
void javitas_listaz(javitas *lista);
void szerviz_rogzites(gepjarmu *adotauto);

#endif //HAZI_SZERVIZ_KEZEL_H
