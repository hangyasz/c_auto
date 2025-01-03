#include "legfontosabb.h"
#include "falj_kezel.h"
#include "fugveny.h"
#include "ugyfel_kezel.h"
#include "auto_kezel.h"
#include "szerviz_kezel.h"
#include "lejar.h"


int main(void) {

    ugyfel *adat_ugyfel= beolvas_ugyfel();
    gepjarmu *adat_auto= beolvas_auto();
    int muvelet=0;
    do {
        econio_clrscr();
        printf("belepes az alabi menupontokba az akabi betuel tortenik:\n");
        econio_gotoxy(10, 1);
        econio_textcolor(COL_YELLOW);
        printf("Ugyfelkezeles (1)\n");
        econio_gotoxy(10, 2);
        econio_textcolor(COL_BLUE);
        printf("Auto kezeles (2)\n");
        econio_gotoxy(10, 3);
        econio_textcolor(COL_GREEN);
        printf("Szerviz (3)\n");
        econio_gotoxy(10, 4);
        econio_textcolor(COL_MAGENTA);
        printf("Kozeli lejaratu autok (4)\n");
        econio_gotoxy(10, 5);
        econio_textcolor(COL_RED);
        printf("Lejart autok (5)\n");
        econio_gotoxy(10, 6);
        econio_textcolor(COL_LIGHTBLUE);
        printf("Oszes auto listazas (6)\n");
        econio_gotoxy(10, 7);
        econio_textcolor(COL_RESET);
        printf("kilepes (7)\n");
        econio_textcolor(COL_CYAN);
        scanf(" %d",&muvelet);
        econio_textcolor(COL_RESET);
        switch (muvelet) {
            case 1:
                u_kezel(&adat_ugyfel,&adat_auto);
                break;
            case 2:
                a_kezel(&adat_auto,&adat_ugyfel);
                break;
            case 3:
                sz_kezel(&adat_auto,&adat_ugyfel);
                break;
            case 4:
                kozeli_lejar(adat_auto,adat_ugyfel);
                break;
            case 5:
                lejart(adat_auto,adat_ugyfel);
                break;
            case 7:
                break;
            case 6:
                osszes_autot_listaz(adat_auto);
                break;
            default:
                break;
        }

    } while (muvelet!=7);

    felszabadit_ugyfel(adat_ugyfel);
    felszabadit_auto(adat_auto);

    return 0;
}
