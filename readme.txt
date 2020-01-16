Do poprawnej komplicji programu potrzebna jest instalacja niektorych bibliotek
dlatego, w razie ich braku:

sudo apt-get install libsdl2-2.0.0
sudo apt-get install libsdl2-gfx-dev

tworzymy katalog: mkdir build
przechodzimy do stworzonego katalogu: cd build
nastepnie uruchamiamy cmake za pomoca komendy cmake ../
wykonjemy polecenie make
uruchamiamy stworzony plik wykonywalny ./TicTacToe

aby wykonac ruch naciskamy lewy przycisk myszy na wybrane pole, nastepnie ture wykonuje drugi gracz,
w przypadku remisu plansza podswietli sie na szaro, jesli wygra gracz X na czerwono,
jesli gracz O na niebiesko, ponowne klikniecie przycisku myszy na plansze spowoduje
rozpoczecie nowej gry
