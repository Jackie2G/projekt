//dodajemy headery
#include <stdio.h>
#include "./status_gry.h"
#include "./funkcjonalnosc.h"

//funkcja umozliwia zmiane ruchu gracza

void zmiana_tury(informacje *gra){
  if (gra -> gracz == GRACZ_X){
    gra -> gracz = GRACZ_O;
  }
  else if (gra -> gracz == GRACZ_O){
    gra -> gracz = GRACZ_X;
  }
}

//funkcja do sprawdzenia ktory gracz wygral
int kto_wygral(informacje *gra, int gracz){
  //tworzymy liczniki do sprawdzenia planszy w poziomie, pionie i po przekatnych
  int licznik_wierszy = 0;
  int licznik_kolumn = 0;
  int licznik_przekatna1 = 0;
  int licznik_przekatna2 = 0;
  for (int i = 0; i < N; ++i){
    for (int j = 0; j < N; ++j){
      if (gra -> plansza[i * N + j] == gracz){
        licznik_wierszy++;
      }
      if (gra -> plansza[j * N  + i] == gracz){
        licznik_kolumn++;
      }
    }
    if (licznik_wierszy >= N || licznik_kolumn >= N){
      return 1;
    }
    licznik_wierszy = 0;
    licznik_kolumn = 0;
    if (gra -> plansza[i * N + i] == gracz){
      licznik_przekatna1++;
    }
    if (gra -> plansza[i * N + N - i - 1] == gracz){
      licznik_przekatna2++;
    }
  }
  return licznik_przekatna1 >= N || licznik_przekatna2 >= N;
}

//funkcja liczaca wyplenione komorki
int licznik_komorek(const int *plansza, int komorka){
  int licznik = 0;
  for (int i = 0; i < N * N; ++i){
    if (plansza[i] == komorka){
      licznik++;
    }
  }
  return licznik;
}

//sprawdzenie czy gra sie skonczyla
void sprawdz_koniec_gry(informacje *gra){
  if (kto_wygral(gra, GRACZ_X)){
    gra -> status = GRACZ_X_WYGRYWA;
  }
  else if (kto_wygral(gra, GRACZ_O)){
    gra -> status = GRACZ_O_WYGRYWA;
  }
  else if (licznik_komorek(gra -> plansza, PUSTE) == 0){
    gra -> status = REMIS;
  }
}

//funkcja ustala ktory gracz wykonuje ture
void tura_gracza(informacje *gra, int wiersz, int kolumna){
  if (gra -> plansza[wiersz * N + kolumna] == PUSTE){
    gra -> plansza[wiersz * N + kolumna] = gra -> gracz;
    zmiana_tury(gra);
    sprawdz_koniec_gry(gra);
  }
}

//funkcja resetujaca gre do pierwotnych ustawien

void resetuj(informacje *gra){
  gra -> gracz = GRACZ_X;
  gra -> status = GRA_TRWA;
  for (int i = 0; i < N * N; ++i){
    gra -> plansza[i] = PUSTE;
  }
}

//funkcja ktora bedzie sie wywolywac kiedy nacisniemy myszka na wybrane pole
void nacisnij_pole(informacje *gra, int wiersz, int kolumna){
  if (gra->status == GRA_TRWA){
     tura_gracza(gra, wiersz, kolumna);
   }
  else{
    resetuj(gra);
  }
}
