#ifndef UCZEN_H_
#define UCZEN_H_

#include<iostream>
#include<fstream>
#include<vector>
#include "uzytkownik.h"
#include "sys_var.h"
#include "zrobraport.h"

using namespace std;

class Uczen: public Uzytkownik{
    friend class Nauczyciel;

    public:
        struct Ocena{
            string przedmiot;
            string symbol;
            float wartosc;
            string data;
            string opis;
            int waga;

            Ocena(string p, string s, string o, int w, string d)
            : przedmiot(p), symbol(s), opis(o), waga(w), data(d)
            {
                wartosc = przeliczNaLiczbe(s);
            }

            float przeliczNaLiczbe(string s) {
                if (s == "6") return 6.0;
                if (s == "6-") return 5.75;
                if (s == "5+") return 5.5;
                if (s == "5") return 5.0;
                if (s == "5-") return 4.75;
                if (s == "4+") return 4.5;
                if (s == "4") return 4.0;
                if (s == "4-") return 3.75;
                if (s == "3+") return 3.5;
                if (s == "3") return 3.0;
                if (s == "3-") return 2.75;
                if (s == "2+") return 2.5;
                if (s == "2") return 2.0;
                if (s == "2-") return 1.75;
                if (s == "1+") return 1.5;
                if (s == "1") return 1.0;
                return 0.0;
            }

            void wypisz() const { // const, bo wypisywanie nie zmienia obiektu
                cout << przedmiot << ": " << symbol << " (Waga: " << waga << ") - " << opis << " [" << data << "]" << endl;
                zrobRaport("Wyświetlono ocenę: " + przedmiot + " " + symbol + " dla ucznia.");
            }
        };

    private:
        vector<Ocena> dzienniczek;

    public:
        Uczen(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {}

        void dodajOcene(string przedmiot, string symbol, string opis, int waga, string data) {
            Ocena nowaOcena(przedmiot, symbol, opis, waga, data);
            dzienniczek.push_back(nowaOcena);
            zrobRaport("Dodano ocenę: " + przedmiot + " " + symbol + " dla ucznia " + getLogin());
        }

        // --- ZMIANA: Metody do zarządzania ocenami WEWNĄTRZ klasy Uczen ---

        // Zwraca oceny tylko do odczytu (const), żeby Nauczyciel mógł je wyświetlić, ale nie zmienić "ręcznie"
        const vector<Ocena>& pobierzOceny() const {
            zrobRaport("Pobrano oceny do odczytu");
            return dzienniczek;
        }

        bool usunOcene(int indeks) {
            if (indeks < 0 || indeks >= dzienniczek.size()) return false;
            dzienniczek.erase(dzienniczek.begin() + indeks);
            zrobRaport("Usunięto ocenę o indeksie " + to_string(indeks) + " dla ucznia " + getLogin());
            return true;
        }

        bool edytujOcene(int indeks, string nowySymbol, string nowyOpis, int nowaWaga) {
            if (indeks < 0 || indeks >= dzienniczek.size()) return false;

            // Modyfikujemy konkretną ocenę
            dzienniczek[indeks].symbol = nowySymbol;
            dzienniczek[indeks].wartosc = dzienniczek[indeks].przeliczNaLiczbe(nowySymbol);
            dzienniczek[indeks].opis = nowyOpis;
            dzienniczek[indeks].waga = nowaWaga;
            zrobRaport("Zmodyfikowano ocenę o indeksie " + to_string(indeks) + " dla ucznia " + getLogin());
            return true;
        }
        // ------------------------------------------------------------------

        float obliczSrednia() {
            if (dzienniczek.empty()) return 0.0;
            float suma = 0;
            int wagi = 0;
            for (const auto& o : dzienniczek) {
                suma += o.wartosc * o.waga;
                wagi += o.waga;
            }
            if (wagi == 0) return 0.0;
            return suma / wagi;
        }

    void pokazMenu(vector<Uzytkownik*>& baza) override {
            int wybor = 0;

            while (true) {
                Sys::wyczysc();
                zrobRaport("Uczen " + imie + " " + nazwisko + " został poprawnie zalogowany do systemu.");
                cout << "\n========================================\n";
                cout << "   PANEL UCZNIA: " << imie << " " << nazwisko << "\n";
                cout << "========================================\n";
                cout << "1. Zobacz moje oceny\n";
                cout << "2. Wyloguj\n";
                cout << "Wybor > ";
                wybor = Sys::pobierzInt();


                if (wybor == 1) {
                    cout << "\n--- TWOJE OCENY ---\n";
                    if (dzienniczek.empty()) {
                        zrobRaport("Uczen " + imie + " " + nazwisko + " wyświetlił swoje oceny. (brak ocen)");
                        cout << "Brak ocen w dzienniku.\n";
                    } else {
                        zrobRaport("Uczen " + imie + " " + nazwisko + " wyświetlił swoje oceny.");
                        for(auto& o : dzienniczek) {
                            o.wypisz();
                        }

                        cout << "\nSrednia wazona: " << obliczSrednia() << endl;
                    }

                    cout << "\n";
                    Sys::pauza();
                }
                else if (wybor == 2) {
                    cout << "Wylogowywanie...\n";
                    zrobRaport("Uczen " + imie + " " + nazwisko + " poprawnie wylogował się z systemu.");
                    break;
                }
                else {
                    zrobRaport("Uczen " + imie + " " + nazwisko + " wybral nieprawidłową opcje w menu.");
                    cout << "Nie ma takiej opcji!\n";
                    Sys::pauza();
                }
            }
        }
};

#endif