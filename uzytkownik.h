#include <iostream>
#include <string>
#include <vector>
#ifndef UZYTKOWNIK_H_
#define UZYTKOWNIK_H_

using namespace std;

class Uzytkownik {
    protected:
        string login;
        string haslo;
        string imie;
        string nazwisko;

    public:
        Uzytkownik(string l, string h, string i, string n)
        :login(l), haslo(h), imie(i), nazwisko(n) {}


    
        virtual void pokazMenu(vector<Uzytkownik*>& baza) = 0;

        virtual ~Uzytkownik() {}

        string getLogin(){return login;}
        string getImie(){return imie;}
        string getNazwisko(){return nazwisko;}
        bool sprawdzHaslo(string h) {return haslo == h;}
};

#endif



        


