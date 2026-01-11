//cout<<"Loginy: Uczen - login haslo; Nauczyciel - login1 haslo1, Admin - admin admin
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib> 
#include "uzytkownik.h" 
#include "nauczyciel.h"
#include "uczen.h"
#include "admin.h"
#include "zrobraport.h"

using namespace std;

int main() {
    zrobRaport("Program dziennik elektroniczny został uruchomiony.");
    vector<Uzytkownik*> baza;

    ifstream plik_users("uzytkownicy.txt");
    if (plik_users.is_open()) {
        string linia, segment;
        while (getline(plik_users, linia)) {
            if (linia.empty()) continue;
            stringstream ss(linia);
            vector<string> d;
            while(getline(ss, segment, ';')) {
                d.push_back(segment);
            }
            if(d.size() >= 5) {
                if (d[0] == "U") baza.push_back(new Uczen(d[1], d[2], d[3], d[4]));
                else if (d[0] == "N") baza.push_back(new Nauczyciel(d[1], d[2], d[3], d[4]));
                else if (d[0] == "A") baza.push_back(new Admin(d[1], d[2], d[3], d[4]));
            }
        }
        zrobRaport("Dane zostały poprawnie wczytane!");
        plik_users.close();
    } else {
        zrobRaport("BŁAD: Plik uzytkownicy.txt nie został znaleziony przy starcie programu.");
        cout << "BŁAD: Brak pliku uzytkownicy.txt!\n";
        return 1;
    }

    ifstream oceny_plik("oceny.txt");
    if (oceny_plik.is_open()) {
        string linia, segment;
        while(getline(oceny_plik, linia)) {
            if (linia.empty()) continue;
            stringstream ss(linia);
            vector<string> pola;
            while(getline(ss, segment, ';')) pola.push_back(segment);

            if (pola.size() >= 6) { 
                string loginSzukany = pola[0];
                for(Uzytkownik* u : baza) {
                    if(u->getLogin() == loginSzukany) {
                        Uczen* konkretnyUczen = dynamic_cast<Uczen*>(u);
                        if(konkretnyUczen) {
                            int waga = 1;
                            try { waga = stoi(pola[5]); } catch(...) {}
                            konkretnyUczen->dodajOcene(pola[1], pola[2], pola[3], waga, pola[4]);
                        }
                    }
                }
            }
        }
        zrobRaport("Oceny zostały poprawnie wczytane z pliku oceny.txt.");
        oceny_plik.close();
    }


    while (true) {
        Sys::wyczysc();
        cout << "========================================\n";
        cout << "          DZIENNIK ELEKTRONICZNY        \n";
        cout << "========================================\n";
        cout << "Aby wyjsc z programu wpisz exit\n";
        
        string podanyLogin, podaneHaslo;
        cout << "Login: ";
        cin >> podanyLogin;


        if (podanyLogin == "exit") {
            cout << "Do widzenia!\n";
            break;
        }

        cout << "Haslo: ";
        cin >> podaneHaslo;
        podaneHaslo = Sys::szyfrowanie(podaneHaslo, totalnieUkrytyKluczDostepu);
        bool zalogowano = false;


        for (Uzytkownik* u : baza) {

            if (u->getLogin() == podanyLogin && u->sprawdzHaslo(podaneHaslo)) {
                zalogowano = true;
                
                cout << "\nLogowanie poprawne! Witaj " << u->getImie() << ".\n";
                    u->pokazMenu(baza); 
                    break; 
            }
        }

        if (!zalogowano) {
            zrobRaport("Nieudana próba logowania dla loginu: " + podanyLogin);
            cout << "\nBLAD: Niepoprawny login lub haslo!\n";
            cout << "Wcisnij Enter aby sprobowac ponownie...";
            cin.ignore(); cin.get();
        }
    }


    for (Uzytkownik* u : baza) {
        delete u;
    }
    baza.clear();

    return 0;
}