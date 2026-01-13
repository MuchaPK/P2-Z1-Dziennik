#ifndef ZROBRAPORT_H_
#define ZROBRAPORT_H_
#define _CRT_SECURE_NO_WARNINGS // Wyłącza ostrzeżenia o localtime w Visual Studio
#include <iostream>
#include <fstream>  // Obsługa plików
#include <string>   // Obsługa string
#include <chrono>   // Obsługa czasu (C++11)
#include <ctime>    // Konwersja czasu
#include <iomanip>  // Formatowanie wejścia/wyjścia (put_time)

using namespace std;


string g_nazwaPliku; 

void utworzNowyPlikRaportu() {
    auto teraz = chrono::system_clock::now();
    time_t czas_t = chrono::system_clock::to_time_t(teraz);

    std::stringstream ss;
    // Formatujemy datę do nazwy pliku. 
    // UWAGA: Używamy myślników "-" zamiast dwukropków ":", bo Windows nie pozwala na ":" w nazwie pliku.
    ss << "raport_" << std::put_time(std::localtime(&czas_t), "%Y-%m-%d_%H-%M-%S") << ".txt";
    
    g_nazwaPliku = ss.str(); // Przypisujemy wygenerowaną nazwę do zmiennej globalnej
}

void zrobRaport(string tekst) {
    // 1. Pobranie aktualnego czasu
    auto teraz = chrono::system_clock::now();
    time_t czas_t = chrono::system_clock::to_time_t(teraz);

    // 2. Otwarcie pliku w trybie dopisywania (ios::app)
    // Jeśli plik nie istnieje, ofstream automatycznie go stworzy.
    ofstream plik("./logi/" + g_nazwaPliku, ios::app);

    if (plik.is_open()) {
        // 3. Zapisanie sformatowanego czasu i tekstu
        // Format: [RRRR-MM-DD GG:MM:SS] Twój tekst
        plik << put_time(localtime(&czas_t), "[%Y-%m-%d %H:%M:%S] ") 
             << tekst << "\n";
        
        // Plik zamknie się automatycznie po wyjściu z zakresu funkcji,
        // ale można to zrobić ręcznie dla porządku:
        plik.close();
    } else {
        cerr << "Błąd: Nie udało się otworzyć pliku raport.txt!" << endl;
    }
}
#endif