//
// Created by Zoli on 2023. 10. 24..
//

#ifndef HAZI_LEGFONTOSABB_H
#define HAZI_LEGFONTOSABB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "econio.h"

typedef struct Datum{
    int ev,nap,honap;
}datum;


typedef struct Ugyfel{
    char szemely_szam[9];
    char *nev;
    char *email;
    unsigned long long int telefon;
    int autok;
    struct Ugyfel* kov;
}ugyfel;

typedef struct Javitas{
    char *elvegzett_munka;
    int ara;
    datum idopont;
    float garancia;
    struct Javitas* kov;
    struct Javitas* elo;
}javitas;

typedef struct Auto{
    bool akiv;
    char *rendszam;
    char *tipus;
    char szemely_szam[9];
    javitas *munka;
    datum ervenyes;
    struct Auto* kov;
    struct Auto* elo;
}gepjarmu;

#endif //HAZI_LEGFONTOSABB_H
