#include <iostream>
#include <string>


using namespace std;

void wpiszDane(int dni, int &nrIndeksu, string &imie, string &nazwisko, bool *&obecnosc) {
    obecnosc = new bool[dni];
    cout << "Nr indeksu: ";
    cin >> nrIndeksu;
    cout << "Imie: ";
    cin >> imie;
    cout << "Nazwisko: ";
    cin >> nazwisko;
    obecnosc = new bool[dni];
    for (int i = 0; i < dni; i++) {
        cout << "Obecnosc dzien " << i + 1 << " (1/0): ";
        cin >> *(obecnosc + i);
    }
}
void pokazDane(int dni, int nrIndeksu, string imie, string nazwisko, bool *obecnosc) {
    cout << nrIndeksu << " " << imie << " " << nazwisko << " | Dni: ";
    if(obecnosc != nullptr) {
    for (int i = 0; i < dni; i++) {
        cout << *(obecnosc + i) << " ";
    }
    cout << endl;
}
}
int main() {

    int liczbaDni;
    cout << "Na ile dni zrobic liste? ";
    cin >> liczbaDni;

    int nrIndeksu[10];
    string imie[10];
    string nazwisko[10];
    bool *obecnosc[10] = {nullptr};
    int licznik = 0;
    int menu;

    while (true) {
        cout << "\n1.Dodaj 2.Edytuj 3.Usun 4.Lista 0.Wyjscie: ";
        cin >> menu;

        if (menu == 1) {
            if (licznik < 10) {
                wpiszDane(liczbaDni, nrIndeksu[licznik], imie[licznik], nazwisko[licznik], obecnosc[licznik]);
                licznik++;
            }
        } 
        else if (menu == 2) {
            string klucz;
            cout << "Podaj nazwisko: ";
            cin >> klucz;
            for (int i = 0; i < licznik; i++) {
                if (nazwisko[i] == klucz) {
                    wpiszDane(liczbaDni, nrIndeksu[i], imie[i], nazwisko[i], obecnosc[i]);
                    break;
                }
            }
        } 
        else if (menu == 3) {
            string klucz;
            cout << "Podaj nazwisko: ";
            cin >> klucz;
            for (int i = 0; i < licznik; i++) {
                if (nazwisko[i] == klucz) {
                    delete[] obecnosc[i];
                    for (int j = i; j < licznik - 1; j++) {
                        nrIndeksu[j] = nrIndeksu[j + 1];
                        imie[j] = imie[j + 1];
                        nazwisko[j] = nazwisko[j + 1];
                        obecnosc[j] = obecnosc[j + 1];
                    }
                    licznik--;
                    break;
                }
            }
        } 
        else if (menu == 4) {
            for (int i = 0; i < licznik; i++) {
                pokazDane(liczbaDni, nrIndeksu[i], imie[i], nazwisko[i], obecnosc[i]);
            }       
}
        else if (menu == 0) {
            break;
        }
    }

    for (int i = 0; i < licznik; i++) {
        delete[] obecnosc[i];
    }

    return 0;
}