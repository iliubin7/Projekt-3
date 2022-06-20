#include <iostream>
#include "game.hpp"

int main()
{
    int size;         //Pole zawierajace informacje o rozmiarze planszy
    int howmanyInRow;   //Pole zawierajace informacje o ilosci znakow w rzedzie potrzebnych do wygranej
    int win = 0;     //Zmienna zawierajaca informacje jaki jest wynik gry
    int y = 0; //Wspolrzedna wiersza
    int x = 0;    //Wspolrzedna kolumny
    Field whereisMove;      //Nastepny ruch zapisany w strukturze

    //Wczytanie wielkosci planszy oraz ilosci znakow potrzebnych do wygranej
    std::cout << "Podaj rozmiar pola kwadratowego" << std::endl;
    std::cin >> size;
    std::cout << "Podaj ilość potrzebnych do wygranej" << std::endl;
    std::cin >> howmanyInRow;
    std::cout << "Uzytkownik gra krzyzykiem, komputer - kolkiem. Uzytkownik zaczyna" << std::endl;

    //Utworzenie obiektu gry oraz zdefiniowanie wielkosci planszy
    //oraz ilosci znakow potrzebnych do wygranej
    Game NewGame(size, howmanyInRow);
    //Wyswietlenie pustej planszy
    NewGame.display();

    //Petla wykonywujaca sie dopoki nie ma roztrzygniecia
    while (!win)
    {
        std::cin >> y >> x; //Wczytanie wsolrzednych

        //Przypiasanie wartosci do strukutury
        whereisMove.row = y - 1;
        whereisMove.column = x - 1;

        NewGame.move(whereisMove); //Wykonanie ruchu gracza
        NewGame.display();      //Wyswietlenie planszy po wykonanych ruchach

        win = NewGame.checkScore(); //Sprawdzenie jaki jest stan gry

        //Switch odczytujacy kto wygrywa
        switch (win)
        {
        case 0:
            break;
        case 1:
            std::cout << "Uzytkownik wygrywa" << std::endl;
            break;
        case 2:
            std::cout << "Komputer wygrywa" << std::endl;
            break;
        case 3:
            std::cout << "Remis" << std::endl;
            break;
        }
    }
}