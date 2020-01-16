cmake_minimum_required(VERSION 3.0)
#ustawiamy minimalna wersje programu cmake

project(TicTacToe)
#ustalamy nazwe projektu

#sprawdzamy czy jest zainstalowana biblioteka SDL2 i ja dodajemy
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#sprawdzamy czy jest zainstalowana biblioteka SDL2_GFX i ja dodajemy
find_package(PkgConfig)
pkg_check_modules(SDL2_GFX SDL2_gfx)
include_directories(${SDL2_GFX_INCLUDE_DIRS})

#ustawiamy flagi do komplikacji
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Werror -fdump-rtl-expand")

#ustawiamy pliki z rozszerzeniem .c jako SRCS
set(SRCS
  main.c
  tworzenie_gry.c
  funkcjonalnosc.c
)

#ustawiamy pliki z rozszerzeniem.h jako HEADERS
set(HEADERS
  funkcjonalnosc.h
  tworzenie_gry.h
  status_gry.h
)


#dodajemy plik wykonywalny TicTacToe ktory stworzy sie na postawie dodanych plikow
add_executable(TicTacToe ${SRCS} ${HEADERS})
#linkujemy potrzebne biblioteki z ktorych korzystamy
target_link_libraries(TicTacToe ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})
