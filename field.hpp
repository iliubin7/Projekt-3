#include <iostream>

//Struktura przeznaczona do przechowywania wspolrzednych
struct Field
{
    int row = 0;
    int column = 0;

    //Przeciazenie operatora () aby ulatwic przypisanie wartosci
    Field operator()(int y, int x)
    {
        this->row = y - 1;
        this->column = x - 1;
        return *this;
    }
};