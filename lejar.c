//
// Created by Zoli on 2023. 11. 07..
//

#include "lejar.h"
#include "legfontosabb.h"

void tulaj_adat(char *szemjszam, ugyfel *ugyfelek) {
    for (ugyfel *akt = ugyfelek; akt != NULL; akt = akt->kov) {
        if (strcmp(szemjszam, akt->szemely_szam) == 0) {
            printf("%s %lld %s\n", akt->nev, akt->telefon, akt->email);
            return;
        }
    }
    econio_textcolor(COL_RED);
    printf("az adot ugyfel nem talahato\n");
    econio_textcolor(COL_RESET);
}

void kozeli_lejar(gepjarmu *autok, ugyfel *ugyfelek) {
    datum vizsgalt;
    printf("kerem vigye be az evet es a honatpot az amiben szeretne megnezni a lejart/lejar muszakikat\nformatum ev.honap: ");
    while (scanf("%d.%d", &vizsgalt.ev, &vizsgalt.honap) != 2) {
        econio_textcolor(COL_RED);
        printf("nem jo\nkerem vigye be az evet es a honatpot az amiben szeretne megnezni a lejart/lejar muszakikat\nformatum ev.honap: ");
        econio_textcolor(COL_RESET);
    }
    for (gepjarmu *akt = autok; akt != NULL; akt = akt->kov) {
        if (akt->akiv && akt->ervenyes.ev == vizsgalt.ev && akt->ervenyes.honap == vizsgalt.honap) {
            printf("Rendszam: %s pontos nap:%d ", akt->rendszam, akt->ervenyes.nap);
            tulaj_adat(akt->szemely_szam, ugyfelek);
        }
    }
    printf("Nyomj meg egy 'f'-t a folytatashoz.\n");
    while (getchar() != 'f');
}

void lejart(gepjarmu *autok, ugyfel *ugyfelek) {
    datum vizsgalt;
    printf("kerem vigye be az evet.honatpot.napot az amiben szeretne megnezni a lejart/lejar muszakikat\nformatum ev.honap.nap: ");
    while (scanf("%d.%d.%d", &vizsgalt.ev, &vizsgalt.honap, &vizsgalt.nap) != 3) {
        econio_textcolor(COL_RED);
        printf("nem jo\nkerem vigye be az evet es a honatpot az amiben szeretne megnezni a lejart/lejar muszakikat\nformatum ev.honap.nap: ");
        econio_textcolor(COL_RESET);
    }
    for (gepjarmu *akt = autok; akt != NULL; akt = akt->kov) {
        if (akt->akiv && akt->ervenyes.ev <= vizsgalt.ev && akt->ervenyes.honap <= vizsgalt.honap &&
            akt->ervenyes.nap <= vizsgalt.nap) {
            printf("Rendszam: %s lejart: %d.%d.%d ", akt->rendszam, akt->ervenyes.ev, akt->ervenyes.honap,
                   akt->ervenyes.nap);
            tulaj_adat(akt->szemely_szam, ugyfelek);
        }
    }
    printf("Nyomj meg egy 'f'-t a folytatashoz.\n");
    while (getchar() != 'f');
}
