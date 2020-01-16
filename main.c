//dodajemy niezbedne biblioteki
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
//dodajemy headery
#include "./status_gry.h"
#include "./funkcjonalnosc.h"
#include "./tworzenie_gry.h"

int main(int argc, char *argv[]){
	/* spradzamy czy biblioteka SDL2 ZOSTALA zainicjalizowana w przeciwnym
	wypadku zwracamy komunikat wraz z kodem bledu */
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Nie mozna zainicjalizowac biblioteki sdl2: %s \n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//tworzymy okno o zdefiniowanych wczesniej rozmiarach
	SDL_Window *okno = SDL_CreateWindow("TicTacToe", 100, 100, SZEROKOSC, WYSOKOSC, SDL_WINDOW_SHOWN);

	/*sprawdzamy czy okno zostalo utworzone poprawnie, w przeciwnym razie
	zwracamy komunikat wraz z kodem bledu */
	if (okno == NULL){
		printf("Nie mozna utworzyc okna :%s \n", SDL_GetError());
		return EXIT_FAILURE;
	}
	/*tworzymy strukture powiazana z naszym oknem oraz dodajemy flagi
	umozliwiajace np przyspieszenie sprzetowe*/
	SDL_Renderer *renderer = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	/*sprawdzamy czy renderer zostal utworzony poprawnie, w przeciwnym razie
	zwracamy komunikat wraz z kodem bledu oraz niszczymy okno*/
	if (renderer == NULL){
		SDL_DestroyWindow(okno);
		printf("Nie mozna utworzyc renderera: %s \n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//tworzymy poczatkowy stan gry
	informacje gra = {
		.plansza = {PUSTE, PUSTE, PUSTE,
			    PUSTE, PUSTE, PUSTE,
			    PUSTE, PUSTE, PUSTE},
		.gracz = GRACZ_X,
		.status = GRA_TRWA
	};

	SDL_Event e;
	/* tworzymy petle gry, jezeli natrafimy na SDL_QUIT niszczymy okno oraz wychodzimy z gry
	w przypadku wcisniecia przycisku myszy wywolujemy funkcje nacisnij_pole */
	while (gra.status != WYJSCIE){
		// printf("w while");
		while (SDL_PollEvent(&e)){
			// printf("w while");
			switch (e.type){
			case SDL_QUIT:
				gra.status = WYJSCIE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				// printf("myszka");
				// printf("%f", e.button.y / WYSOKOSC_KOMORKI);
				nacisnij_pole(&gra, e.button.y / WYSOKOSC_KOMORKI, e.button.x / SZEROKOSC_KOMORKI);
				break;
			default: {}
			}
		}

		/*wypelniamy tlo na czarno oraz ustawiamy odswiezanie dokonanych przez nas zmian */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		tworz_gre(renderer, &gra);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(okno);
	SDL_Quit();
	return EXIT_SUCCESS;
}
