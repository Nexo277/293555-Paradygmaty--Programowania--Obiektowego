#include <iostream>
#include <string>

using namespace std;

class Osoba {
private:
    int nr_indeksu;
    string imie;
    string nazwisko;
    bool obecnosc; 
    int wzrost;             
    string data_urodzenia;  

public:
    Osoba() : nr_indeksu(0), obecnosc(false), wzrost(0), data_urodzenia("") {}

    void setImie(string wartosc);
    void setNazwisko(string wartosc);
    void setIndeks(int wartosc);
    void setObecnosc(bool status);
    void setWzrost(int wartosc);
    void setDataUrodzenia(string wartosc);

    string getImie();
    string getNazwisko();
    int getIndeks();
    bool getObecnosc();
    int getWzrost();
    string getDataUrodzenia();
};

void Osoba::setImie(string wartosc) {
    if (wartosc.length() >= 3) imie = wartosc;
}
string Osoba::getImie() { return imie; }

void Osoba::setNazwisko(string wartosc) {
    if (wartosc.length() >= 3) nazwisko = wartosc;
}
string Osoba::getNazwisko() { return nazwisko; }

void Osoba::setIndeks(int wartosc) { 
    if (to_string(wartosc).length() >= 4) nr_indeksu = wartosc; 
}
int Osoba::getIndeks() { return nr_indeksu; }

void Osoba::setObecnosc(bool status) { obecnosc = status; }
bool Osoba::getObecnosc() { return obecnosc; }

void Osoba::setWzrost(int wartosc) { wzrost = wartosc; }
int Osoba::getWzrost() { return wzrost; }

void Osoba::setDataUrodzenia(string wartosc) { data_urodzenia = wartosc; }
string Osoba::getDataUrodzenia() { return data_urodzenia; }

int znajdzIdx(Osoba **tab, int licznik, string klucz) {
    for (int i = 0; i < licznik; i++) {
        if (tab[i]->getNazwisko() == klucz) return i;
    }
    return -1;
}

bool dodajOsobe(Osoba **&tab, int &licznik, string nazwisko, string imie, int nr, int wzrost, string data_urodzenia) {
    if (znajdzIdx(tab, licznik, nazwisko) != -1) {
        return false; 
    }

    Osoba *nowaOsoba = new Osoba();
    nowaOsoba->setNazwisko(nazwisko);
    nowaOsoba->setImie(imie);
    nowaOsoba->setIndeks(nr);
    nowaOsoba->setWzrost(wzrost);                  
    nowaOsoba->setDataUrodzenia(data_urodzenia);   
    nowaOsoba->setObecnosc(false);

    Osoba **nowaTab = new Osoba*[licznik + 1];
    for (int j = 0; j < licznik; j++) {
        nowaTab[j] = tab[j];
    }
    nowaTab[licznik] = nowaOsoba;

    delete[] tab; 
    tab = nowaTab;
    licznik++;
    return true;
}

bool ustawObecnosc(Osoba **tab, int licznik, string klucz, bool status) {
    int idx = znajdzIdx(tab, licznik, klucz);
    if (idx == -1) return false;

    tab[idx]->setObecnosc(status);
    return true; 
}

bool usunOsobe(Osoba **&tab, int &licznik, string klucz) {
    int idx = znajdzIdx(tab, licznik, klucz);
    if (idx == -1) return false;

    Osoba **nowaTab = new Osoba*[licznik - 1];
    for (int j = 0, k = 0; j < licznik; j++) {
        if (j != idx) {
            nowaTab[k] = tab[j];
            k++;
        } else {
            delete tab[j]; 
        }
    }

    delete[] tab;
    tab = nowaTab;
    licznik--;
    return true;
}

void drukujListe(Osoba **tab, int licznik) {
    if (licznik == 0) {
        cout << "Lista jest pusta!\n";
        return;
    }
    for (int j = 0; j < licznik; j++) {
        cout << tab[j]->getIndeks() << " | "
             << tab[j]->getNazwisko() << " " << tab[j]->getImie() << " | "
             << "Data ur.: " << tab[j]->getDataUrodzenia() << " | "
             << "Wzrost: " << tab[j]->getWzrost() << " cm"
             << " | Obecnosc: " << tab[j]->getObecnosc() << endl;
    }
}

int main() {
    Osoba **tabOs1 = nullptr; 
    Osoba **tabOs2 = nullptr; 

    int licznik1 = 0;
    int licznik2 = 0;
    int menu;

    while (true) {
        cout << "\n1. Dodaj osobe\n";
        cout << "2. Ustaw obecnosc\n";
        cout << "3. Usun osobe\n";
        cout << "4. Pokaz liste\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";

        cin >> menu;

        if (menu == 1) {
            int nr_tab;
            cout << "Wybierz tabele (1 lub 2): ";
            cin >> nr_tab;

            if (nr_tab == 1 || nr_tab == 2) {
                string nazwisko, imie, data_urodzenia;
                int nr, wzrost;

                cout << "Nazwisko: ";
                cin >> nazwisko;
                cout << "Imie: ";
                cin >> imie;
                cout << "Indeks: ";
                cin >> nr;
                cout << "Wzrost (cm): ";
                cin >> wzrost;
                cout << "Data urodzenia: ";
                cin >> data_urodzenia;

                if (nazwisko.length() < 3 || imie.length() < 3) {
                    cout << "Blad: Imie i nazwisko musza miec co najmniej 3 litery!\n";
                    continue; 
                }
                if (to_string(nr).length() < 4) {
                    cout << "Blad: Indeks musi miec co najmniej 4 cyfry!\n";
                    continue; 
                }

                bool sukces = false;
                if (nr_tab == 1) {
                    sukces = dodajOsobe(tabOs1, licznik1, nazwisko, imie, nr, wzrost, data_urodzenia);
                } else {
                    sukces = dodajOsobe(tabOs2, licznik2, nazwisko, imie, nr, wzrost, data_urodzenia);
                }

                if (sukces) cout << "Osoba zostala pomyslnie dodana!\n";
                else cout << "Blad: Osoba o tym nazwisku juz istnieje w tej tabeli!\n";
            } else {
                cout << "Niepoprawny numer tabeli!\n";
            }
        }
        else if (menu == 2) {
            int nr_tab;
            cout << "Wybierz tabele (1 lub 2): ";
            cin >> nr_tab;

            if (nr_tab == 1 || nr_tab == 2) {
                string nazwisko;
                bool status;

                cout << "Nazwisko: ";
                cin >> nazwisko;
                cout << "Obecnosc (1/0): ";
                cin >> status;

                bool sukces = false;
                if (nr_tab == 1) sukces = ustawObecnosc(tabOs1, licznik1, nazwisko, status);
                else sukces = ustawObecnosc(tabOs2, licznik2, nazwisko, status);

                if (sukces) cout << "Obecnosc zostala zaktualizowana!\n";
                else cout << "Blad: Nie znaleziono osoby o takim nazwisku!\n";
            } else {
                cout << "Niepoprawny numer tabeli!\n";
            }
        }
        else if (menu == 3) {
            int nr_tab;
            cout << "Wybierz tabele (1 lub 2): ";
            cin >> nr_tab;

            if (nr_tab == 1 || nr_tab == 2) {
                string nazwisko;

                cout << "Nazwisko do usuniecia: ";
                cin >> nazwisko;

                bool sukces = false;
                if (nr_tab == 1) sukces = usunOsobe(tabOs1, licznik1, nazwisko);
                else sukces = usunOsobe(tabOs2, licznik2, nazwisko);

                if (sukces) cout << "Osoba zostala pomyslnie usunieta!\n";
                else cout << "Blad: Nie znaleziono osoby o takim nazwisku!\n";
            } else {
                cout << "Niepoprawny numer tabeli!\n";
            }
        }
        else if (menu == 4) {
            int nr_tab;
            cout << "Wybierz tabele (1 lub 2): ";
            cin >> nr_tab;

            if (nr_tab == 1) {
                cout << "--- TABELA 1 ---\n";
                drukujListe(tabOs1, licznik1);
            } else if (nr_tab == 2) {
                cout << "--- TABELA 2 ---\n";
                drukujListe(tabOs2, licznik2);
            } else {
                cout << "Niepoprawny numer tabeli!\n";
            }
        }
        else if (menu == 0) {
            break;
        }
        else {
            cout << "Niepoprawny wybor!\n";
        }
    }

    for (int i = 0; i < licznik1; i++) {
        delete tabOs1[i];
    }
    delete[] tabOs1;

    for (int i = 0; i < licznik2; i++) {
        delete tabOs2[i];
    }
    delete[] tabOs2;

    return 0;

}