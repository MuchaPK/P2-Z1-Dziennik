/* Plik sprawdzający używany system operacyjny, niektóre polecenia różnią się w systemach
np. Windows - system("cls"); Linux - system("clear");
//Uwaga: Wszystkie strumienie z przestrzeni std należy dodawać tutaj ręcznie (nie dodawałem w nagłówkach namespace std)

Do prawidłowego działania na linuxie Trzeba włączyć emulację w CLionie: Run -> Edit Configurations... -> Emulate Terminal, wtedy wszystko ładnie czyści
*/
#ifndef SYS_VAR_H
#define SYS_VAR_H
#include <iostream>
#include <string>
#include <cstdlib>

namespace Sys {


    #ifdef _WIN32
        inline constexpr bool windows = true;
    #else
        inline constexpr bool windows = false;
    #endif

    inline void wyczysc() {
        if (windows) {
            std::system("cls");
        }
        else {
            std::system("clear");
        }
    }

    inline void pauza() {
        if (windows) {
            std::system("pause");
        }
        else {
            std::cout<<"Naciśnij Enter, aby kontunuuować...";
            std::cin.get();
            std::cin.get();
        }
    }

    //Zapobiega pobraniu stringa w wyborze, który powoduje wpadnięcie w nieskończoną pętlę
    int pobierzInt() {
        int n;
        while (!(std::cin >> n)) {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout << "Wybierz jedną z opcji: ";
        }
        return n;
    }

    //Szyfrowanie XOR
    string szyfrowanie(string tekst, string klucz) {
        for (int i = 0; i < tekst.length(); i++) {
            tekst[i] ^= klucz[i % klucz.length()];
            if (tekst[i] == ';') tekst[i]='F'; //Zabezpieczenie przed rozparcelowaniem naszej CSV'ki
        }
        return tekst;
    }



    //Walidacja podawanych zmiennych jako oceny: nazwy ucznia, nazwy przedmiotu, wartości oceny, opisu, daty, wagi
    //Walidacja dodawanych użytkowników przez Administratora
}

#endif