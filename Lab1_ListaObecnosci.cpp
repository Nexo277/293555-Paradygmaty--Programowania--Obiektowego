#include <iostream>
#include <string>

using namespace std;

class Uczen {
public:
    int nrIndeksu;
    string imie;
    string nazwisko;
    bool *obecnosc;

    void wpiszDane(int dni) {
        obecnosc = new bool[dni];
        cout << "Nr indeksu: ";
        cin >> nrIndeksu;
        cout << "Imie: ";
        cin >> imie;
        cout << "Nazwisko: ";
        cin >> nazwisko;
        for (int i = 0; i < dni; i++) {
            cout << "Obecnosc dzien " << i + 1 << " (1/0): ";
            cin >> *(obecnosc + i);
        }
    }

    void pokazDane(int dni) {
        cout << nrIndeksu << " " << imie << " " << nazwisko << " | Dni: ";
        for (int i = 0; i < dni; i++) {
            cout << *(obecnosc + i) << " ";
        }
        cout << endl;
    }
};

int main() {
    int liczbaDni;
    cout << "Na ile dni zrobic liste? ";
    cin >> liczbaDni;

    Uczen *tablica = new Uczen[10];
    int licznik = 0;
    int menu;

    while (true) {
        cout << "\n1.Dodaj 2.Edytuj 3.Usun 4.Lista 0.Wyjscie: ";
        cin >> menu;

        if (menu == 1) {
            if (licznik < 10) {
                (tablica + licznik)->wpiszDane(liczbaDni);
                licznik++;
            }
        } 
        else if (menu == 2) {
            string klucz;
            cout << "Podaj nazwisko: ";
            cin >> klucz;
            for (int i = 0; i < licznik; i++) {
                if ((tablica + i)->nazwisko == klucz) {
                    int dzien;
                    cout << "Ktory dzien zmienic (1-" << liczbaDni << "): ";
                    cin >> dzien;
                    if (dzien >= 1 && dzien <= liczbaDni) {
                        cout << "Nowa obecnosc (1/0): ";
                        cin >> *((tablica + i)->obecnosc + (dzien - 1));
                    }
                    break;
                }
            }
        } 
        else if (menu == 3) {
            string klucz;
            cout << "Podaj nazwisko: ";
            cin >> klucz;
            for (int i = 0; i < licznik; i++) {
                if ((tablica + i)->nazwisko == klucz) {
                    for (int j = i; j < licznik - 1; j++) {
                        *(tablica + j) = *(tablica + j + 1);
                    }
                    licznik--;
                    break;
                }
            }
        } 
        else if (menu == 4) {
            for (int i = 0; i < licznik; i++) {
                (tablica + i)->pokazDane(liczbaDni);
            }
        } 
        else if (menu == 0) {
            break;
        }
    }

    delete[] tablica;
    return 0;
}