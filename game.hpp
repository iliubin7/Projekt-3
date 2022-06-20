#include <iostream>
#include "field.hpp"

class Game
{
public:
    int **gameBoard;   //Wskaznik na wskaznik, tu bedzie zawarte obszar gry
    int boardSize = 0; //Informacja o rozmiarze planszy
    int numberInRow = 0;    //Informacja o ilosci znakow potrzebnej do wygranej

    int whoIsMove = 0; // Liczba sygnalizujaca kogo jest teraz ruch 0 - uzytkownik 1 - komputer

    Game(int size, int number);   //Konstruktor tworzacy plansze
    void display();               //Funkcja wyswietlajaca plansze
    bool checkEmpty(Field field);  //Funkcja sprawdzajaca czy dane pole jest wolne
    bool checkRange(Field field); //Funkcja sprawdzjaca czy podana liczba miesci sie w zakresie
    void move(Field field);          //Funkcja wykonujaca ruch
    int checkWin();          //Funkcja zwracajaca czy ktos wygral
    bool checkDraw();           //Funkcja sprawdzajaca czy jest remis
    void bestMove();          //Funkcja wykonujaca najlepszy ruch
    int minimax(int **board, int depth, int alpha, int beta, int whetherMax); //Funkcja  algorytmu minimax zwracjaca wartosc danej pozycji
    int checkScore();                                                          //Funkcja zwracajaca jaki jest wynik gry
};