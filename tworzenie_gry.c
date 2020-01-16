//dodajemy biblioteki
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

//dodajemy headery
#include "./status_gry.h"
#include "./tworzenie_gry.h"

//ustalamy kolory poszczegolnych elementow
const SDL_Color KOLOR_PLANSZY = {.r = 255, .g = 255, .b = 255}; //czarny
const SDL_Color KOLOR_GRACZ_X = {.r = 255, .g = 50, .b = 50}; //czerwony
const SDL_Color KOLOR_GRACZ_O = {.r = 50, .g = 100, .b = 255}; //niebieski
const SDL_Color KOLOR_REMISU = {.r = 100, .g = 100, .b = 100}; //szary

//tworzymy siatke ktora pozniej bedziemy wypelniac kolkiem lub krzyzykiem
void stworz_plansze(SDL_Renderer *renderer, const SDL_Color *kolor){
	SDL_SetRenderDrawColor(renderer, kolor -> r, kolor -> g, kolor -> b, 255);

	for (int i = 1; i < N; ++i){
		//tworzymy pionowe linie
		SDL_RenderDrawLine(renderer, i * SZEROKOSC_KOMORKI, 0, i * SZEROKOSC_KOMORKI, WYSOKOSC);
		//tworzymy poziome linie
		SDL_RenderDrawLine(renderer, 0, i * WYSOKOSC_KOMORKI, SZEROKOSC, i * WYSOKOSC_KOMORKI);
	}
}

//funkcja umozliwi nam tworzenie X na planszy
void narysuj_x(SDL_Renderer *renderer, int wiersz, int kolumna, const SDL_Color *kolor){

	/* ponizsze zmienne tworzymy aby znalezc wierzcholki kwadratu, ktorego
	dlugosc boku jest 2 razy mniejsza od pola naszej kratki, dzieki temu
	bedziemy mogli narysowac ukosne linie ktore zbuduja X */
	const float kwadracik = fmin(SZEROKOSC_KOMORKI, WYSOKOSC_KOMORKI) * 0.25;
	const float srodek_x = SZEROKOSC_KOMORKI * 0.5 + kolumna * SZEROKOSC_KOMORKI;
	const float srodek_y = WYSOKOSC_KOMORKI * 0.5 + wiersz * WYSOKOSC_KOMORKI;

	//rysujemy ukosnia linie
	thickLineRGBA(renderer, srodek_x - kwadracik, srodek_y - kwadracik,
		      srodek_x + kwadracik, srodek_y + kwadracik, 10,
		      kolor -> r, kolor -> g, kolor -> b, 255);
	//rysujemy druga ukosna linie dzieki ktorej powstanie X
	thickLineRGBA(renderer, srodek_x + kwadracik, srodek_y - kwadracik,
                      srodek_x - kwadracik, srodek_y + kwadracik, 10,
                      kolor -> r, kolor -> g, kolor -> b, 255);
}

//funkcja umozliwi nam tworzenie O na planszy
void narysuj_o(SDL_Renderer *renderer, int wiersz, int kolumna, const SDL_Color *kolor){

	/* wykorzystujemy podobna zasade jak przy tworzeniu X */
	const float kwadracik = fmin(SZEROKOSC_KOMORKI, WYSOKOSC_KOMORKI) * 0.25;
  const float srodek_x = SZEROKOSC_KOMORKI * 0.5 + kolumna * SZEROKOSC_KOMORKI;
	const float srodek_y = WYSOKOSC_KOMORKI * 0.5 + wiersz * WYSOKOSC_KOMORKI;

	//rysujemy wypelniony niebieski okrag
	filledCircleRGBA(renderer, srodek_x, srodek_y, kwadracik + 5,
			 kolor -> r, kolor -> g, kolor -> b, 255);
	//rysujemy mniejszy wypelniony na czarno okrag aby uzyskac pozadany efekt
  filledCircleRGBA(renderer, srodek_x, srodek_y, kwadracik -5,
                   0, 0, 0, 255);
}

//wypelniamy plansze X albo O w zaleznosci od ruchu gracza
void wypelnij_plansze(SDL_Renderer *renderer, const int *plansza,
	const SDL_Color *kolor_gracz_x,
	const SDL_Color *kolor_gracz_o){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			switch (plansza[i * N + j]){
			case GRACZ_X:
				narysuj_x(renderer, i, j, kolor_gracz_x);
				break;
			case GRACZ_O:
				narysuj_o(renderer, i, j, kolor_gracz_o);
				break;
			default: {}
			}
		}
	}
}

//funkcja kontroluje dzialanie programu kiedy gra trwa
void gra_w_toku(SDL_Renderer *renderer, const informacje *gra){
	stworz_plansze(renderer, &KOLOR_PLANSZY);
	wypelnij_plansze(renderer, gra -> plansza,
									 &KOLOR_GRACZ_X, &KOLOR_GRACZ_O);
}

//funkcja wykona sie w przypadku konca gry
void koniec_gry(SDL_Renderer *renderer, const informacje *gra, const SDL_Color *kolor){
  stworz_plansze(renderer, kolor);
	wypelnij_plansze(renderer, gra -> plansza, kolor, kolor);
}

//funkcja kontrolujaca przebieg gry
void tworz_gre(SDL_Renderer *renderer, const informacje *gra){
	switch(gra -> status){
		case GRA_TRWA:
			gra_w_toku(renderer, gra);
			break;
		case GRACZ_X_WYGRYWA:
			koniec_gry(renderer, gra, &KOLOR_GRACZ_X);
			break;
		case GRACZ_O_WYGRYWA:
			koniec_gry(renderer, gra, &KOLOR_GRACZ_O);
			break;
		case REMIS:
			koniec_gry(renderer, gra, &KOLOR_REMISU);
			break;
		default: {}
	}
}
