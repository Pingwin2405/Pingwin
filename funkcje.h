#ifndef PRM_PROJECT_TMP_FUNKCJE_H
#define PRM_PROJECT_TMP_FUNKCJE_H

#define ROZMIAR 21



struct Lista_rodzajow {
    char rodzaj[ROZMIAR];
    struct Lista_rodzajow *nast;
    struct Lista_bakterii *pierwszy_gatunek;
};
typedef struct Lista_rodzajow *ptr_rod;

/**lista jednokierunkowa, przechowuje wszystkie dodane bakterie, np. Lactococcus lactis */
struct Lista_bakterii {
    char bakteria[ROZMIAR];
    struct Lista_bakterii *B_nast;
};
typedef struct Lista_bakterii *ptr_bak;

enum menu {
    DODAJ_RODZAJ=1,
    WYSWIETL_RODZAJE=2,
    ZARAZ=3,
    DODAJ_BAKTERIE=4,
    WYSWIETL_BAKTERIE=5,
    USUN_RODZAJ=6,
    USUN_BAKTERIE=7,
    WYJSCIE = 8
};
/**ponumerowanie opcji menu*/
ptr_rod dodaj_rod(ptr_rod pierw);/**dodaje rodzaj*/
ptr_rod usun_rodzaj(ptr_rod pierw);/**usuwa rodzaj*/
ptr_rod zwolnij(ptr_rod pierw);
void wyswietl_rodzaje(ptr_rod pierw);/**wyswietla wszystkie rodzaje*/
unsigned int pusta(ptr_rod pierw);
void menu(ptr_rod pierw); //*wyswietlanie menu*/
ptr_bak usun_gat(ptr_rod pierw); //*usuwanie gatunku bakterii*/
void zapiszRodzaj(ptr_rod rodzaj); /**zapisywanie do pliku*/
unsigned int odczyt(char *kom, int *dane); 
void zapiszGatunek(ptr_rod rodzaj, ptr_bak bakteria);
void wyswietl_bakterie(ptr_rod pierw); /**wyswietla wszystkie gatunki*/
ptr_bak dodaj_bakterie(ptr_rod gener);/**dodaje gatunek*/

#endif //PRM_PROJECT_TMP_FUNKCJE_H
