# Dziennik z podstawowymi funkcjonalnościami zarządzania ocenami i użytkownikami w C++

---

[Wymagania](#wymagania)

[Do zrobienia](#do-zrobienia)

[Wykonane](#wykonane)

[Znane błędy](#znane-bledy)

[Pliki](#pliki)

---
<a name="wymagania" id="wymagania"></a>
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
<a name="do-zrobienia" id="do-zrobienia"></a>
## Do zrobienia

[] Podział tak aby uczeń widział oceny ze względu na przedmioty

[] Szyfrowanie i odszyfrowywanie haseł z pliku

[] Walidacja podawanych zmiennych jako oceny: nazwy ucznia, nazwy przedmiotu, wartości oceny, opisu, daty, wagi
    
[] Walidacja dodawanych użytkowników przez Administratora

[x] Edycja ocen uczniów

[x] Usuwanie ocen uczniów

[] Opcja administratora do usuwania użytkoników z walidacją żeby zalogowany użytkownik nie mógł się skasować

...

---
<a name="wykonane" id="wykonane"></a>
## Wykonane
[x] Podstawowa kontrola aplikacji (menu nauczyciela i ucznia)

[x] Logowanie użytkowników

[x] Klasy i struktury

[x] Obsługa działania programu w systemie Windows/Linux

[x] Wyświetlanie ocen ucznia

[x] Wyświetlanie listy uczniów

[x] Wystawianie ocen (Dodaje do wektora)

[x] Zapis ocen do plików

[x] Konto administratora z możliwością dodawania użytkowników

[x] 
---
<a name="znane-bledy" id="znane-bledy"></a>
## Znane błędy

- Należy przetestować komunikaty systemowe w Windowsie (Możliwe że w linuxie ścieżkę względną trzeba podawać jako ../path.xyz, a w Windowsie path.xyz)

---

<a name="pliki" id="pliki"></a>
## Pliki
- main.cpp - Zawiera główne menu logowania, odczyt z plików
  
- uzytkownik.h - plik nagłówkowy zawierający klasę użytkownik, która jest też klasą abstrakcyjną
  
- nauczyciel.h - plik nagłówkowy zawierający panel nauczyciela i metody dotyczące działań nauczyciela
  
- uczen.h - plik nagłówkowy zawierający panel ucznia i metody dotyczące działań ucznia
  
- sys_var.h - plik nagłówkowy zawierający sprawdzanie systemu operacyjnego oraz narzędzia walidacyjne
  
- uzytkownicy.txt - plik tekstowy zawierający dane użytkowników
  
- oceny.txt - plik tekstowy zawierający oceny uczniów




