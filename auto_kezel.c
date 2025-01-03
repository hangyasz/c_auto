#include "auto_kezel.h"
#include "legfontosabb.h"
#include "fugveny.h"
#include "ugyfel_kezel.h"
#include "falj_kezel.h"

void auto_lista_bovit(gepjarmu **adat, char *uj_rendszam, char tulaj[9]) {
    datum muszaki;
    if (*adat == NULL) {
        gepjarmu *uj = (gepjarmu *) malloc(sizeof(gepjarmu));
        uj->kov = NULL;
        uj->elo = NULL;
        strcpy(uj->szemely_szam, tulaj);
        uj->rendszam = uj_rendszam;
        printf("Kerem az auto markajat es tipusat: ");
        char *tipus = hosszu_sort_olvas();
        bool tipus_eln = karakter_ellenoriz(tipus);
        while (!tipus_eln) {
            econio_textcolor(COL_RED);
            printf("Kerem, ne legyen a bevitt szovegben / es # karakter\n");
            printf("Kerem az auto markajat es tipusat: ");
            free(tipus);
            tipus = hosszu_sort_olvas();
            tipus_eln = karakter_ellenoriz(tipus);
            econio_textcolor(COL_RESET);
        }
        uj->tipus = tipus;
        printf("Kerem vigye be, hogy meddig ervenyes a muszaki az alabbi formatum szerint ev.honap.nap");
        while (scanf("%d.%d.%d", &muszaki.ev, &muszaki.honap, &muszaki.nap) != 3) {
            econio_textcolor(COL_RED);
            printf("Kerem vigye be, hogy meddig evenyes a muszaki az alábbi formátum szerint ev.honap.nap");
        }
        econio_textcolor(COL_RESET);
        uj->ervenyes = muszaki;
        uj->munka = NULL;
        uj->akiv = true;
        *adat = uj;
        return;
    }
    gepjarmu *lista = *adat;
    gepjarmu *elozo = *adat;
    for (; elozo->kov != NULL; elozo = elozo->kov);
    gepjarmu *uj = (gepjarmu *) malloc(sizeof(gepjarmu));
    elozo->kov = uj;
    uj->kov = NULL;
    uj->elo = elozo;
    strcpy(uj->szemely_szam, tulaj);
    uj->rendszam = uj_rendszam;
    printf("Kerem az auto markajat es tipusat: ");
    char *tipus = hosszu_sort_olvas();
    bool tipus_eln = karakter_ellenoriz(tipus);
    while (!tipus_eln) {
        econio_textcolor(COL_RED);
        printf("Kerem ne legyen a bevitt szovegben / es # karakter\n");
        printf("Kerem az auto markajat es tipusat: ");
        free(tipus);
        tipus = hosszu_sort_olvas();
        tipus_eln = karakter_ellenoriz(tipus);
        econio_textcolor(COL_RESET);
    }
    uj->tipus = tipus;
    printf("Kerem vigye be, hogy meddig ervenyes a muszaki az alabbi formatumban ev.honap.nap");
    while (scanf("%d.%d.%d", &muszaki.ev, &muszaki.honap, &muszaki.nap) != 3) {
        econio_textcolor(COL_RED);
        printf("Kerem vigye be, hogy meddig ervenyes a muszaki az alabbi formatumban ev.honap.nap");
    }
    econio_textcolor(COL_RESET);
    uj->ervenyes = muszaki;
    uj->munka = NULL;
    uj->akiv = true;

    *adat = lista;
}


gepjarmu *keres_rendszam_alapjan(char *rendszm, gepjarmu *autok_lista) {
    for (gepjarmu *lista = autok_lista; lista != NULL; lista = lista->kov)
        if (strcmp(lista->rendszam, rendszm) == 0)
            return lista;
    return NULL;
}

void auto_hozzaad(gepjarmu **a_lista, char *uj_rendszam, ugyfel **u_lista) {
    char szemelyszam[9];
    printf("Kerem az ugyfel szemely szamat: ");
    scanf(" %8s", szemelyszam);
    ugyfel *adot_ugyfel = u_keres(*u_lista, szemelyszam);
    int valsz_nincsen=0;
    if (adot_ugyfel == NULL) {
        do {
            econio_textcolor(COL_MAGENTA);
            printf("Az ugyfel nem talalhato. Kerem valasszon:\n");
            econio_textcolor(COL_YELLOW);
            printf("Uj ugyfel hozzaadasa (1)\n");
            econio_textcolor(COL_CYAN);
            printf("Szemelyszam modositas (2)\n");
            econio_textcolor(COL_RESET);
            scanf(" %d", &valsz_nincsen);
            switch (valsz_nincsen) {
                case 1:
                    uj_u_hozzaad(&*u_lista, szemelyszam);
                    adot_ugyfel = u_keres(*u_lista, szemelyszam);
                    break;
                case 2:
                    printf("kerem az ugy fel szemely szamat: ");
                    scanf(" %8s", szemelyszam);
                    adot_ugyfel = u_keres(*u_lista, szemelyszam);
                    break;
                default:
                    printf("kerem a listabol valaszon\n");
                    break;
            }
        } while (adot_ugyfel == NULL);
    }
    auto_lista_bovit(&*a_lista, uj_rendszam, szemelyszam);
    adot_ugyfel->autok += 1;
}

void auto_modosit(gepjarmu *adot_auto, gepjarmu *auto_lista) {
    int valszto=0;
    do {
        econio_textcolor(COL_CYAN);
        printf("Tipus modositas (1)\n");
        econio_textcolor(COL_MAGENTA);
        printf("Rendszam modositas (2)\n");
        econio_textcolor(COL_YELLOW);
        printf("Autó aktivitasa (3)\n");
        econio_textcolor(COL_GREEN);
        printf("Muszaki modositas (4)\n");
        econio_textcolor(COL_RED);
        printf("Modositas befejezese (5)\n");
        econio_textcolor(COL_RESET);
        scanf(" %d", &valszto);
        switch (valszto) {
            case 1:
                printf("kerem vigyebe az uj modelel es tipus: ");
                char *tipus = hosszu_sort_olvas();
                bool tipus_eln = karakter_ellenoriz(tipus);
                while (!tipus_eln) {
                    econio_textcolor(COL_RED);
                    printf("kerme ne legyen a bevit szovegben / es # karakter\n");
                    printf("kerem vigyebe az uj modelel es tipus: ");
                    free(tipus);
                    tipus = hosszu_sort_olvas();
                    tipus_eln = karakter_ellenoriz(tipus);
                    econio_textcolor(COL_RESET);
                }
                free(adot_auto->tipus);
                adot_auto->tipus = tipus;
                break;
            case 2:
                printf("kerem vigyebe az uj redszamot: ");
                char *rendszam = hosszu_sort_olvas();
                bool rendszam_eln = karakter_ellenoriz(tipus);
                while (!rendszam_eln) {
                    econio_textcolor(COL_RED);
                    printf("kerme ne legyen a bevit szovegben / es # karakter\n");
                    printf("kerem vigyebe az uj modelel es tipus: ");
                    free(rendszam);
                    rendszam = hosszu_sort_olvas();
                    rendszam_eln = karakter_ellenoriz(tipus);
                    econio_textcolor(COL_RESET);
                }
                if (strcmp(rendszam, adot_auto->rendszam) == 0) {
                    econio_textcolor(COL_RED);
                    printf("Az uj es a regi rendszam megegyezik");
                    free(rendszam);
                    econio_textcolor(COL_RESET);
                    break;
                }
                gepjarmu *talat = keres_rendszam_alapjan(rendszam, auto_lista);
                if (talat != NULL) {
                    econio_textcolor(COL_BLUE);
                    printf("az adot auto mar letezik a rendszerben auto:");
                    printf("rendszam: %s statusz: %s tuljdonos:%s adatok:%s\n", rendszam, talat->akiv ? "igen" : "nen",
                           talat->szemely_szam, talat->tipus);
                    free(rendszam);
                    econio_textcolor(COL_RESET);
                    break;
                }
                free(adot_auto->rendszam);
                adot_auto->rendszam = rendszam;
                break;
            case 3:
                printf("Kerem valasszon az auto statusza legyen\n");
                econio_textcolor(COL_GREEN);
                printf("aktív (1)\n");
                econio_textcolor(COL_RED);
                printf("inaktív (0)\n");
                econio_textcolor(COL_RESET);
                int aktivitas_betu=0;
                scanf("%d", &aktivitas_betu);
                aktivitas_betu = tolower(aktivitas_betu);
                if (aktivitas_betu == 1)
                    adot_auto->akiv = true;
                else
                    adot_auto->akiv = false;
                break;
            case 5:
                break;
            case 4:
                muszaki_modosit(adot_auto);
                if (!auto_iras(auto_lista)) {
                    econio_textcolor(COL_RED);
                    printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            default:
                printf("kerem a listabol valaszon");
                break;
        }
    } while (valszto != 5);
}

void auto_torol(gepjarmu *adtod, gepjarmu **auto_lista) {
    gepjarmu *lista = *auto_lista;
    if (adtod->elo == NULL) {
        lista = adtod->kov;
        adtod->kov->elo = NULL;
        free(adtod->tipus);
        free(adtod->rendszam);
        javitas *leptett_jav;
        javitas *kov_jav;
        for (leptett_jav = adtod->munka; leptett_jav != NULL; leptett_jav = kov_jav) {
            kov_jav = leptett_jav->kov;
            free(leptett_jav->elvegzett_munka);
            free(leptett_jav);
        }
        free(adtod);
    } else {
        if (adtod->kov != NULL)
            adtod->kov->elo = adtod->elo;
        adtod->elo->kov = adtod->kov;
        free(adtod->tipus);
        free(adtod->rendszam);
        javitas *leptett_jav;
        javitas *kov_jav;
        for (leptett_jav = adtod->munka; leptett_jav != NULL; leptett_jav = kov_jav) {
            kov_jav = leptett_jav->kov;
            free(leptett_jav->elvegzett_munka);
            free(leptett_jav);
        }
        free(adtod);
    }
    *auto_lista = lista;
}

void atruhaz_auto(ugyfel **ugyfel_lista, gepjarmu *adot) {
    printf("kerem vigyebe az uj tuljdonos szemelyszamt: ");
    char szemelyszm[9];
    scanf("%8s", szemelyszm);
    ugyfel *kers_ugyfel_uj = u_keres(*ugyfel_lista, szemelyszm);
    ugyfel *kers_ugyfel_regi = u_keres(*ugyfel_lista, adot->szemely_szam);
    if (kers_ugyfel_uj == NULL) {
        econio_textcolor(COL_BLUE);
        printf("szeretne e ez az ugyfelet rogziteni? igen(1) nem(0) ");
        int valszot=0;
        scanf("%d", &valszot);
        econio_textcolor(COL_RESET);
        valszot = tolower(valszot);
        if (valszot == 1)
            uj_u_hozzaad(&*ugyfel_lista, szemelyszm);
        else
            return;
    }
    kers_ugyfel_uj = u_keres(*ugyfel_lista, szemelyszm);
    if (kers_ugyfel_uj == NULL) {
        econio_textcolor(COL_RED);
        printf("Vamai hibat tortent");
        econio_textcolor(COL_RESET);
        return;
    }
    strcpy(adot->szemely_szam, szemelyszm);
    kers_ugyfel_uj->autok += 1;
    if (kers_ugyfel_regi != NULL && kers_ugyfel_regi->autok > 0)
        kers_ugyfel_regi->autok -= 1;
}

void muszaki_modosit(gepjarmu *adot_auto) {
    printf("kerem irja be a muszaki ervenyeseget ev.honap. formatumba pl 2023.12.12\n");
    while (scanf("%d.%d.%d", &adot_auto->ervenyes.ev, &adot_auto->ervenyes.honap, &adot_auto->ervenyes.nap) != 3) {
        econio_textcolor(COL_RED);
        printf("Nem jo!\nkerem irja be a muszaki ervenyeseget ev.honap. formatumba pl 2023.12.12\n");
        econio_textcolor(COL_RESET);
    }
}

int meglevo_auto_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat, gepjarmu *adot_auto) {
    gepjarmu *auto_lista = *auto_adat;
    ugyfel *ugyfel_lista = *ugyfel_adat;
    int valszto=0;
    bool u_iras;
    bool a_iras;
    do {
        if (adot_auto->akiv) {
            econio_textcolor(COL_GREEN);
            printf("Az auto adatai:\nStatusz: Aktiv\nRendszam: %s\n Tulajdonos: %s\nTipus: %s\nMuszaki ervenyes:%d.%d.%d\n",
                   adot_auto->rendszam, adot_auto->szemely_szam, adot_auto->tipus, adot_auto->ervenyes.ev,
                   adot_auto->ervenyes.honap, adot_auto->ervenyes.nap);
            econio_textcolor(COL_RESET);
        } else {
            econio_textcolor(COL_MAGENTA);
            printf("Az auto adatai:\nStatusz: Nem aktiv\nRendszam: %s\n Tulajdonos: Jelenleg nincsen\nTipus: %s\nMuszaki ervenyes:%d.%d.%d\n",
                   adot_auto->rendszam, adot_auto->tipus, adot_auto->ervenyes.ev, adot_auto->ervenyes.honap,
                   adot_auto->ervenyes.nap);
            econio_textcolor(COL_RESET);
        }
        econio_textcolor(COL_CYAN);
        printf("Adatok modositasa (1)\n");
        econio_textcolor(COL_MAGENTA);
        printf("Auto torlese (2)\n");
        econio_textcolor(COL_BROWN);
        printf("Auta atruhazasa (3)\n");
        econio_textcolor(COL_YELLOW);
        printf("Visszalepes, uj rendszam bevitele (4)\n");
        econio_textcolor(COL_RED);
        printf("Kilepes (5)\n");
        econio_textcolor(COL_RESET);
        scanf(" %d", &valszto);
        switch (valszto) {
            case 5:
                *ugyfel_adat = ugyfel_lista;
                *auto_adat = auto_lista;
                return 3;
                break;
            case 1:
                auto_modosit(adot_auto, auto_lista);
                if (!auto_iras(auto_lista)){
                    econio_textcolor(COL_RED);
                    printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);}
                break;
            case 2:
                auto_torol(adot_auto, &auto_lista);
                if (!auto_iras(auto_lista)){
                    econio_textcolor(COL_RED);
                    printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);}
                valszto = 5;
                break;
            case 3:
                atruhaz_auto(&ugyfel_lista, adot_auto);
                u_iras = !ugyfel_iras(ugyfel_lista);
                a_iras = !auto_iras(adot_auto);
                if (u_iras && a_iras){
                    econio_textcolor(COL_RED);
                    printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);}
                break;
            case 4:
                *ugyfel_adat = ugyfel_lista;
                *auto_adat = auto_lista;
                return 0;
                break;
            default:
                printf("kerem a listabol valaszon");
                break;

        }
    } while (valszto != 5);
    *ugyfel_adat = ugyfel_lista;
    *auto_adat = auto_lista;
    return 0;

}


void a_kezel(gepjarmu **auto_adat, ugyfel **ugyfel_adat) {
    gepjarmu *autok = *auto_adat;
    ugyfel *ugyfelek = *ugyfel_adat;
    char *rendszam = NULL;
    int hoazada_valasz=0;
    int valszto=0;
    bool u_iras;
    bool a_iras;
    do {
        printf("kerem vigye be a rendszamot: ");
        rendszam = hosszu_sort_olvas();
        rendszam = strupr(rendszam);
        if (karakter_ellenoriz(rendszam)) {
            gepjarmu *kereset_auto = keres_rendszam_alapjan(rendszam, autok);
            if (kereset_auto == NULL) {
                do {
                    econio_textcolor(COL_MAGENTA);
                    printf("Hozza szeretne adni az alabbi rendszamot: %s a rendszerhez\n", rendszam);
                    econio_textcolor(COL_GREEN);
                    printf("igen (1)\n");
                    econio_textcolor(COL_RED);
                    printf("nem (0)\n");
                    econio_textcolor(COL_YELLOW);
                    printf("visszalépés a főmenübe (3)\n");
                    econio_textcolor(COL_RESET);
                    scanf(" %d", &hoazada_valasz);
                    switch (hoazada_valasz) {
                        case 1:
                            auto_hozzaad(&autok, rendszam, &ugyfelek);
                            u_iras = !ugyfel_iras(ugyfelek);
                            a_iras = !auto_iras(autok);
                            if (u_iras && a_iras) {
                                econio_textcolor(COL_RED);
                                printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                                econio_textcolor(COL_RESET);
                            }
                            break;
                        case 0:
                            free(rendszam);
                            break;
                        case 3:
                            free(rendszam);
                            valszto = 3;
                            break;
                        default:
                            printf("kerem a listabol valszol\n");
                    }
                } while (hoazada_valasz != 0 && hoazada_valasz != 1 && hoazada_valasz != 3);
            } else {
                valszto = meglevo_auto_kezel(&autok, &ugyfelek, kereset_auto);
                free(rendszam);
            }
        } else {
            econio_textcolor(COL_RED);
            printf("kerme ne legyen a bevit szovegben / es # karakter\n");
            econio_textcolor(COL_RESET);
            free(rendszam);
        }
        rendszam = NULL;
    } while (valszto != 3);
    *auto_adat = autok;
    *ugyfel_adat = ugyfelek;
}


void autok_szemely_mod(char regi[9], char uj[9], gepjarmu *autok) {
    for (gepjarmu *akt = autok; akt != NULL; akt = akt->kov) {
        if (strcmp(akt->szemely_szam, regi) == 0)
            strcpy(akt->szemely_szam, uj);
    }
    if (!auto_iras(autok)) {
        econio_textcolor(COL_RED);
        printf("valami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve");
        econio_textcolor(COL_RESET);
    }
}

void atok_torles_szemelyszam(char *szemely, gepjarmu **autok) {
    gepjarmu *elzo = NULL;
    gepjarmu *kovetkezo = NULL;
    gepjarmu *lista = *autok;
    for (gepjarmu *akt = lista; akt != NULL; akt = kovetkezo)
        if (strcmp(akt->szemely_szam, szemely) == 0) {
            javitas *lepte = NULL;
            for (javitas *aktualis = akt->munka; aktualis != NULL; aktualis = lepte) {
                lepte = aktualis->kov;
                free(aktualis->elvegzett_munka);
                free(aktualis);
            }
            if (elzo == NULL) {
                lista = akt->kov;
                kovetkezo = akt->kov;
                free(akt->rendszam);
                free(akt->tipus);
                free(akt);
            } else {
                kovetkezo = akt->kov;
                elzo->kov = kovetkezo;
                kovetkezo->elo = elzo;
                free(akt->rendszam);
                free(akt->tipus);
                free(akt);
            }
        } else {
            elzo = akt;
            kovetkezo = akt->kov;
        }
    *autok = lista;
    if (!auto_iras(lista)) {
        econio_textcolor(COL_RED);
        printf("\nvalami hibatortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
        econio_textcolor(COL_RESET);
    }
}

void auto_passzival(gepjarmu *lista, char *szemelyszam) {
    for (gepjarmu *akt = lista; akt != NULL; akt = akt->kov) {
        if (akt->akiv && strcmp(akt->szemely_szam, szemelyszam) == 0)
            akt->akiv = false;
    }
}

void autok_listaz_tulaj(gepjarmu *lista, char *szemelyszam) {
    econio_textcolor(COL_BROWN);
    for (gepjarmu *akt = lista; akt != NULL; akt = akt->kov) {
        if (akt->akiv && strcmp(akt->szemely_szam, szemelyszam) == 0)
            printf("Rendszam: %s Tulajdonos: %s Tipus: %s Muszaki ervenyes:%d.%d.%d\n",
                   akt->rendszam, akt->szemely_szam, akt->tipus, akt->ervenyes.ev,
                   akt->ervenyes.honap, akt->ervenyes.nap);
    }
    econio_textcolor(COL_RESET);
}

void osszes_autot_listaz(gepjarmu *lista) {
    printf("Az auto adatai:\n");
    for (gepjarmu *akt = lista; akt != NULL; akt = akt->kov)
        printf("Aktiv: %s Rendszam: %s Tulajdonos: %s Tipus: %s Muszaki ervenyes:%d.%d.%d\n",
               akt->akiv ? "igen" : "nem", akt->rendszam, akt->szemely_szam, akt->tipus, akt->ervenyes.ev,
               akt->ervenyes.honap, akt->ervenyes.nap);
    printf("Nyomj meg  '1'-st a folytatashoz.(+enter)\n");
    int beker=0;
    while (scanf(" %d",&beker)==1 && beker!=0)
    while (scanf(" %d",&beker)==1 && beker!=0)
        printf("Nyomj meg  '1'-st a folytatashoz.(+enter)\n");
}
