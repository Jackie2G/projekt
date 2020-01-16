#ifndef STATUS_GRY_H_
#define STATUS_GRY_H_

/*definiujemy ilosc wierszy i kolumn, wysokosc, szerokosc okna
 oraz wysokosc i szerokosc pol */

#define N 3
#define SZEROKOSC 640.0
#define WYSOKOSC 480.0
#define SZEROKOSC_KOMORKI (SZEROKOSC / N)
#define WYSOKOSC_KOMORKI (WYSOKOSC / N)

//definiujemy graczy

#define PUSTE 0
#define GRACZ_X 1
#define GRACZ_O 2

//definiumey status gry

#define GRA_TRWA 0
#define GRACZ_X_WYGRYWA 1
#define GRACZ_O_WYGRYWA 2
#define REMIS 3
#define WYJSCIE 4

//tworzymy strukture przechowujaca podstawowe informacje dotyczace gry

typedef struct{
  int plansza[N * N];
  int gracz;
  int status;
}informacje;

#endif
