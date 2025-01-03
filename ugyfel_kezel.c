#include "ugyfel_kezel.h"
#include "legfontosabb.h"
#include "auto_kezel.h"
#include "fugveny.h"
#include "falj_kezel.h"

void listaz_ugyfel(ugyfel *ugyfelek) {
    for (ugyfel *akt = ugyfelek; akt != NULL; akt = akt->kov)
        printf("%s %s %s +%lld %d\n", akt->szemely_szam, akt->nev, akt->email, akt->telefon, akt->autok);
}

ugyfel *u_keres(ugyfel *ugyfelek, char *szemely_szam) {
    for (ugyfel *akt = ugyfelek; akt != NULL; akt = akt->kov) {
        if (strcmp(akt->szemely_szam, szemely_szam) == 0)
            return akt;
    }
    return NULL;
}


void torol_ugyfel(ugyfel **ugyfelk, gepjarmu **autok) {
    char szemel_szam[9];
    printf("kerem a torolendo ugyfel szemelyszamat: ");
    scanf(" %8s", szemel_szam);
    ugyfel *akt = *ugyfelk;
    ugyfel *eleozo = NULL;
    for (; akt != NULL; akt = akt->kov) {
        if (strcmp(akt->szemely_szam, szemel_szam) == 0) {
            printf("az adot : az alabi adatokaugyfel ezeket az adatokat tartalmaza:\n");
            printf("%s %s %s +%lld %d\n", akt->szemely_szam, akt->nev, akt->email, akt->telefon, akt->autok);
            econio_textcolor(COL_MAGENTA);
            printf("biztos hogy torli?: igen(i) nem(bermilyen mas betu)");
            char valsz;
            scanf(" %c", &valsz);
            econio_textcolor(COL_RESET);
            valsz = tolower(valsz);
            if (valsz == 'i') {
                econio_textcolor(COL_BLUE);
                printf("szeretne e torlni az autokat is a felhasznalotol: igen(i) nem(bermilyen mas betu)\n");
                char valsz_auto;
                scanf(" %c", &valsz_auto);
                econio_textcolor(COL_RESET);
                if (valsz_auto == 'i')
                    atok_torles_szemelyszam(szemel_szam, &*autok);
                else
                    auto_passzival(*autok, szemel_szam);
                if (eleozo == NULL) {
                    *ugyfelk = akt->kov;
                    free(akt->nev);
                    free(akt->email);
                    free(akt);
                    return;
                } else {
                    eleozo->kov = akt->kov;
                    free(akt->nev);
                    free(akt->email);
                    free(akt);
                    return;
                }
            } else
                return;
        }
        eleozo = akt;
    }
    econio_textcolor(COL_MAGENTA);
    printf("nem talalhato ez:%s a szemelyszam", szemel_szam);
    econio_textcolor(COL_RESET);
}

void uj_u_hozzaad(ugyfel **ugyfelek, char *szemelysz) {
    ugyfel *akt;
    ugyfel *lista = *ugyfelek;
    if (lista == NULL) {
        ugyfel *uj = (ugyfel *) malloc(sizeof(ugyfel));
        uj->kov = NULL;
        strcpy(uj->szemely_szam, szemelysz);
        printf("keren az ugyfel nevet: ");
        char *nev = hosszu_sort_olvas();
        bool nev_eln = karakter_ellenoriz(nev);
        while (!nev_eln) {
            econio_textcolor(COL_RED);
            printf("kerem ne legyen a bevitt szovegben / es # karakter\n");
            printf("keren az ugyfel nevet: ");
            free(nev);
            nev = hosszu_sort_olvas();
            nev_eln = karakter_ellenoriz(nev);
            econio_textcolor(COL_RESET);
        }
        uj->nev = nev;
        printf("keren az ugyfel email cim: ");
        char *email = hosszu_sort_olvas();
        bool eamil_eln = !karakter_ellenoriz(email);
        bool email_kukac = !email_ellenoriz(email);
        while (eamil_eln || email_kukac) {
            econio_textcolor(COL_RED);
            if (!eamil_eln)
                printf("kerem ne legyen a bevitt szovegben / es # karakter\n");
            if (!email_kukac)
                printf("Az email cim helytelen formatumban lett megadva. pl valami@valami.valami\n");
            printf("keren az ugyfel eamil cim: ");
            free(email);
            email = hosszu_sort_olvas();
            eamil_eln = karakter_ellenoriz(email);
            econio_textcolor(COL_RESET);
        }
        uj->email = email;
        printf("kerem a telefon szamot: ");
        scanf(" %lld", &uj->telefon);
        uj->autok = 0;
        uj->kov = NULL;
        lista = uj;

    } else {
        for (akt = *ugyfelek; akt->kov != NULL; akt = akt->kov);
        ugyfel *uj = (ugyfel *) malloc(sizeof(ugyfel));
        uj->kov = NULL;
        strcpy(uj->szemely_szam, szemelysz);
        printf("keren az ugyfel nevet: ");
        char *nev = hosszu_sort_olvas();
        bool nev_eln = karakter_ellenoriz(nev);
        while (!nev_eln) {
            econio_textcolor(COL_RED);
            printf("kerem ne legyen a bevitt szovegben / es # karakter");
            printf("keren az ugyfel nevet: ");
            free(nev);
            nev = hosszu_sort_olvas();
            nev_eln = karakter_ellenoriz(nev);
            econio_textcolor(COL_RESET);
        }
        uj->nev = nev;
        printf("keren az ugyfel email: ");
        char *email = hosszu_sort_olvas();
        bool eamil_eln = !karakter_ellenoriz(email);
        bool email_kukac = !email_ellenoriz(email);
        while (eamil_eln && email_kukac) {
            econio_textcolor(COL_RED);
            if (eamil_eln)
                printf("kerem ne legyen a bevitt szovegben / es # karakter");
            if (email_kukac)
                printf("Az email cim helytelen formatumban lett megadva. pl valami@valami.valami\n");
            printf("keren az ugyfel eamil: ");
            free(email);
            email = hosszu_sort_olvas();
            eamil_eln = karakter_ellenoriz(email);
            econio_textcolor(COL_RESET);
        }
        uj->email = email;
        printf("kerem a telefon szamot: ");
        scanf(" %lld", &uj->telefon);
        uj->autok = 0;
        akt->kov = uj;
    }
    *ugyfelek = lista;

}


void uj_ugyfel(ugyfel **ugyfelek_lista, gepjarmu **auto_lista) {
    ugyfel *ugyfelek = *ugyfelek_lista;
    char szemely_szam[9];
    char valasz = 'e';
    do {
        printf("keren vigyebe az uj ugyfel szemely szamat: ");
        scanf(" %8s", szemely_szam);
        ugyfel *uj = u_keres(ugyfelek, szemely_szam);
        if (uj != NULL) {
            econio_textcolor(COL_MAGENTA);
            printf("az adot szemely mar letezik: az alabi adatokat tartalmaza:\n");
            printf("%s %s %s +%lld %d\n", uj->szemely_szam, uj->nev, uj->email, uj->telefon, uj->autok);
            econio_textcolor(COL_RESET);
            do {
                printf("kerem valaszol az alabi menupontokbol:\n");
                econio_textcolor(COL_BLUE);
                printf("meglevo ugyfel torlese(t)\n");
                econio_textcolor(COL_GREEN);
                printf("szemelyszam modosit(m)\n");
                econio_textcolor(COL_RED);
                printf("megsem szeretnem ezt csinalni(e)\n");
                econio_textcolor(COL_RESET);
                scanf(" %c", &valasz);
                valasz = tolower(valasz);
                switch (valasz) {
                    case 't':
                        torol_ugyfel(&ugyfelek, &*auto_lista);
                        break;
                    case 'm':
                        break;
                    case 'e':
                        return;
                    default:
                        printf("Nincen ilyen kerem valaszon a listabol");
                        break;
                }
            } while (valasz != 'e' && valasz != 'm');
        }
    } while (valasz != 'e');
    uj_u_hozzaad(&ugyfelek, szemely_szam);
    *ugyfelek_lista = ugyfelek;
}

void kezel_ugyfel(ugyfel **ugyfelek, gepjarmu *autok) {
    printf("keren vigyebe az uj ugyfel szemely szamat: ");
    char szemely_szam[9];
    scanf(" %8s", szemely_szam);
    ugyfel *ugyfel_kereset = u_keres(*ugyfelek, szemely_szam);
    int valasz;
    if (ugyfel_kereset == NULL) {
        econio_textcolor(COL_MAGENTA);
        printf("az ugyfelmeg nem szerepel a rendszerbe szertne felveni? igen(1) nem(2)");
        scanf(" %d", &valasz);
        econio_textcolor(COL_RESET);
        valasz = tolower(valasz);
        if (valasz == 1) {
            uj_u_hozzaad(&*ugyfelek, szemely_szam);
            return;
        } else
            return;
    }
    do {
        char regi_szem[9];
        printf("jelnlegi adatok:\n");
        printf("%s %s %s +%lld %d\n", ugyfel_kereset->szemely_szam, ugyfel_kereset->nev, ugyfel_kereset->email,
               ugyfel_kereset->telefon, ugyfel_kereset->autok);
        econio_textcolor(COL_BROWN);
        printf("Autok listazasa (1)\n");
        econio_textcolor(COL_RESET);
        printf("\nmodositas:\n");
        econio_textcolor(COL_BLUE);
        printf("nev(2)\n");
        econio_textcolor(COL_GREEN);
        printf("email(3)\n");
        econio_textcolor(COL_MAGENTA);
        printf("telefonszam(4)\n");
        econio_textcolor(COL_RED);
        printf("szemelyszam(5)\n");
        econio_textcolor(COL_BROWN);
        econio_textcolor(COL_CYAN);
        printf("befejez(6)\n");
        econio_textcolor(COL_YELLOW);
        printf("Mit szeretne tenni?  ");
        econio_textcolor(COL_RESET);
        scanf(" %d", &valasz);
        switch (valasz) {
            case 1:
                autok_listaz_tulaj(autok, szemely_szam);
                break;
            case 2:
                printf("az uj nev: ");
                char *nev = hosszu_sort_olvas();
                bool nev_eln = karakter_ellenoriz(nev);
                while (!nev_eln) {
                    econio_textcolor(COL_RED);
                    printf("kerem ne legyen a bevitt szovegben / es # karakter\n");
                    printf("keren az ugyfel nevet: ");
                    free(nev);
                    nev = hosszu_sort_olvas();
                    nev_eln = karakter_ellenoriz(nev);
                    econio_textcolor(COL_RESET);
                }
                free(ugyfel_kereset->nev);
                ugyfel_kereset->nev = nev;
                break;
            case 3:
                printf("az uj email cim: ");
                char *email = hosszu_sort_olvas();
                bool eamil_eln = karakter_ellenoriz(email);
                bool email_kukac = email_ellenoriz(email);
                while (!eamil_eln && !email_kukac) {
                    econio_textcolor(COL_RED);
                    if (!eamil_eln)
                        printf("kerem ne legyen a bevitt szovegben / es # karakter\n");
                    if (!email_kukac)
                        printf("Az email cim helytelen formatumban lett megadva. pl valami@valami.valami\n");
                    printf("keren az ugyfel eamil cim: ");
                    free(email);
                    email = hosszu_sort_olvas();
                    eamil_eln = karakter_ellenoriz(email);
                    econio_textcolor(COL_RESET);
                }
                free(ugyfel_kereset->email);
                ugyfel_kereset->email = email;
                break;
            case 5:
                printf("az uj szemelyszam: ");
                strcpy(regi_szem, ugyfel_kereset->szemely_szam);
                scanf(" %8s", ugyfel_kereset->szemely_szam);
                autok_szemely_mod(regi_szem, ugyfel_kereset->szemely_szam, autok);
                break;
            case 4:
                printf("az uj telefon: ");
                scanf("%lld", &ugyfel_kereset->telefon);
            case 6:
                break;
            default:
                printf("Nincen ilyen kerem valaszon a listabol");
                break;
        }
    } while (valasz != 6);
}

void u_kezel(ugyfel **ugyfelek, gepjarmu **autok) {
    printf("Ugyfel kezelses\n");
    int beolvas;
    ugyfel *ugyfelek_adat = *ugyfelek;
    gepjarmu *autok_adat = *autok;
    bool u_iras;
    bool a_iras;
    do {
        printf("belepes az alabi menupontokba az akabi betukel tortenik:\n");

        printf("uj ugyfel felvetele(1)\n");
        econio_textcolor(COL_BLUE);
        printf("Meglevo ugyfell kezel(2)\n");
        econio_textcolor(COL_GREEN);
        printf("Ugyfelek listazasa(3)\n");
        econio_textcolor(COL_MAGENTA);
        printf("Ugyfel torlese(4)\n");
        econio_textcolor(COL_RED);
        printf("Kilepes(5)\n");
        econio_textcolor(COL_RESET);
        scanf(" %d", &beolvas);
        switch (beolvas) {
            case 1:
                uj_ugyfel(&ugyfelek_adat, &autok_adat);
                u_iras = !ugyfel_iras(ugyfelek_adat);
                a_iras = !auto_iras(autok_adat);
                if (u_iras && a_iras) {
                    econio_textcolor(COL_RED);
                    printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            case 2:
                kezel_ugyfel(&ugyfelek_adat, autok_adat);
                u_iras = !ugyfel_iras(ugyfelek_adat);
                a_iras = !auto_iras(autok_adat);
                if (u_iras && a_iras) {
                    econio_textcolor(COL_RED);
                    printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            case 3:
               listaz_ugyfel(ugyfelek_adat);
                break;
            case 4:
                torol_ugyfel(&ugyfelek_adat, &autok_adat);
                u_iras = !ugyfel_iras(ugyfelek_adat);
                a_iras = !auto_iras(autok_adat);
                if (u_iras && a_iras) {
                    econio_textcolor(COL_RED);
                    printf("\nValami hiba tortent inditsa ujara programot a kert muvelet nem lett elmentve\n");
                    econio_textcolor(COL_RESET);
                }
                break;
            case 5:
                break;
            default:
                printf("Nincs ilyen lehetoség a listaban\n");
                break;
        }
    } while (beolvas != 5);
    *ugyfelek = ugyfelek_adat;
    *autok = autok_adat;
}
