#ifndef ADMIN_H_
#define ADMIN_H_
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#include "uzytkownik.h"
#include "sys_var.h"



class Admin : public Uzytkownik {
public:
    Admin(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {};

    void pokazMenu(vector<Uzytkownik*>& baza) override {
        int wybor = 0;

        while (wybor != 3) {
            Sys::wyczysc();
            cout << "\n========================================\n";
            cout << "   PANEL ADMINISTRATORA: " << imie << " " << nazwisko << "\n";
            cout << "========================================\n";
            cout << "1. Stwórz użytkownika\n";
            cout << "2. Usuń Użytkownika\n";
            cout << "3. Wyloguj\n";
            cout << "wybor > ";
            wybor = Sys::pobierzInt();

            if (wybor == 1) dodajUzytkownika(baza);
            else if (wybor == 2) usunUzytkownika(baza);
            else if (wybor == 3) break;
            else {
                cout << "Nie ma takiej opcji!\n";
                Sys::pauza();
            }
        }
    }

    void dodajUzytkownika(vector<Uzytkownik*>& baza) {
        ofstream uzytkownicy("../uzytkownicy.txt", ios::app | ios::out);
        string typ_uzytkownika, login, haslo, imie, nazwisko;

        cout << "Typ użytkownika: (U, N, A): "; cin >> typ_uzytkownika;
        cout << "Login: "; cin >> login;
        cout << "Haslo: "; cin >> haslo;
        cout << "Imie: "; cin >> imie;
        cout << "Nazwisko: "; cin >> nazwisko;

        if (uzytkownicy.is_open()) {
            uzytkownicy << "\n" << typ_uzytkownika << ";" << login << ";" << haslo << ";" <<  imie << ";" << nazwisko;
            if (typ_uzytkownika == "U") baza.push_back(new Uczen(login, haslo, imie, nazwisko));
            else if (typ_uzytkownika == "N") baza.push_back(new Nauczyciel(login, haslo, imie, nazwisko));
            else if (typ_uzytkownika == "A") baza.push_back(new Admin(login, haslo, imie, nazwisko));
            cout << "Dodano użytkownika: " << imie << " " << nazwisko << "!\n";
            Sys::pauza();
        }
        else {
            cout << "Nie ma takiego pliku!\n";
            Sys::pauza();
        }

        uzytkownicy.close();
    }

    //Trzeba zrobić żeby nie mógł skasować siebie
    //Trzeba zrobić kasowanie z pliku
    void usunUzytkownika(vector<Uzytkownik*>& baza) {}
};


#endif //ADMIN_H_