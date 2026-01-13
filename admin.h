#ifndef ADMIN_H_
#define ADMIN_H_
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#include "uzytkownik.h"
#include "sys_var.h"
#include "zrobraport.h"

string totalnieUkrytyKluczDostepu = "KOTWPRALCE";

class Admin : public Uzytkownik {
public:
    Admin(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {};

    void pokazMenu(vector<Uzytkownik*>& baza) override {
        int wybor = 0;
        zrobRaport("Administrator " + imie + " " + nazwisko + " został poprawnie zalogowany do systemu.");
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
        ofstream uzytkownicy("uzytkownicy.txt", ios::app | ios::out);
        string typ_uzytkownika, login, haslo, imie, nazwisko;

        cout << "Typ użytkownika: (U, N, A): "; cin >> typ_uzytkownika;
        cout << "Login: "; cin >> login;
        cout << "Haslo: "; cin >> haslo; haslo = Sys::szyfrowanie(haslo,totalnieUkrytyKluczDostepu);
        cout << "Imie: "; cin >> imie;
        cout << "Nazwisko: "; cin >> nazwisko;

        if (uzytkownicy.is_open()) {
            uzytkownicy << "\n" << typ_uzytkownika << ";" << login << ";" << haslo << ";" <<  imie << ";" << nazwisko;
            if (typ_uzytkownika == "U") baza.push_back(new Uczen(login, haslo, imie, nazwisko));
            else if (typ_uzytkownika == "N") baza.push_back(new Nauczyciel(login, haslo, imie, nazwisko));
            else if (typ_uzytkownika == "A") baza.push_back(new Admin(login, haslo, imie, nazwisko));
            cout << "Dodano użytkownika: " << imie << " " << nazwisko << "!\n";
            zrobRaport("Użytkownik: " + imie + " " + nazwisko + " został poprawnie dodany przez administratora " + this->imie + " " + this->nazwisko + ".");
            Sys::pauza();
        }
        else {
            cout << "Nie ma takiego pliku!\n";
            zrobRaport("Błąd: Nie udało się otworzyć pliku uzytkownicy.txt przy próbie dodania użytkownika przez administratora " + this->imie + " " + this->nazwisko + ".");
            Sys::pauza();
        }

        uzytkownicy.close();
    }

    void wypiszUzytkownikow(vector<Uzytkownik*>& baza) {
        zrobRaport("Administrator " + imie + " " + nazwisko + " wyświetlił listę użytkowników.");
        cout << "\nLista użytkowników w systemie:\n";
        int licznik = 1;
        for (Uzytkownik* u : baza) {
                cout << licznik <<"- " << u->getImie() << " " << u->getNazwisko()<< " (Login: " << u->getLogin() << ") \n";
            licznik++;
        }
    }



    void usunUzytkownika(vector<Uzytkownik*>& baza) {
        wypiszUzytkownikow(baza);
        int do_usuniecia{0};
        do_usuniecia = Sys::pobierzInt();

        if (do_usuniecia == 0) {
            cout<<"Nikogo nie usunięto";
            Sys::pauza();
        }
        else {
            ifstream przed("uzytkownicy.txt", ios::in); //plik musiał istneć podczas uruchamiania programu dlatego już nie sprawdzam
            ofstream po("temp_uzytkownicy.txt", ios::trunc);
            string linia{};

            int licznik{0};
            while (getline(przed, linia)) {
                licznik++;
                if (licznik == do_usuniecia)
                    continue;
                else
                    po << linia << endl;

            }
            zrobRaport("Użytkownik: " + baza[do_usuniecia - 1]->getImie() + " " + baza[do_usuniecia - 1]->getNazwisko() + " został usunięty przez administratora " + this->imie + " " + this->nazwisko + ".");
            przed.close();
            po.close();
            remove("uzytkownicy.txt");
            rename("temp_uzytkownicy.txt", "uzytkownicy.txt");
            Sys::pauza();
        }
    }

};


#endif //ADMIN_H_