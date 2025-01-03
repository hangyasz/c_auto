//
// Created by Zoli on 2023. 11. 07..
//

#include "szerviz_kezel.h"
#include "legfontosabb.h"
#include "auto_kezel.h"
#include "fugveny.h"
#include "falj_kezel.h"


void szerviz_rogzites(gepjarmu *adotauto) {
    javitas *akt = adotauto->munka;
    if (akt == NULL) {
        javitas *uj = (javitas *) malloc(sizeof(javitas));
        printf("kerem irja be javitas: ");
        char *munka = hosszu_sort_olvas();
        bool munka_el = karakter_ellenoriz(munka);
        while (!munka_el) {
            econio_textcolor(COL_RED);
            printf("kerme ne legyen a bevit szovegben / es # karakter\n");
            printf("kerem irja be javitas: ");
            free(munka);
            munka = hosszu_sort_olvas();
            munka_el = karakter_ellenoriz(munka);
            econio_textcolor(COL_RESET);
        }
        uj->elvegzett_munka = munka;
        printf("menyibe kerult: ");
        scanf("%d", &uj->ara);
        printf("kerem hogy hamy ev garanciat valalunk: ");
        scanf("%f", &uj->garancia);
        printf("javitas idopontaj ev.honap.nap formatumba pl(2023.11.7): ");
        while (scanf("%d.%d.%d", &uj->idopont.ev, &uj->idopont.honap, &uj->idopont.nap) != 3) {
            econio_textcolor(COL_RED);
            printf("kerem igy vigye be az adatot ev.honap.nap formatumba pl(2023.11.7): ");
            econio_textcolor(COL_RESET);
        }
        uj->elo = NULL;
        uj->kov = NULL;
        adotauto->munka=uj;
        return;
    }
    for (; akt->kov != NULL; akt = akt->kov);
    javitas *uj = (javitas *) malloc(sizeof(javitas));
    printf("kerem irja be javitas: ");
    char *munka = hosszu_sort_olvas();
    bool munka_el = karakter_ellenoriz(munka);
    while (!munka_el) {
        econio_textcolor(COL_RED);
        printf("kerme ne legyen a bevit szovegben / es # karakter\n");
        printf("kerem irja be javitas: ");
        free(munka);
        munka = hosszu_sort_olvas();
        munka_el = karakter_ellenoriz(munka);
        econio_textcolor(COL_RESET);
    }
    uj->elvegzett_munka = munka;
    printf("menyibe kerult: ");
    scanf("%d", &uj->ara);
    printf("kerem hogy hamy ev garanciat valalunk: ");
    scanf("%f", &uj->garancia);
    printf("javitas idopontaj ev.honap.nap formatumba pl(2023.11.7): ");
    while (scanf("%d.%d.%d", &uj->idopont.ev, &uj->idopont.honap, &uj->idopont.nap) != 3) {
        econio_textcolor(COL_RED);
        printf("kerem igy vigye be az adatot ev.honap.nap formatumba pl(2023.11.7): ");
        econio_textcolor(COL_RESET);
    }
    uj->elo = akt;
    uj->kov = NULL;
    akt->kov = uj;
}

void javitas_listaz(javitas *lista) {
    for (javitas *i = lista; i != NULL; i = i->kov)
        printf("%s arra:%d datum:%d.%d.%d garancia:%g\n", i->elvegzett_munka, i->ara, i->idopont.ev, i->idopont.honap,
               i->idopont.nap, i->garancia);
}


void javitas_torles(javitas **adat) {
    javitas *akt = *adat;
    javitas *lista = akt;
    javitas *bufr;
    while (akt != NULL) {
        printf("%s arra:%d datum:%d.%d.%d garancia:%g\n", akt->elvegzett_munka, akt->ara, akt->idopont.ev,
               akt->idopont.honap,
               akt->idopont.nap, akt->garancia);
        char valasz;
        econio_textcolor(COL_MAGENTA);
        printf("szeretne torolni a javitast? igen(i) nem(egyeb betu): ");
        scanf(" %c", &valasz);
        econio_textcolor(COL_RESET);
        valasz = tolower(valasz);
        if (valasz == 'i') {
            if (akt->elo == NULL) {
                lista = akt->kov;
                free(akt->elvegzett_munka);
                free(akt);
                akt = lista;
            } else {
                if (akt->kov != NULL)
                    akt->kov = akt->elo;
                akt->elo = akt->kov;
                bufr = akt->kov;
                free(akt->elvegzett_munka);
                free(akt);
                akt = bufr;
            }
        } else
            akt = akt->kov;
    }
    *adat = lista;


}

 int talalt_auto(gepjarmu *adot_auto) {
    printf("Az auto tipusa: %s\n", adot_auto->tipus);
    int valaszto;
    do {
        econio_textcolor(COL_GREEN);
        printf("Javitas rogzitese (1)\n");
        econio_textcolor(COL_CYAN);
        printf("Korabbi javitasok listazasa (2)\n");
        econio_textcolor(COL_MAGENTA);
        printf("Javitas torlese (3)\n");
        econio_textcolor(COL_YELLOW);
        printf("Visszalepes (4)\n");
        econio_textcolor(COL_RED);
        printf("Kilepes a szerviz menubol (5)\n");
        econio_textcolor(COL_RESET);
        scanf(" %d", &valaszto);
        switch (valaszto) {
            case 1:
                szerviz_rogzites(adot_auto);
                if (!auto_iras(adot_auto)) {
                    econio_textcolor(COL_RED);
                    printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            case 2:
                javitas_listaz(adot_auto->munka);
                break;
            case 3:
                javitas_torles(&adot_auto->munka);
                if (!auto_iras(adot_auto)){
                    econio_textcolor(COL_RED);
                    printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            case 4:
                return 4;
                break;
            case 5:
                return 5;
                break;
            default:
                printf("Kerem a listabol valszon\n");
                break;
        }

    } while (valaszto != 'e');
}

void sz_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat) {
    gepjarmu *autok = *auto_adat;
    ugyfel *ugyfelek = *ugyfel_adat;
    char *rendszam = NULL;
    int hoazada_valasz;
    int valszto=0;
    bool u_iras;
    bool a_iras;
    do {
        printf("Kerem vigye be a rendszamot: ");
        rendszam = hosszu_sort_olvas();
        rendszam = strupr(rendszam);
        if (karakter_ellenoriz(rendszam)) {
            gepjarmu *kereset_auto = keres_rendszam_alapjan(rendszam, autok);
            if (kereset_auto == NULL) {
                do {
                    econio_textcolor(COL_MAGENTA);
                    printf("Hozza szeretne adni az alábbi rendszamot: %s a rendszerhez\n", rendszam);
                    econio_textcolor(COL_CYAN);
                    printf("Hozzaadas (1)\n");
                    econio_textcolor(COL_MAGENTA);
                    printf("Nem hozzaadas (2)\n");
                    econio_textcolor(COL_YELLOW);
                    printf("Visszalepes (4)\n");
                    econio_textcolor(COL_RESET);
                    scanf(" %d", &hoazada_valasz);
                    econio_textcolor(COL_RESET);
                    switch (hoazada_valasz) {
                        case 1:
                            auto_hozzaad(&autok, rendszam, &ugyfelek);
                            u_iras = !ugyfel_iras(ugyfelek);
                            a_iras = !auto_iras(autok);
                            if (u_iras && a_iras) {
                                econio_textcolor(COL_RED);
                                printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                                econio_textcolor(COL_RESET);
                            }
                            break;
                        case 2:
                            free(rendszam);
                            break;
                        case 4:
                            free(rendszam);
                            valszto = 5;
                            break;
                        default:
                            free(rendszam);
                            printf("Kerem a listabol valszol\n");
                            break;
                    }
                } while (hoazada_valasz != 1 && hoazada_valasz != 2 && hoazada_valasz != 4);
            } else {
                free(rendszam);
                valszto = talalt_auto(kereset_auto);
            }
        } else {
            econio_textcolor(COL_RED);
            printf("kerem ne legyen a bevitt szovegben / es # karakter\n");
            econio_textcolor(COL_RESET);
            free(rendszam);
            rendszam = NULL;
        }
    } while (valszto != 5);
    *auto_adat = autok;
    *ugyfel_adat = ugyfelek;
}
