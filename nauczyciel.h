#ifndef NAUCZYCIEL_H_
#define NAUCZYCIEL_H_

#include<iostream>
#include<fstream>
using namespace std;
#include "uzytkownik.h"
#include "uczen.h"

class Nauczyciel : public Uzytkownik {
public:
    Nauczyciel(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {}

    void pokazMenu(vector<Uzytkownik*>& baza) override {
        int wybor = 0;
        while (wybor != 3) {
            Sys::wyczysc();
            cout << "\n========================================\n";
            cout << "   PANEL NAUCZYCIELA: " << imie << " " << nazwisko << "\n";
            cout << "========================================\n";
            cout << "1. Wystaw ocene\n";
            cout << "2. Lista uczniow\n";
            cout << "3. Wyloguj\n";
            cout << "wybor > ";
            wybor = Sys::pobierzInt();

            if (wybor == 1) wystawOcene(baza);
            else if (wybor == 2) wypiszUczniow(baza);
            else if (wybor == 3) break;
            else {
                cout << "Nie ma takiej opcji!\n";
                Sys::pauza();
            }
        }
    }

    void wypiszUczniow(vector<Uzytkownik*>& baza) {
        cout << "\nLista uczniow w systemie:\n";
        for (Uzytkownik* u : baza) {
            if (dynamic_cast<Uczen*>(u)) {
                cout << "- " << u->getImie() << " " << u->getNazwisko() 
                     << " (Login: " << u->getLogin() << ") \n";
            }
        }
        Sys::pauza();
    }

    void wystawOcene(vector<Uzytkownik*>& baza) {
        string loginUcznia;
        cout << "Podaj login ucznia: ";
        cin >> loginUcznia;

        Uczen* wybranyUczen = nullptr;

        for (Uzytkownik* u : baza) {
            if (u->getLogin() == loginUcznia) {
                wybranyUczen = dynamic_cast<Uczen*>(u);
                break;
            }
        }

        if (wybranyUczen == nullptr) {
            cout << "Nie znaleziono takiego ucznia!\n";
            Sys::pauza();
            return;
        }

        string przedmiot, symbol, opis, data;
        int waga;
        
        cout << "Przedmiot: "; cin >> przedmiot;
        cout << "Ocena (np. 4+): "; cin >> symbol;
        cout << "Waga: "; cin >> waga;
        cout << "Data: "; cin >> data;
        cout << "Opis (jedno slowo lub uzyj podkreslen): "; cin >> opis; 

        
        wybranyUczen->dodajOcene(przedmiot, symbol, opis, waga, data);
        ofstream ocenki("../oceny.txt", std::ios_base::app | std::ios_base::out);
        ocenki << "\n" << loginUcznia << ";" << przedmiot << ";" << symbol << ";" <<  opis << ";" << data << ";" << waga << ";";
        cout << "Dodano ocene!\n";
        Sys::pauza();
    }
};
#endif