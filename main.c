
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROZMIAR 21

struct Bakteria                       /**definicja typu bakteria*/
{
        char gatunek[ROZMIAR];
};
typedef struct Bakteria bakteria;

struct L_rodzaj
   {
   char rodzaj [ROZMIAR];
   bakteria gatunki_rodzaju [15];
   struct L_rodzaj *nast;
   };

typedef struct L_rodzaj * ptr_rod;

struct L_Bak
{                                          /**lista jednokierunkowa, przechowuje wszystkie dodane bakterie, np. Lactococcus lactis
                                                        */
    bakteria Bakteria;
    struct L_Bak *B_nast;
};

typedef struct L_Bak* ptr_bak;

ptr_rod dodaj_rod(ptr_rod pierw, char gener);//dodaje rodzaj

ptr_rod usun_rod(ptr_rod pierw, char gener);//usuwa rodzaj
ptr_rod zwolnij(ptr_rod pierw);
void wyswietl_rod(ptr_rod pierw);//wyswietla wszystkie rodzaje
unsigned int pusta(ptr_rod pierw);
void menu(ptr_rod pierw);
char odczytM(void);
unsigned int odczyt(char * kom, int * dane);

int main(void)
	{

	ptr_rod pierw = NULL;
	char wybor;
	int tymcz;
	for(;;)
		{
		menu(pierw);
		wybor=odczytM();
		switch(wybor)
			 {
			 case 'a': //dodaje rodzaj
				if (odczyt("\nPodaj nazwe rodzaju:", &tymcz ))
					 pierw=dodaj_rod(pierw,tymcz );
			    break;
             case 'b'://dodaje bakterie
                 if (odczyt("\nPodaj nazwe bakterii:", &tymcz ))
					 pierw=dodaj_rod(pierw,tymcz);
                break;
			 case 'c': ///wyswietla wszystkie rodzaje
			    wyswietl_rod(pierw);
			    break;
             case 'd':
                break;
             case 'e':
                 printf("Nie badz taki/a zlosliwy/a\n");
                break;
			 case 'f': //usuwa rodzaj
				if (odczyt("Ktory rodzaj chcesz usunac? ", &tymcz ))
					 pierw=usun_rod(pierw,tymcz);
				break;
             case 'g':
                break;
			 case 'h':
				pierw=zwolnij(pierw);
			    exit(0);
			    break;
			 default:
			    printf("Prosze poprawnie wybrac opcje\n");
			 }
		}
	return 0;
	}

ptr_rod dodaj_rod(ptr_rod pierw, char gener)
   {
   ptr_rod nowy= (ptr_rod)malloc( sizeof(struct L_rodzaj) );
   if(nowy==NULL)
      {
      fputs("Nie ma miejsca na nowy rodzaj",stderr);
      exit(1);
      }

   strcpy(nowy->rodzaj, gener);
   nowy->nast = pierw;
   return nowy;
   }

void wyswietl_rod(ptr_rod pierw)
   {
	ptr_rod akt=pierw;
	unsigned ktory_rod=1;
	do
    	{
		printf("Rodzaj %d: %s\n",ktory_rod++, akt->rodzaj );
		akt = akt->nast;
    	} while(akt != NULL);
   }

ptr_rod usun_rod(ptr_rod pierw, char gener)
   {
	ptr_rod akt=pierw, poprz=NULL;
	do
		{
        if( akt->rodzaj==gener)
        	{
        	if(akt==pierw) pierw = akt->nast;
        	else poprz->nast = akt->nast;
        	free(akt);
        	return pierw;
        	}
        poprz = akt;
        akt = akt->nast;
		} while(akt != NULL);
	printf("Nie ma takiego rodzaju\n");
	return pierw;
   }

ptr_rod zwolnij(ptr_rod pierw)
   {
   ptr_rod akt=pierw, tymcz;
   do
      {
      tymcz = akt;
      akt = akt->nast;
      free(tymcz);
      } while(akt != NULL);
   return NULL;
   }

unsigned int pusta(ptr_rod pierw)
	{
	if (pierw == NULL) return 1;
	else return 0;
	}

void menu(ptr_rod pierw)
	{
	  printf("Wybierz opcje:\n a-dodaj rodzaj bakterii\n b-wyswietl wszystkie rodzaje bakterii\n  c-zaraz bakteriami nielubianego kolege\n ");
	 if (!pusta(pierw))
	 	 {
		 printf("d-dodaj bakterie\n e-wyswietl wszystkie bakterie\n f-usun rodzaj bakterii\n g-usun bakterie\n ");

		 }
     printf("h- wyjscie z programu\n");

	}

char odczytM(void)
	{
	char c, wybor[2];
	fgets(wybor,2,stdin);
	while((c=getchar())!='\n');
	return wybor[0];
	}

unsigned int odczyt(char * kom, int * dane)
	{
	char bufor[ROZMIAR];
	int konw;
	printf("%s",kom);
	fgets(bufor,ROZMIAR,stdin);
	konw=sscanf(bufor,"%d", dane);
	if (konw==EOF) return 0;
	else return 1;
	}
