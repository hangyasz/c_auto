#include "fugveny.h"
#include "legfontosabb.h"
#include "falj_kezel.h"

bool email_ellenoriz(char *email) {
    int db = 0;
    int kukac_db = 0;
    int pont_db=0;
    while (email[db] != '\0') {
        if (email[db] == '@')
            ++kukac_db;
        if (kukac_db == 1)
            if (email[db] == '.')
                ++pont_db;
        ++db;
    }
    if (kukac_db == 1 && pont_db > 0)
        return true;
    else
        return false;
}

bool karakter_ellenoriz(char *szoveg) {
    int db = 0;
    while (szoveg[db] != '\0') {
        if (szoveg[db] == '/' || szoveg[db] == '#')
            return false;
        ++db;
    }
    return true;
}


char *hozzafuz(char *jelenlegi, char uj_karakter) {
    if (jelenlegi == NULL) {
        char *szoveg = (char *) malloc(sizeof(char) * 2);
        szoveg[0] = uj_karakter;
        szoveg[1] = '\0';
        return szoveg;
    }
    unsigned int hosz = strlen(jelenlegi);

    char *szoveg = (char *) malloc(sizeof(char) * (hosz + 2));
    strcpy(szoveg, jelenlegi);
    free(jelenlegi);
    szoveg[hosz] = uj_karakter;
    szoveg[hosz + 1] = '\0';
    return szoveg;
}


javitas *lancol_javitas(javitas *elso, char *hibba, int ara, datum idopont, float gari) {
    if (elso == NULL) {
        javitas *uj = (javitas *) malloc(sizeof(javitas));
        uj->elvegzett_munka = hibba;
        uj->ara = ara;
        uj->idopont = idopont;
        uj->garancia = gari;
        uj->kov = NULL;
        uj->elo = NULL;
        return uj;
    }

    javitas *elozo;

    for (elozo = elso; elozo->kov != NULL; elozo = elozo->kov);

    javitas *seged = (javitas *) malloc(sizeof(javitas));
    elozo->kov = seged;
    seged->elvegzett_munka = hibba;
    seged->ara = ara;
    seged->idopont = idopont;
    seged->garancia = gari;
    seged->kov = NULL;
    seged->elo = elozo;
    return elso;
}

gepjarmu *
lancol_autok(gepjarmu *adat, char tulaj[9], char *rendszam, char *tipus, datum muszaki, javitas *javitasok, bool aktiv) {
    if (adat == NULL) {
        gepjarmu *uj = (gepjarmu *) malloc(sizeof(gepjarmu));
        if (uj == NULL)
            return NULL;
        uj->kov = NULL;
        uj->elo = NULL;
        strcpy(uj->szemely_szam, tulaj);
        uj->rendszam = rendszam;
        uj->tipus = tipus;
        uj->ervenyes = muszaki;
        uj->munka = javitasok;
        uj->akiv = aktiv;
        return uj;
    }
    gepjarmu *elozo;
    for (elozo = adat; elozo->kov != NULL; elozo = elozo->kov);
    gepjarmu *uj = (gepjarmu *) malloc(sizeof(gepjarmu));
    if (uj == NULL)
        return NULL;
    elozo->kov = uj;
    uj->kov = NULL;
    uj->elo = elozo;
    strcpy(uj->szemely_szam, tulaj);
    uj->rendszam = rendszam;
    uj->tipus = tipus;
    uj->ervenyes = muszaki;
    uj->munka = javitasok;
    uj->akiv = aktiv;
    return adat;

}

void felszabadit_ugyfel(ugyfel *adat) {
    ugyfel *leptet;
    ugyfel *kov;
    for (leptet = adat; leptet != NULL; leptet = kov) {
        kov = leptet->kov;
        free(leptet->email);
        free(leptet->nev);
        free(leptet);
    }
}

void felszabadit_auto(gepjarmu *adat) {
    gepjarmu *leptet;
    gepjarmu *kov;
    for (leptet = adat; leptet != NULL; leptet = kov) {
        kov = leptet->kov;
        free(leptet->tipus);
        free(leptet->rendszam);
        javitas *leptett_jav;
        javitas *kov_jav;
        for (leptett_jav = leptet->munka; leptett_jav != NULL; leptett_jav = kov_jav) {
            kov_jav = leptett_jav->kov;
            free(leptett_jav->elvegzett_munka);
            free(leptett_jav);
        }
        free(leptet);
    }
}

char *hosszu_sort_olvas() {
    int db = 0;
    char *szoveg = (char *) malloc(sizeof(char) * 1);
    szoveg[0] = '\0';
    char ujkar;
    scanf(" %c", &ujkar);
    char *ujszoveg = (char *) malloc(sizeof(char) * (db + 2));
    if (ujkar != '\n') {
        free(szoveg);
        szoveg = ujszoveg;
        szoveg[db] = ujkar;
        szoveg[db + 1] = '\0';
        ++db;
    } else
        return szoveg;
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
        char *ujszoveg = (char *) malloc(sizeof(char) * (db + 2));
        strcpy(ujszoveg, szoveg);
        free(szoveg);
        szoveg = ujszoveg;
        szoveg[db] = ujkar;
        szoveg[db + 1] = '\0';
        ++db;
    }

    return szoveg;
}