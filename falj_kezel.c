#include "legfontosabb.h"
#include "falj_kezel.h"
#include "fugveny.h"

ugyfel *beolvas_ugyfel(void){
    ugyfel *ugyfelek=NULL;
    ugyfel *utolso;
    FILE *ugyfel_f=fopen("ugyfel.txt", "r");
    if(ugyfel_f==NULL)
        return ugyfelek;
    char szemely_szam[9];
    long long int tel_szam;
    int auto_szam;
    while (fscanf(ugyfel_f,"%8s ",szemely_szam)==1){
        char *nev=NULL;
        char *email=NULL;
        char akt;
        while (fscanf(ugyfel_f,"%c",&akt)==1 && akt!='/'){
            nev= hozzafuz(nev, akt);
        }
        while (fscanf(ugyfel_f,"%c",&akt)==1 && akt!='/'){
            email= hozzafuz(email, akt);
        }
        fscanf(ugyfel_f,"%lld %d",&tel_szam,&auto_szam);
        ugyfel *seged=(ugyfel *) malloc(sizeof(ugyfel));
        if(ugyfelek == NULL){
            ugyfelek=seged;
        seged->kov=NULL;
        seged->email=email;
        seged->nev=nev;
        seged->telefon=tel_szam;
        seged->autok=auto_szam;
        strcpy(seged->szemely_szam,szemely_szam);
            utolso=ugyfelek;
        } else{
            utolso->kov=seged;
            seged->kov=NULL;
            seged->email=email;
            seged->nev=nev;
            seged->telefon=tel_szam;
            seged->autok=auto_szam;
            strcpy(seged->szemely_szam,szemely_szam);
            utolso=seged;
        }
        }
    fclose(ugyfel_f);
    return ugyfelek;
}



gepjarmu *beolvas_auto(void){
    gepjarmu *autok=NULL;
    FILE *auto_f=fopen("auto.txt", "r");
    if(auto_f==NULL)
        return NULL;
    char tulaj[9];
    int bool_olvas;
    while (fscanf(auto_f,"%d %8s /",&bool_olvas,tulaj)==2){
        datum muszaki;
        datum munkaidopnt;
        bool akit;
        if(bool_olvas==1)
            akit=true;
        else
            akit=false;
        int arr;
        float gari;
        char *rendszam=NULL;
        char *tipus=NULL;
        char akt;
        javitas *javitasok=NULL;
        char *javitas_munka=NULL;
        while (fscanf(auto_f,"%c",&akt)==1 && akt!='/'){
            rendszam= hozzafuz(rendszam, akt);
            }
        while (fscanf(auto_f,"%c",&akt)==1 && akt!='/'){
            tipus= hozzafuz(tipus, akt);
        }
        fscanf(auto_f,"%d.%d.%d/",&muszaki.ev,&muszaki.honap,&muszaki.nap);
        while (fscanf(auto_f,"%c",&akt)==1 && akt!='\n'){
            javitas_munka=NULL;
        while (fscanf(auto_f,"%c",&akt)==1 && akt!='#'){
            javitas_munka= hozzafuz(javitas_munka, akt);
        }
        fscanf(auto_f,"%d/%d.%d.%d/%f/",&arr,&munkaidopnt.ev,&munkaidopnt.honap,&munkaidopnt.nap,&gari);
            javitasok= lancol_javitas(javitasok,javitas_munka,arr,munkaidopnt,gari);
        }
        autok= lancol_autok(autok, tulaj, rendszam, tipus, muszaki, javitasok, akit);
    }

    fclose(auto_f);
    return autok;
}


bool auto_iras(gepjarmu *adat){
    bool siker=false;
    FILE *auto_f=fopen("auto.txt", "w");
    if(auto_f==NULL){
        return siker;
    }
    if(adat==NULL){
        fclose(auto_f);
        return true;
    }
    gepjarmu *leptet;
    for(leptet=adat;leptet!=NULL;leptet=leptet->kov){
        fprintf(auto_f, "%d %s /%s/%s/%d.%d.%d/", leptet->akiv, leptet->szemely_szam, leptet->rendszam, leptet->tipus, leptet->ervenyes.ev, leptet->ervenyes.honap, leptet->ervenyes.nap);
        javitas *leptett_jav;
        for(leptett_jav=leptet->munka;leptett_jav!=NULL;leptett_jav=leptett_jav->kov){
            fprintf(auto_f, " %s#%d/%d.%d.%d/%g/", leptett_jav->elvegzett_munka, leptett_jav->ara, leptett_jav->idopont.ev, leptett_jav->idopont.honap, leptett_jav->idopont.nap, leptett_jav->garancia);
        }
        fprintf(auto_f,"\n");
        siker=true;
    }
    fclose(auto_f);
    return siker;

}

bool ugyfel_iras(ugyfel *adat){
    bool siker=false;
    FILE *ugyfel_f=fopen("ugyfel.txt", "w");
    if(ugyfel_f==NULL){
        return siker;
    }
    if (adat==NULL){
        fclose(ugyfel_f);
        return true;
    }
    ugyfel *leptet;
    for (leptet=adat;leptet!=NULL;leptet=leptet->kov){
        fprintf(ugyfel_f,"%s %s/%s/%lld %d\n",leptet->szemely_szam,leptet->nev,leptet->email,leptet->telefon,leptet->autok);
        siker=true;
    }
    fclose(ugyfel_f);
    return siker;
}

