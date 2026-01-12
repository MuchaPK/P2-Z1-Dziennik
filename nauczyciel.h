#ifndef NAUCZYCIEL_H_
#define NAUCZYCIEL_H_

#include<iostream>
#include<fstream>
using namespace std;
#include "uzytkownik.h"
#include "uczen.h"
#include "zrobraport.h"

class Nauczyciel : public Uzytkownik {
public:
    Nauczyciel(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {}

    // Funkcja zapisująca stan faktyczny (z pamięci RAM) do pliku tekstowego
    void zapiszWszystkieOcenyDoPliku(vector<Uzytkownik*>& baza) {
        ofstream plik("oceny.txt", ios::trunc);
        if (!plik.is_open()) return;
        for (Uzytkownik* u : baza) {
            // Rzutujemy na Ucznia, żeby dostać się do dzienniczka
            Uczen* ucz = dynamic_cast<Uczen*>(u);
            if (ucz) {
                // Dzięki "friend class" mamy bezpośredni dostęp do ucz->dzienniczek
                for (const auto& o : ucz->dzienniczek) {
                    plik << ucz->getLogin() << ";"
                         << o.przedmiot << ";"
                         << o.symbol << ";"
                         << o.opis << ";"
                         << o.data << ";"
                         << o.waga << endl;
                }
            }
        }
        zrobRaport("Zapisano wszystkie oceny do pliku oceny.txt przez nauczyciela " + imie + " " + nazwisko);
        plik.close();
        cout << " [i] Zapisano zmiany w pliku oceny.txt\n";
    }

    // Pomocnicza funkcja do wyboru ucznia z listy
    Uczen* wybierzUcznia(vector<Uzytkownik*>& baza) {
        vector<Uczen*> listaUczniow;
        int i = 1;
        cout << "\n--- LISTA UCZNIOW ---\n";
        zrobRaport("Nauczyciel " + imie + " " + nazwisko + " wyświetlił listę uczniów.");
        for (Uzytkownik* u : baza) {
            Uczen* ucz = dynamic_cast<Uczen*>(u);
            if (ucz) {
                cout << i++ << ". " << ucz->getImie() << " " << ucz->getNazwisko()
                     << " (" << ucz->getLogin() << ")\n";
                listaUczniow.push_back(ucz);
            }
        }
        if (listaUczniow.empty()) { cout << "Brak uczniow.\n"; return nullptr; }

        cout << "Wybierz numer ucznia (0 anuluje): ";
        int wybor = Sys::pobierzInt();
        if (wybor < 1 || wybor > listaUczniow.size()) return nullptr;

        return listaUczniow[wybor - 1];
    }

    void edytujOcene(vector<Uzytkownik*>& baza) {
        Uczen* ucz = wybierzUcznia(baza);
        if (!ucz) { cout << "Nie ma uczniów.\n"; Sys::pauza();}
        else if (ucz->dzienniczek.empty()) { cout << "Ten uczen nie ma ocen.\n"; Sys::pauza(); }
        else {
            // Wyświetlanie ocen (dostęp bezpośredni dzięki friend)
            cout << "\nOceny ucznia " << ucz->getImie() << ":\n";
            for (int i = 0; i < ucz->dzienniczek.size(); i++) {
                cout << i + 1 << ". ";
                ucz->dzienniczek[i].wypisz();
            }

            cout << "Wybierz numer oceny do edycji: ";
            int nr = Sys::pobierzInt();
            if (nr < 1 || nr > ucz->dzienniczek.size()) { cout << "Zly numer.\n"; Sys::pauza(); }
            else {
                // Edycja bezpośrednia na wektorze
                auto& ocena = ucz->dzienniczek[nr - 1];
                cout << "Edytujesz: " << ocena.przedmiot << " (" << ocena.symbol << ")\n";

                cout << "Nowa ocena (symbol, np. 4+): "; cin >> ocena.symbol;
                cout << "Nowy opis: "; cin.ignore(); getline(cin, ocena.opis);
                cout << "Nowa waga: "; ocena.waga = Sys::pobierzInt();
                cout << "Ocena zaktualizowana.\n";

                // Przeliczenie wartości liczbowej (korzystamy z metody w strukturze Ocena)
                ocena.wartosc = ocena.przeliczNaLiczbe(ocena.symbol);
                zrobRaport("Zaktualizowano ocene dla ucznia " + ucz->getLogin() + " przez nauczyciela " + imie + " " + nazwisko);
                zapiszWszystkieOcenyDoPliku(baza); // Zapis do pliku
            }
        }
    }

    void usunOcene(vector<Uzytkownik*>& baza) {
        Uczen* ucz = wybierzUcznia(baza);
        if (!ucz) return;
        if (ucz->dzienniczek.empty()) { cout << "Brak ocen.\n"; return; }

        cout << "\nOceny do usuniecia:\n";
        for (int i = 0; i < ucz->dzienniczek.size(); i++) {
            cout << i + 1 << ". "; ucz->dzienniczek[i].wypisz();
        }

        cout << "Podaj numer oceny do USUNIECIA: ";
        int nr = Sys::pobierzInt();
        if (nr < 1 || nr > ucz->dzienniczek.size()) { cout << "Zly numer.\n"; return; }

        // Usuwanie z wektora
        ucz->dzienniczek.erase(ucz->dzienniczek.begin() + (nr - 1));
        cout << "Usunieto ocene.\n";
        zrobRaport("Usunieto ocene dla ucznia " + ucz->getLogin() + " przez nauczyciela " + imie + " " + nazwisko);
        zapiszWszystkieOcenyDoPliku(baza); // Zapis do pliku
    }

    void pokazMenu(vector<Uzytkownik*>& baza) override {
        int wybor = 0;
        while (wybor != 5) {
            zrobRaport("Nauczyciel " + imie + " " + nazwisko + " został poprawnie zalogowany do systemu.");
            Sys::wyczysc();
            cout << "\n========================================\n";
            cout << "   PANEL NAUCZYCIELA: " << imie << " " << nazwisko << "\n";
            cout << "========================================\n";
            cout << "1. Wystaw ocene\n";
            cout << "2. Lista uczniow\n";
            cout << "3. Edytuj ocene\n";
            cout << "4. Usun ocene\n";
            cout << "5. Wyloguj\n";
            cout << "wybor > ";
            wybor = Sys::pobierzInt();

            if (wybor == 1) {
                wystawOcene(baza);
                zapiszWszystkieOcenyDoPliku(baza);
            }
            else if (wybor == 2) wypiszUczniow(baza);

            else if (wybor == 3) edytujOcene(baza);
            else if (wybor == 4) usunOcene(baza);
            else if (wybor == 5) break;
            else {
                cout << "Nie ma takiej opcji!\n";
                zrobRaport("Nauczyciel " + imie + " " + nazwisko + " wybral nieprawidlowa opcje w menu.");
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
        zrobRaport("Nauczyciel " + imie + " " + nazwisko + " wypisal liste uczniow.");
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
        ofstream ocenki("oceny.txt", std::ios_base::app | std::ios_base::out);
        ocenki << "\n" << loginUcznia << ";" << przedmiot << ";" << symbol << ";" <<  opis << ";" << data << ";" << waga << ";";
        cout << "Dodano ocene!\n";
        zrobRaport("Nauczyciel " + imie + " " + nazwisko + " wystawil ocene " + symbol + " uczniowi " + loginUcznia + " z przedmiotu " + przedmiot + ".");
        Sys::pauza();
    }
};
#endif