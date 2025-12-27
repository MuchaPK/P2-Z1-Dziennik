#ifndef UCZEN_H_
#define UCZEN_H_

#include<iostream>
#include<fstream>
using namespace std;
#include "uzytkownik.h"
#include "sys_var.h"

class Uczen: public Uzytkownik{
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
        };
        void wypisz() {
            cout << przedmiot << ": " << symbol << " (Waga: " << waga << ") - " << opis << endl;
        }
    };
    private:
        vector<Ocena> dzienniczek;
    
    public:
        Uczen(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {}

        void dodajOcene(string przedmiot, string symbol, string opis, int waga, string data) {
            Ocena nowaOcena(przedmiot, symbol, opis, waga, data);
            dzienniczek.push_back(nowaOcena);

            //Dopisać zapisywanie do pliku
    }
    float obliczSrednia() {
        if (dzienniczek.empty()) return 0.0;
        
        float sumaOcenRazWaga = 0;
        int sumaWag = 0;

        for (Ocena& o : dzienniczek) {
            sumaOcenRazWaga += o.wartosc * o.waga;
            sumaWag += o.waga;
        }

        if (sumaWag == 0) return 0.0;
        return sumaOcenRazWaga / sumaWag;
    }


    void pokazMenu(vector<Uzytkownik*>& baza) override {
    int wybor = 0;

    while (true) {
        Sys::wyczysc();

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
                cout << "Brak ocen w dzienniku.\n";
            } else {
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
            break;
        }
        else {
            cout << "Nie ma takiej opcji!\n";
            Sys::pauza();
        }
    }
}
};

#endif