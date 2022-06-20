#include <iostream>
#include <algorithm>
#include "game.hpp"

//Konstruktor tworzacy plansze
Game::Game(int size, int number) : boardSize(size), numberInRow(number)
{
    //Dynamicznie stworzenie tablicy z wskaznikami do nastepnej tablicy
    gameBoard = new int *[size];
    for (int i = 0; i < size; i++)
        gameBoard[i] = new int[size];

    //Przypisanie kazdemu elementowi stworzonej planszy wartosc 0 - puste pole
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gameBoard[i][j] = 0;
        }
    }
}

//Funkcja wyswietlajaca plansze
void Game::display()
{
    for (int i = 0; i < boardSize; i++)
    {
        std::cout << "  -";
        for (int k = 0; k < boardSize; k++)
            std::cout << "----";
        std::cout << std::endl;

        std::cout << i + 1 << " "; // numeracja pionowa
        for (int j = 0; j < boardSize; j++)
        {
            if (gameBoard[i][j] == 0)
                std::cout << "|   ";
            else if (gameBoard[i][j] == 1)
                std::cout << "| x ";
            else if (gameBoard[i][j] == 2)
                std::cout << "| o ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " ";
    for (int i = 0; i < boardSize; i++)
    {
        std::cout << "   " << i + 1;
    }
    std::cout << std::endl;
}

//Funkcja sprawdzajaca czy dane pole jest wolne
//Jesli dane pole jest wolne zwraca true
//Jesli nie jest wolne zwraca false
bool Game::checkEmpty(Field field)
{
    if (gameBoard[field.row][field.column] == 0)
        return true;
    else
        return false;
}

//Funkcja sprawdzjaca czy podana liczba miesci sie w zakresie
// Jesli wartosc miesci sie w zakresie zwraca true
// Jesli nie miesci sie w zakresie zwraca false
bool Game::checkRange(Field field)
{
    if ((field.row < boardSize && field.row >= 0) && (field.column < boardSize && field.column >= 0))
        return true;
    else
        return false;
}

//Funkcja wykonujaca ruch
void Game::move(Field field)
{
    if (checkRange(field)) //Sprawdzenie czy miesci sie w zakresie
    {
        if (whoIsMove == 0) //Sprawdzenie czy jest ruch przez uzytkownika krzyzykiem
        {
            
            if (checkEmpty(field)) //Sprawdzenie czy wskazane pole jest wolne
            {
                gameBoard[field.row][field.column] = 1; //Wpisanie we wskazane pole wartosc odpowiadajace krzyzykowi
                whoIsMove = 1;                              //Zmiana ze kolejny ruch bedzie komputera
            }
            else
            {
                    std::cout << "Podaj ruch jeszcze raz" << std::endl; //Jesli podano ruch na zajete pole pojawia sie komunikat
                
                
            }    
        }
        else // Sprawdzenie czy jest ruch przez komputera kolkiem 
        {
            if (checkEmpty(field)) //Sprawdzenie czy wskazane pole jest wolne
            {
                gameBoard[field.row][field.column] = 2; //Wpisanie we wskazane pole wartosc odpowiadajace kolku
                whoIsMove = 0;                              //Zmiana ze kolejny ruch bedzie uzytkownika
            }
            else
            {
                  std::cout << "Podaj ruch jeszcze raz" << std::endl; //Jesli podano ruch na zajete pole pojawia sie komunikat
                 
            }
        }
        if (checkScore() != 0)
        {
            return;
        }
        else{
            bestMove();
        }
        
    }
    else
        std::cout << "Blad zakresu podaj ruch jeszcze raz" << std::endl; //Wyswietlenie informacji o bledzie zakresu

}

//Funkcja zwracajaca czy ktos wygral
//0-nikt
//1-uzytkownik (krzyzyk)
//2-komputer (kolko)
int Game::checkWin()
{
    int howmanyInaRow = 0; //Informacja ile jest liczb pod rzad
    int supDiagonal = 0;   //Liczba ilosci rzedu potrzebna przy badaniu wygranych po skosach

    //Petla odczytujaca kazda pozycje na planszy
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (gameBoard[i][j] == 1) //W chwili gdy znajdzie krzyzyk
            {
                howmanyInaRow = 0; //Zerowanie ilosci krzyzykow pod rzad

                for (int k = i; k < boardSize; k++) //Sprawdzenie wygranej w pionie
                {
                    if (k < i + numberInRow) //Sprawdzenie czy jest mozliwa wygrana
                    {
                        if (gameBoard[k][j] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc w pionie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura w pionie nie jest krzyzykiem przerywa sprawdzanie w pionie
                    }
                }

                howmanyInaRow = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                for (int k = j; k < boardSize; k++) //Sprawdzenie w poziomie
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[i][k] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc w poziomie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura w pozimie nie jest krzyzykiem przerywa sprawdzanie w poziomie
                    }
                }

                howmanyInaRow = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                supDiagonal = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < boardSize; k++) //Sprawdzenie po skosie na prawo ( z lewej  gory na prawo dol)
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[k][supDiagonal] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            supDiagonal++;
                            if (supDiagonal > boardSize) //Jesli zmienna jest wieksza niz wielkosc planszy przerywa petle
                                break;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                        }
                        else
                            break; //Jesli kolejna figura po skosie nie jest krzyzykiem przerywa sprawdzanie po skosie
                    }
                }

                howmanyInaRow = 0;                       //Zerowanie ilosci krzyzykow pod rzad
                supDiagonal = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < boardSize; k++) //Sprawdzenie po skosie na lewo( prawej gory na lewo dol)
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[k][supDiagonal] == 1) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;

                            if (supDiagonal < 0) //Jesli zmienna jest mniejsza niz zero przerywa petle
                                break;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 1
                                return 1;
                            supDiagonal--;
                        }
                        else
                            break; //Jesli kolejna figura po skosie nie jest krzyzykiem przerywa sprawdzanie po skosie
                    }
                }
            }
            else if (gameBoard[i][j] == 2) // Jesli petla glowna spotyka kolko na planszy
            {

                howmanyInaRow = 0;                       //Zerowanie ilosci kolek pod rzad
                for (int k = i; k < boardSize; k++) //Sprawdzenie w pionie
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[k][j] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc w pionie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                        }
                        else
                            continue; //Jesli kolejna figura w pionie nie jest kolkiem przerywa sprawdzanie w pionie
                    }
                }

                howmanyInaRow = 0;                       //Zerowanie ilosci kolek pod rzad
                for (int k = j; k < boardSize; k++) //Sprawdzenie w poziomie
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[i][k] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc w poziomie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                            continue;
                        }
                        else
                            break; //Jesli kolejna figura w poziomie nie jest kolkiem przerywa sprawdzanie w poziomie
                    }
                }

                howmanyInaRow = 0;                       //Zerowanie ilosci kolek pod rzad
               supDiagonal = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < boardSize; k++) //Sprawdzenie po skosie na prawo
                {
                    if (k < i + numberInRow)
                    {
                        if (gameBoard[k][supDiagonal] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            supDiagonal++;
                            if (supDiagonal > boardSize) //Jesli zmienna jest wieksza niz wielkosc planszy przerywa petle
                                break;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                        }
                        else
                            break;
                    }
                }
                howmanyInaRow = 0;                       //Zerowanie ilosci kolek pod rzad
                supDiagonal = j;                         // Przypisanie do pomocniczej wartosci kolumny
                for (int k = i; k < boardSize; k++) //Sprawdzenie po skosie na lewo
                {
                    if (k < i + numberInRow)
                    {

                        if (gameBoard[k][supDiagonal] == 2) //Sprawdzanie kolejnych wartosci
                        {
                            howmanyInaRow++;
                            if (supDiagonal < 0) //Jesli zmienna jest mniejsza niz zero przerywa petle
                                break;
                            if (howmanyInaRow == numberInRow) //Jesli ilosc po skosie jest rowna potrzebnej do wygranej zwracaj 2
                                return 2;
                            supDiagonal--;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::checkDraw()
{
    int numberOfAllFields = boardSize * boardSize; //Obliczenie ilosc wszystkich pol
    //Petla sprawdzajaca kazde pole planszy
    //Jezeli pole jest puste odejmuje -1 od zmiennej numberOfAllFields
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (gameBoard[i][j] != 0) //Jesli rozne od 0 odejmuje 1
            {
                numberOfAllFields--;
            }
        }
    }
    if (numberOfAllFields == 0) //Jesli nie ma wolnych pol zwraca true
        return true;
    else //Jesli sa wolne pola zwraca false
        return false;
}

void Game::bestMove()
{
    int bestScore = -1000; //Poczatkowa wartosc (komputer szuka jak najwiekszej)
    int depth = 5;          // Na ile ruchow do przodu sprawdza warianty
    Field bestStep;   //Pole zawierajce najlepsze mozliwe posuniecie
    int alpha = -1000;          //Wartosc alpha potrzeba do zastosowania alpha beta ciec
    int beta = 1000;            //Wartosc beta potrzeba do zastosowania alpha beta ciec
    //Petle potrzebne do poruszania sie po planszy
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (gameBoard[i][j] == 0) //Jesli pole jest wolne
            {
                gameBoard[i][j] = 2;                                           //Wstawiamy tam wartosc kolka i sprawdzamy jaki nam wychodzi wynik
                int score = minimax(gameBoard, depth - 1, alpha, beta, 0); //Symulacja kolejnych posuniec z ta wartoscia
                gameBoard[i][j] = 0;                                           // Przypisanie z powrotem 0
                //std::cout<<"wynik = "<< score << std::endl;
                if (score > bestScore) //Sprawdzenie czy uzyskany wynik jest najlepszy
                {
                    bestScore = score;            //Jesli jest najlepszy przypisanie go jako najlepszy wynik
                    bestStep(i + 1, j + 1); //Zapisanie jako najlepszy ruch
                }
            }
        }
    }
    //Po przesymulowaniu kazdej pozycji uzykujemy najlepsza
    //I dla niej przypisuje wartosc kolko
    gameBoard[bestStep.row][bestStep.column] = 2;
    whoIsMove = 0; //0 - uzytkownik,  1 - komputer
}

//Funkcja obliczajaca wartosc danej pozycji
//Komputer sprawdza mozliwosci kolka i krzyzyka w pionie, poziomie i skosie
//Komputer dodaje do siebie wartosci np jesli w poziomie sa 2 znaki i jest mozliwosc zeby dostawic odpowiednia ilosc znakow aby wygrac
//dodaje 2 do ogolnego wyniku, jesli nie ma mozliwosci wygranej w poziomie nie dodaje nic
//Funkcja ta sprawdza dla kolka i krzyzyka wartosc pozycji i odejmuje na koncu krzyzyk od kolka
//Poniewaz zakladam ze komputer(kolko) maksymalizuje, uzytkownik(krzyzyk) minimalizuje
int Game::positionValue(int win)
{
       int counterInaRow = 0; //Ilosc kolka/krzyzyka w rzedzie
    int supDiagonalkol = 0;
    int emptyField = 0; //Ile jest pustych pol w danym rzedzie
    int supDiagonals = 0;
    int subScore1 = 0; //Wynik kolka
    int subScore2 = 0; //Wynik krzyzyka

    //Glowne petle sprawdzajace kazda polzycje na planszy
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (gameBoard[i][j] == 2) //Sprawdzenie czy jest kolko
            {
                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                emptyField = 0;

                for (int k = 0; k < boardSize; k++) //Sprawdzenie w pionie
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (gameBoard[k][j] == 2)
                    {
                        counterInaRow++;
                    }
                    else if (gameBoard[k][j] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[k][j] == 0)
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;

                subScore1 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                emptyField = 0;

                for (int k = 0; k < boardSize; k++) //Sprawdzenie w poziomie
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (gameBoard[i][k] == 2)
                        counterInaRow++;

                    else if (gameBoard[i][k] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[i][k] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore1 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                supDiagonalkol = 0;
                emptyField = 0;
                supDiagonals = j + 1;

                for (int m = i; m >= 0; m--) //funkcja wracajaca na poczatek skosu
                {
                    supDiagonalkol = m;
                    supDiagonals--;
                    if (supDiagonals <= 0)
                    {
                        supDiagonals = 0;
                        break;
                    }
                }

                for (int m = supDiagonalkol; m <= boardSize - 1; m++) //sprawdzenie skosu w prawo
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (gameBoard[m][supDiagonals] == 2)
                    {
                        counterInaRow++;
                    }
                    else if (gameBoard[m][supDiagonals] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[m][supDiagonals] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;

                    supDiagonals++;
                    if (supDiagonals >= boardSize)
                        break;
                }

                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;

                subScore1 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                supDiagonalkol = 0;
                emptyField = 0;
                supDiagonals = j + 1;

                for (int k = i; k < boardSize; k++) //na dol skosu
                {

                    supDiagonalkol = k;
                    supDiagonals--;
                    if (supDiagonals <= 0)
                    {
                        break;
                    }
                }

                for (int m = supDiagonalkol; m >= 0; m--) //sprawdzenie skosu w lewo
                {
                    //Jezeli w rzedzie jest kolko dodajemy ilosc kolek w rzedzie
                    if (gameBoard[m][supDiagonals] == 2)
                    {
                        counterInaRow++;
                    }
                    else if (gameBoard[m][supDiagonals] == 1) //Jesli w rzedzie jest krzyzyk zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[m][supDiagonals] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;

                    supDiagonals++;
                    if (supDiagonals >= boardSize)
                        break;
                }

                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore1 += counterInaRow; //Dodanie do wyniku
            }

            if (gameBoard[i][j] == 1)
            {
                counterInaRow = 0;
                emptyField = 0;

                for (int k = 0; k < boardSize; k++) //Sprawdzenie w pionie
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (gameBoard[k][j] == 1)
                    {
                       counterInaRow++;
                    }
                    else if (gameBoard[k][j] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[k][j] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore2 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                emptyField = 0;

                for (int k = 0; k < boardSize; k++) //Sprawdzenie w poziomie
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (gameBoard[i][k] == 1)
                        counterInaRow++;

                    else if (gameBoard[i][k] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[i][k] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore2 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                supDiagonalkol = 0;
                emptyField = 0;
                supDiagonals = j + 1;

                for (int m = i; m >= 0; m--) //funkcja wracajaca na poczatek skosu
                {
                    supDiagonalkol = m;
                    supDiagonals--;
                    if (supDiagonals <= 0)
                    {
                        supDiagonals = 0;
                        break;
                    }
                }

                for (int m = supDiagonalkol; m <= boardSize - 1; m++) //sprawdzenie skosu w prawo
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (gameBoard[m][supDiagonals] == 1)
                    {
                        counterInaRow++;
                    }
                    else if (gameBoard[m][supDiagonals] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[m][supDiagonals] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                    supDiagonals++;
                    if (supDiagonals >= boardSize)
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore2 += counterInaRow; //Dodanie do wyniku

                //Zerowanie wartosci pomocniczych
                counterInaRow = 0;
                supDiagonalkol = 0;
                emptyField = 0;
                supDiagonals = j + 1;

                for (int k = i; k < boardSize; k++) //na dol skosu
                {

                    supDiagonalkol = k;
                    supDiagonals--;
                    if (supDiagonals <= 0)
                    {
                        break;
                    }
                }
                for (int m = supDiagonalkol; m >= 0; m--) //sprawdzenie skosu w lewo 
                {
                    //Jezeli w rzedzie jest krzyzyk dodajemy ilosc kolek w rzedzie
                    if (gameBoard[m][supDiagonals] == 1)
                    {
                        counterInaRow++;
                    }
                    else if (gameBoard[m][supDiagonals] == 2) //Jesli w rzedzie jest kolko zerujemy ilosc
                    {
                        counterInaRow = 0;
                        emptyField = 0;
                    }
                    else if (gameBoard[m][supDiagonals] == 0) //Jesli w rzedzie jest puste pole  dodajemy wartosc pustego pola
                        emptyField++;
                    if (counterInaRow + emptyField == numberInRow) //Jesli jest odpowiednia ilosc aby wygrac przerwanie petli
                        break;
                    supDiagonals++;
                    if (supDiagonals >= boardSize)
                        break;
                }
                //Sprawdzenie czy jest mozliwosc aby moc wygrac
                if (counterInaRow + emptyField < numberInRow)
                    counterInaRow = 0;
                subScore2 += counterInaRow; //Dodanie do wyniku
            }
        }
    }

    return subScore1 - subScore2; //Zwraca wartosc pozycja kolko minus pozycja krzyzyk
}

//Funkcja  algorytmu minimax zwracjaca wartosc jaka osiagnie gracz przy danym ruchu
int Game::minimax(int **board, int depth, int alpha, int beta, int whetherMax)
{
    int score = 0; //Zmienna zawierajaca wynik

    if ((depth == 0)) //Jesli glebokosc = 0, zwraca aktualny wynik symulowanej planszy
    {
        score = positionValue(whetherMax);
        return score;
    }
    else if (checkWin() == 1) //Jesli wygrywa krzyzyk zwraca -200
        return -200;
    else if (checkWin() == 2) //Jesli wygrywa kolko zwraca 200
        return 200;
    else if (checkDraw()) //Jesli remis zwraca 0
        return 0;

    //1 - gracz maksymalizujacy(komputer)
    //2 - gracz minimalizujacy(uzytkownik)
    if (whetherMax == 1) //Sprawdza kogo ruch
    {

        int bestScore = -100; //Wynik taki aby byl wiekszy
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (board[i][j] == 0) //Jesli pole jest wolne
                {
                    board[i][j] = 2;                                       //Wstawiamy tam wartosc kolka i sprawdzamy jaki nam wychodzi wynik
                    score = minimax(board, depth - 1, alpha, beta, 0); //Symulacja kolejnych posuniec z ta wartoscia
                    board[i][j] = 0;                                       //Ustawiamy do poczatkowego stanu
                    bestScore = std::max(score, bestScore);        //Przypisanie wiekszej wartosci do najlepszego wyniku
                    alpha = std::max(alpha, score);                          //Przypisanie do alphy wiekszej wartosci
                    if (alpha >= beta)                                       //Jesli alpha wieksza od bety przerwanie petli
                        break;                                               //Odcinamy galaz 
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 100; //Wynik taki aby byl mniejszy
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (board[i][j] == 0) //Jesli pole jest wolne
                {
                    board[i][j] = 1;                                       //Wstawiamy tam wartosc krzyzyka i sprawdzamy jaki nam wychodzi wynik
                    score = minimax(board, depth - 1, alpha, beta, 1); //Symulacja kolejnych posuniec z ta wartoscia
                    board[i][j] = 0;                                       //Ustawiamy do poczatkowego stanu
                    bestScore = std::min(score, bestScore);        //Przypisanie mniejszej wartosci do najlepszego wyniku
                    beta = std::min(beta, score);                            //Przypisanie do bety mniejszej wartosci
                    if (alpha >= beta)                                       //Jesli alpha wieksza od bety przerwanie petli
                        break;                                               //Odcinamy galaz
                }
            }
        }
        return bestScore;
    }
}

//Funkcja zwracajaca jaki jest wynik gry
//1-wygrywa krzyzyk
//2-wyrgywa kolko
//3 -remis
//0-niema jeszcze rostrzygniecia i mozna grac dalej
int Game::checkScore()
{
    if (checkWin())
        return checkWin();
    if (checkDraw())
        return 3;
    else
        return 0;
}