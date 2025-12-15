#include <iostream>
#include <fstream>
#include<vector>
#include "klasy.h"
using namespace std;
//Należy rozdzielić każdą klasę do osobnego pliku
//Należy utworzyć klasy dla odczytanych danych z plików

int main() {
    ifstream oceny_plik("oceny.txt");
    if (!oceny_plik.is_open()) {
        throw runtime_error("Nie mozna otworzyć pliku");
    }

    string p,s,o,d,w;

    string linia;

    int licznik=0;

    while(getline(oceny_plik,linia,';')) {
        switch(licznik) {
            case 0:
                p=linia;
                break;
            case 1:
                s=linia;
                break;
            case 2:
                o=linia;
                break;
            case 3:
                d=linia;
                break;
            case 4:
                w=linia;
                licznik = -1;
                cout<<p<<" "<<s<<" "<<o<<" "<<d<<endl;
                break;
        }
        licznik++;

        //Tutaj należy to wrzucić do wektora
    }



    return 0;
}