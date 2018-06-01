#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"

int main(void) {
    ptr_rod pierw = NULL;
    short wybor;
    short dziala = 1;
    int tymcz;

    while (dziala) {
        menu(pierw);

        scanf("%hi", &wybor);

        switch (wybor) {
            case DODAJ_RODZAJ:
                pierw = dodaj_rod(pierw);
                break;
            case WYSWIETL_BAKTERIE:
                wyswietl_bakterie(pierw);
                break;
            case WYSWIETL_RODZAJE:
                wyswietl_rodzaje(pierw);
                break;
            case DODAJ_BAKTERIE:
                dodaj_bakterie(pierw);
                break;
            case ZARAZ:
                printf("Nie badz taki/a zlosliwy/a\n");
                break;
            case USUN_RODZAJ:
               // if (odczyt("Ktory rodzaj chcesz usunac? ", &tymcz))
                   pierw = usun_rodzaj(pierw);
                break;
            case USUN_BAKTERIE:
                break;
            case WYJSCIE:
                pierw = zwolnij(pierw);
                dziala = 0;
                break;
            default:
                printf("Prosze poprawnie wybrac opcje\n");
                break;
        }
    }
    return 0;
}

