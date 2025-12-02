#include <iostream>
#include <string>
#include <vector>

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
    void pokazMenu(vector<Uzytkownik*>& baza) override;
};
class Nauczyciel : public Uzytkownik {
public:
    Nauczyciel(string l, string h, string i, string n) : Uzytkownik(l, h, i, n) {}

    void pokazMenu(vector<Uzytkownik*>& baza) override {
        int wybor = 0;
        while (wybor != 3) {
            cout << "\n--- NAUCZYCIEL: " << imie << " " << nazwisko << " ---\n";
            cout << "1. Wystaw ocene\n";
            cout << "2. Lista uczniow\n";
            cout << "3. Wyloguj\n";
            cout << "wybor > ";
            cin >> wybor;

            if (wybor == 1) wystawOcene(baza);
            else if (wybor == 2) wypiszUczniow(baza);
            else if (wybor == 3) break;
        }
    }

    void wypiszUczniow(vector<Uzytkownik*>& baza) {
        cout << "\nLista uczniow w systemie:\n";
        for (Uzytkownik* u : baza) {
            if (dynamic_cast<Uczen*>(u)) {
                cout << "- " << u->getImie() << " " << u->getNazwisko() 
                     << " (Login: " << u->getLogin() << ")\n";
            }
        }
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
        cout << "Dodano ocene!\n";
    }
};
        


