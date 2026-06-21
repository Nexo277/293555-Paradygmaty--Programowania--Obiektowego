# Projekt: System Zarządzania Listą Obecności (Lab 7)

Projekt zaliczeniowy z przedmiotu **Programowanie Obiektowe**. Główny kod programu, łączący wszystkie wcześniejsze etapy i nową architekturę eksportu danych, znajduje się w pliku `Lab7_ListaObecnosci.cpp`.

## Opis programu
Aplikacja to konsolowy system do zarządzania bazą osób (studentów oraz pracowników) i przypisywania ich do konkretnych list obecności. Program pozwala na pełną interakcję z danymi w pamięci oraz umożliwia zapisywanie stanu końcowego do plików zewnętrznych.

## Funkcjonalności programu
* **Zarządzanie bazą osób:** Dodawanie studentów (z numerem indeksu) oraz pracowników.
* **Obsługa list obecności:** Przypisywanie osób z bazy do wybranych list, sprawdzanie i zmiana statusu obecności (TAK/NIE).
* **Modyfikacja danych:** Możliwość edycji danych osób oraz usuwania ich z list.
* **Zapis i Eksport (System ze schematu):** * Klasyczny zapis do pliku tekstowego przez mechanizm `ISerializable`.
  * Nowy system eksportu oparty na interfejsach z tablicy (`IEksportowalny` oraz `IExporter`) z mapowaniem danych (`std::map`).

## Wykorzystane mechanizmy OOP
W projekcie zostały zaimplementowane kluczowe pojęcia programowania obiektowego:
* **Dziedziczenie i Polimorfizm:** Klasa bazowa `Osoba` oraz klasy pochodne `Student` i `Pracownik` z nadpisanymi metodami wirtualnymi.
* **Klasy abstrakcyjne i Interfejsy:** * `ISerializable` – do prostego zrzutu obiektów do formatu tekstowego.
  * `IEksportowalny` – wymusza implementację metody zwracającej mapę klucz-wartość (użyte w `Student`, `Pracownik`, `ListaObecnosci`).
  * `IExporter` – interfejs dla klas odpowiedzialnych za formatowanie wyjściowe (klasa `ExporterTxt`).
* **Kontenery STL:** Użycie `std::map` oraz iteratorów do dynamicznego zarządzania polami obiektów podczas eksportu.
* **Rzutowanie dynamiczne:** Wykorzystanie `dynamic_cast` do bezpiecznej identyfikacji interfejsów w czasie wykonywania programu.

## Instrukcja uruchomienia

### Wymagania
* Kompilator wspierający standard C++11 lub nowszy (np. `g++`).

### Kompilacja
Aby skompilować główny plik projektu, należy wykonać w terminalu polecenie:
```bash
g++ -std=c++11 Lab7_ListaObecnosci.cpp -o program