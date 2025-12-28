# Dziennik z podstawowymi funkcjonalnościami zarządzania ocenami i użytkownikami w C++

---

[Wymagania](#-wymagania)

[Do zrobienia](#-do-zrobienia)

[Wykonane](#-wykonane)

[Znane błędy](#-znane-błędy)

[Pliki](#-pliki)

---

## Wymagania
[] Dziedziczenie

[] Polimorfizm

[x] Klasy abstrakcyjne

[] Klasy wewnętrzne

[] Odczyt i zapis do pliku/ów

  - Odczyt użytkoników i ocen jest zrobiony
    
[] Generowanie raportu z wynikami działania programu

[] Sprawozdanie

---

## Do zrobienia
[] Zapis ocen do plików

[] Podział tak aby uczeń widział oceny ze względu na przedmioty

[] Szyfrowanie i odszyfrowywanie haseł z pliku

...

---

## Wykonane
[x] Podstawowa kontrola aplikacji (menu nauczyciela i ucznia)

[x] Logowanie użytkowników

[x] Klasy i struktury

[x] Obsługa działania programu w systemie Windows/Linux

[x] Wyświetlanie ocen ucznia

[x] Wyświetlanie listy uczniów

[x] Wystawianie ocen (Dodaje do wektora)

---

## Znane błędy

- Należy przetestować komunikaty systemowe w Windowsie

---

## Pliki
- main.cpp - Zawiera główne menu logowania, odczyt z plików
  
- uzytkownik.h - plik nagłówkowy zawierający klasę użytkownik, która jest też klasą abstrakcyjną
  
- nauczyciel.h - plik nagłówkowy zawierający panel nauczyciela i metody dotyczące działań nauczyciela
  
- uczen.h - plik nagłówkowy zawierający panel ucznia i metody dotyczące działań ucznia
  
- sys_var.h - plik nagłówkowy zawierający sprawdzanie systemu operacyjnego oraz narzędzia walidacyjne
  
- uzytkownicy.txt - plik tekstowy zawierający dane użytkowników
  
- oceny.txt - plik tekstowy zawierający oceny uczniów




