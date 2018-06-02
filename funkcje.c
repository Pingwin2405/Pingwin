#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funkcje.h"

//ptr_rod pierw, char gener
ptr_rod dodaj_rod(ptr_rod pierw) {
    char nazwa[ROZMIAR];
    printf("Podaj nazwe nowego rodzaju\n");
    scanf("%s", &nazwa);

    ptr_rod nowy = (ptr_rod) malloc(sizeof(struct Lista_rodzajow));
    if (nowy == NULL) {
        fputs("Nie ma miejsca na nowy rodzaj", stderr);
        exit(1);
    }
    strcpy(nowy->rodzaj, nazwa);

    nowy->nast = pierw;
    nowy->pierwszy_gatunek = NULL;
    //zapiszRodzaj(nowy);
    return nowy;
}

void zapiszRodzaj(ptr_rod rodzaj) {
    FILE *plik = fopen("plik.txt", "a+");
    fwrite(rodzaj, sizeof(rodzaj), 1, plik);
    fclose(plik);
}

void zapiszGatunek(ptr_rod rodzaj, ptr_bak bakteria) {
    FILE *plik = fopen("plik.txt", "r+");
    fwrite(rodzaj, sizeof(struct Lista_bakterii), 1, plik);
    fclose(plik);
}

void wyswietl_rodzaje(ptr_rod pierw) {
    ptr_rod akt = pierw;
    unsigned ktory_rod = 1;
    do {
        printf("Rodzaj %d: %s\n", ktory_rod++, akt->rodzaj);
        akt = akt->nast;
    } while (akt != NULL);
}

//ptr_rod usun_rodzaj(ptr_rod pierw){}




ptr_rod usun_rodzaj(ptr_rod pierw) {
    ptr_rod akt = pierw, poprz = NULL;
    char gener[ROZMIAR];
    printf("Ktory rodzaj chcesz usunac?\n");
    scanf("%s", &gener);

//    while(akt->rodzaj)

    do {
        if (!strcmp(akt->rodzaj, gener)) {
            if (akt == pierw) pierw = akt->nast;
            else poprz->nast = akt->nast;
            free(akt);
            return pierw;
        }
        poprz = akt;
        akt = akt->nast;
    } while (akt != NULL);
    if (NULL == akt)
        printf("Nie ma takiego rodzaju\n");
    return pierw;
}

ptr_rod zwolnij(ptr_rod pierw) {
    ptr_rod akt = pierw, tymcz;
    do {
        tymcz = akt;
        akt = akt->nast;
        free(tymcz);
    } while (akt != NULL);
    return NULL;
}

unsigned int pusta(ptr_rod pierw) {
    if (pierw == NULL) return 1;
    else return 0;
}

void menu(ptr_rod pierw) {
    printf("Wybierz opcje:\n 1-dodaj rodzaj bakterii\n 2-wyswietl wszystkie rodzaje bakterii\n 3-zaraz bakteriami nielubianego kolege\n ");
    if (!pusta(pierw)) {
        printf("4-dodaj bakterie\n 5-wyswietl wszystkie bakterie\n 6-usun rodzaj bakterii\n 7-usun bakterie\n ");

    }
    printf("8- wyjscie z programu\n");
}

unsigned int odczyt(char *kom, int *dane) {
    char bufor[ROZMIAR];
    int konw;
    printf("%s", kom);
    fgets(bufor, ROZMIAR, stdin);
    konw = sscanf(bufor, "%d", dane);
    if (konw == EOF) return 0;
    else return 1;
}


void wyswietl_bakterie(ptr_rod pierw) {

    ptr_rod akt = pierw;
    unsigned ktory_rod = 1;
    while (NULL != akt) {
        {
            printf("Rodzaj %d: %s\n", ktory_rod++, akt->rodzaj);
            ptr_bak aktualny_gatunek = akt->pierwszy_gatunek;
            printf("Gatunki:\n");
            while (NULL != aktualny_gatunek) {
                printf("%s\n", aktualny_gatunek->bakteria);
                aktualny_gatunek = aktualny_gatunek->B_nast;
            }
            akt = akt->nast;
        }

    }
}

ptr_bak dodaj_bakterie(ptr_rod gener) {
    char nazwa_rodzaju[ROZMIAR];
    ptr_rod aktRodzaj = gener;
    printf("Podaj nazwe rodzaju, do ktorego nalezy nowa bakteria\n");
    scanf("%s", &nazwa_rodzaju);


    while (NULL != aktRodzaj) {
        if (!strcmp(aktRodzaj->rodzaj, nazwa_rodzaju)) {
            char nazwa_bakterii[ROZMIAR];
            printf("Podaj nazwe nowego gatunku\n");
            scanf("%s", &nazwa_bakterii);

            ptr_bak nowy_gatunek = (ptr_bak) malloc(sizeof(struct Lista_bakterii));
            if (nowy_gatunek == NULL) {
                fputs("Nie ma miejsca na nowy rodzaj", stderr);
                exit(1);
            }
            strcpy(nowy_gatunek->bakteria, nazwa_bakterii);
            ptr_bak tmp = aktRodzaj->pierwszy_gatunek;

            if (NULL == aktRodzaj->pierwszy_gatunek) {
                aktRodzaj->pierwszy_gatunek = nowy_gatunek;
                return tmp;
            }
            while (NULL != tmp->B_nast) {
                tmp = tmp->B_nast;
            }

            //tutaj mamy w tmp element, którego nastepny jest nulem
            tmp->B_nast = nowy_gatunek;
            nowy_gatunek->B_nast=NULL;

            return nowy_gatunek;
        }
        aktRodzaj = aktRodzaj->nast;
    }

    printf("Nie ma takiego rodzaju\n");
    return NULL;
}


ptr_bak usun_gat(ptr_rod pierw) {
    ptr_rod akt = pierw;
    ptr_bak obecna, nastepna;
    char gener[ROZMIAR], gatunek[ROZMIAR];
    printf("Z ktorego rodzaju chcesz usunac gatunek?\n");
    scanf("%s", &gener);

    while (strcmp(akt->rodzaj, gener)) {
        if (NULL == akt) {
            printf("Nie ma takiego rodzaju\n");
            return NULL;
        }
        akt = akt->nast;
    }

    obecna = akt->pierwszy_gatunek;
    nastepna = obecna->B_nast;
    if (NULL == obecna) {
        printf("Nie ma zadnej bakterii w tym rodzaju!\n");
        return NULL;
    }
    printf("Ktory gatunek chcesz usunac?\n");
    scanf("%s", &gatunek);
    if (!strcmp(gatunek, obecna->bakteria)) {
        akt->pierwszy_gatunek = obecna->B_nast;
        free(obecna);
        return NULL;
    }

    while (NULL != obecna->B_nast && strcmp(obecna->B_nast->bakteria, gatunek)) {
        nastepna = nastepna->B_nast;
        obecna = obecna->B_nast;
    }
    if(NULL==obecna->B_nast){
        printf("Nie ma takiego gatunku\n");
        return NULL;
    }
    obecna->B_nast = nastepna->B_nast;
    free(nastepna);

    return NULL;
}






