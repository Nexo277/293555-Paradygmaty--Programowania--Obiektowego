#include <iostream>
#include <string>

using namespace std;

int znajdzIdx(string *n, int licznik, string klucz) {
    for (int i = 0; i < licznik; i++) {
        if (n[i] == klucz) return i;
    }
    return -1;
}

bool dodajOsobe(string *&n, string *&i, int *&id, bool *&o,
                int &licznik, string nazwisko, string imie, int nr) {

    if (znajdzIdx(n, licznik, nazwisko) != -1) {
        return false; 
    }

    string *noweN = new string[licznik + 1];
    string *noweI = new string[licznik + 1];
    int *noweId = new int[licznik + 1];
    bool *noweO = new bool[licznik + 1];

    for (int j = 0; j < licznik; j++) {
        noweN[j] = n[j];
        noweI[j] = i[j];
        noweId[j] = id[j];
        noweO[j] = o[j];
    }

    noweN[licznik] = nazwisko;
    noweI[licznik] = imie;
    noweId[licznik] = nr;
    noweO[licznik] = false;

    delete[] n;
    delete[] i;
    delete[] id;
    delete[] o;

    n = noweN;
    i = noweI;
    id = noweId;
    o = noweO;

    licznik++;
    return true;
}

bool ustawObecnosc(string *n, bool *o, int licznik, string klucz, bool status) {
    int idx = znajdzIdx(n, licznik, klucz);

    if (idx == -1) {
        return false;
    }

    o[idx] = status;
    return true; 
}

bool usunOsobe(string *&n, string *&i, int *&id, bool *&o,
               int &licznik, string klucz) {

    int idx = znajdzIdx(n, licznik, klucz);

    if (idx == -1) {
        return false;
    }

    string *noweN = new string[licznik - 1];
    string *noweI = new string[licznik - 1];
    int *noweId = new int[licznik - 1];
    bool *noweO = new bool[licznik - 1];

    for (int j = 0, k = 0; j < licznik; j++) {
        if (j != idx) {
            noweN[k] = n[j];
            noweI[k] = i[j];
            noweId[k] = id[j];
            noweO[k] = o[j];
            k++;
        }
    }

    delete[] n;
    delete[] i;
    delete[] id;
    delete[] o;

    n = noweN;
    i = noweI;
    id = noweId;
    o = noweO;

    licznik--;
    return true;
}

void drukujListe(string *n, string *i, int *id, bool *o, int licznik) {
    if (licznik == 0) {
        cout << "Lista jest pusta!\n";
        return;
    }

    for (int j = 0; j < licznik; j++) {
        cout << id[j] << " | "
             << n[j] << " " << i[j]
             << " | Obecnosc: " << o[j] << endl;
    }
}

int main() {
    string *tabN = nullptr;
    string *tabI = nullptr;
    int *tabId = nullptr;
    bool *tabO = nullptr;

    int licznik = 0;
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
            string nazwisko, imie;
            int nr;

            cout << "Nazwisko: ";
            cin >> nazwisko;
            cout << "Imie: ";
            cin >> imie;
            cout << "Indeks: ";
            cin >> nr;

            if (dodajOsobe(tabN, tabI, tabId, tabO, licznik, nazwisko, imie, nr)) {
                cout << "Osoba zostala pomyslnie dodana!\n";
            } else {
                cout << "Blad: Osoba o tym nazwisku juz istnieje!\n";
            }
        }
        else if (menu == 2) {
            string nazwisko;
            bool status;

            cout << "Nazwisko: ";
            cin >> nazwisko;
            cout << "Obecnosc (1/0): ";
            cin >> status;

            if (ustawObecnosc(tabN, tabO, licznik, nazwisko, status)) {
                cout << "Obecnosc zostala zaktualizowana!\n";
            } else {
                cout << "Blad: Nie znaleziono osoby o takim nazwisku!\n";
            }
        }
        else if (menu == 3) {
            string nazwisko;

            cout << "Nazwisko do usuniecia: ";
            cin >> nazwisko;

            if (usunOsobe(tabN, tabI, tabId, tabO, licznik, nazwisko)) {
                cout << "Osoba zostala pomyslnie usunieta!\n";
            } else {
                cout << "Blad: Nie znaleziono osoby o takim nazwisku!\n";
            }
        }
        else if (menu == 4) {
            drukujListe(tabN, tabI, tabId, tabO, licznik);
        }
        else if (menu == 0) {
            break;
        }
        else {
            cout << "Niepoprawny wybor!\n";
        }
    }

    delete[] tabN;
    delete[] tabI;
    delete[] tabId;
    delete[] tabO;

    return 0;
}