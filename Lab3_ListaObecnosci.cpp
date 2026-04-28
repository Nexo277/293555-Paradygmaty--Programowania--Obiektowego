#include <iostream>
#include <string>
using namespace std;

class Zwierze {
private:
    int wzrost;

public:
    Zwierze() : wzrost(0) {}

    void setWzrost(int w) { wzrost = w; }
    int  getWzrost()      { return wzrost; }
};

class Czlowiek : public Zwierze {
private:
    string imie;
    string nazwisko;
    string data_urodzenia;

public:
    Czlowiek() {}

    void   setImie(string w)          { if (w.length() >= 3) imie = w; }
    void   setNazwisko(string w)      { if (w.length() >= 3) nazwisko = w; }
    void   setDataUrodzenia(string w) { data_urodzenia = w; }

    string getImie()          { return imie; }
    string getNazwisko()      { return nazwisko; }
    string getDataUrodzenia() { return data_urodzenia; }
};

class Student : public Czlowiek {
private:
    int  nr_indeksu;
    bool ustawiony;

public:
    Student() : nr_indeksu(0), ustawiony(false) {}

    void setIndeks(int w)     { if (to_string(w).length() >= 4) nr_indeksu = w; }
    void setUstawiony(bool v) { ustawiony = v; }

    int  getIndeks()    { return nr_indeksu; }
    bool czyUstawiony() { return ustawiony; }

    void drukuj() {
        cout << nr_indeksu << " | "
             << getNazwisko() << " " << getImie() << " | "
             << "Data ur.: " << getDataUrodzenia() << " | "
             << "Wzrost: " << getWzrost() << " cm\n";
    }
};

class ListaObecnosci {
private:
    Student *tabOsob[10];
    bool     tabObecnosc[10];
    int      iloscOsob;
    int      nr;
    string   tekst;
    int      prog;

public:
    ListaObecnosci() : iloscOsob(0), nr(0), tekst(""), prog(50) {
        for (int i = 0; i < 10; i++) {
            tabOsob[i]     = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void   setNr(int v)       { nr = v; }
    void   setTekst(string v) { tekst = v; }
    void   setProg(int v)     { if (v >= 0 && v <= 100) prog = v; }
    int    getNr()            { return nr; }
    string getTekst()         { return tekst; }
    int    getProg()          { return prog; }
    int    getIloscOsob()     { return iloscOsob; }

    bool dodajStudenta(Student *s) {
        if (iloscOsob >= 10) return false;
        for (int i = 0; i < iloscOsob; i++) {
            if (tabOsob[i] == s) return false;
        }
        tabOsob[iloscOsob]     = s;
        tabObecnosc[iloscOsob] = false;
        iloscOsob++;
        return true;
    }

    bool ustawObecnosc(string nazwisko, bool status) {
        for (int i = 0; i < iloscOsob; i++) {
            if (tabOsob[i]->getNazwisko() == nazwisko) {
                tabObecnosc[i] = status;
                return true;
            }
        }
        return false;
    }

    bool usunStudenta(string nazwisko) {
        for (int i = 0; i < iloscOsob; i++) {
            if (tabOsob[i]->getNazwisko() == nazwisko) {
                for (int j = i; j < iloscOsob - 1; j++) {
                    tabOsob[j]     = tabOsob[j + 1];
                    tabObecnosc[j] = tabObecnosc[j + 1];
                }
                iloscOsob--;
                return true;
            }
        }
        return false;
    }

    void drukuj() {
        cout << "=== Lista nr " << nr << " | \"" << tekst
             << "\" | Prog zaliczenia: " << prog << "% ===\n";
        if (iloscOsob == 0) {
            cout << "  (lista jest pusta)\n";
            return;
        }
        for (int i = 0; i < iloscOsob; i++) {
            cout << "  ";
            tabOsob[i]->drukuj();
            cout << "    -> Obecnosc: " << (tabObecnosc[i] ? "TAK" : "NIE") << "\n";
        }
    }
};

class InterfejsUzytkownika {
private:
    Student        *tabStudentow;
    ListaObecnosci *tablicaList;
    int             iloscStudentow;
    int             iloscList;
    int             licznik;

    int znajdzStudenta(string nazwisko) {
        for (int i = 0; i < licznik; i++) {
            if (tabStudentow[i].getNazwisko() == nazwisko)
                return i;
        }
        return -1;
    }

    void pokazWszystkichStudentow() {
        if (licznik == 0) {
            cout << "  (baza studentow jest pusta)\n";
            return;
        }
        for (int i = 0; i < licznik; i++) {
            cout << "  " << i + 1 << ". ";
            tabStudentow[i].drukuj();
        }
    }

    void menuDodajStudenta() {
        if (licznik >= iloscStudentow) {
            cout << "Blad: Baza studentow jest pelna!\n";
            return;
        }
        string nazwisko, imie, data;
        int nr, wzrost;

        cout << "Nazwisko: ";       cin >> nazwisko;
        cout << "Imie: ";           cin >> imie;
        cout << "Indeks: ";         cin >> nr;
        cout << "Wzrost (cm): ";    cin >> wzrost;
        cout << "Data urodzenia: "; cin >> data;

        if (nazwisko.length() < 3 || imie.length() < 3) {
            cout << "Blad: Imie i nazwisko musza miec min. 3 znaki!\n";
            return;
        }
        if (to_string(nr).length() < 4) {
            cout << "Blad: Indeks musi miec min. 4 cyfry!\n";
            return;
        }
        if (znajdzStudenta(nazwisko) != -1) {
            cout << "Blad: Student o takim nazwisku juz istnieje!\n";
            return;
        }

        tabStudentow[licznik].setNazwisko(nazwisko);
        tabStudentow[licznik].setImie(imie);
        tabStudentow[licznik].setIndeks(nr);
        tabStudentow[licznik].setWzrost(wzrost);
        tabStudentow[licznik].setDataUrodzenia(data);
        tabStudentow[licznik].setUstawiony(true);
        licznik++;
        cout << "Student zostal dodany do bazy!\n";
    }

    void menuPrzypiszDoListy() {
        cout << "Dostepni studenci w bazie:\n";
        pokazWszystkichStudentow();

        string nazwisko;
        cout << "Podaj nazwisko studenta: "; cin >> nazwisko;
        int idx = znajdzStudenta(nazwisko);
        if (idx == -1) {
            cout << "Blad: Nie znaleziono studenta o takim nazwisku!\n";
            return;
        }

        cout << "Wybierz liste (1-" << iloscList << "): ";
        int nr_listy; cin >> nr_listy;
        if (nr_listy < 1 || nr_listy > iloscList) {
            cout << "Blad: Niepoprawny numer listy!\n";
            return;
        }

        if (tablicaList[nr_listy - 1].dodajStudenta(&tabStudentow[idx]))
            cout << "Student zostal przypisany do listy!\n";
        else
            cout << "Blad: Student juz jest na tej liscie lub lista jest pelna!\n";
    }

    void menuPokazListe() {
        cout << "Wybierz liste (1-" << iloscList << "): ";
        int nr_listy; cin >> nr_listy;
        if (nr_listy < 1 || nr_listy > iloscList) {
            cout << "Blad: Niepoprawny numer listy!\n";
            return;
        }
        tablicaList[nr_listy - 1].drukuj();
    }

    void menuUstawObecnosc() {
        cout << "Wybierz liste (1-" << iloscList << "): ";
        int nr_listy; cin >> nr_listy;
        if (nr_listy < 1 || nr_listy > iloscList) {
            cout << "Blad: Niepoprawny numer listy!\n";
            return;
        }
        string nazwisko;
        bool status;
        cout << "Nazwisko: ";        cin >> nazwisko;
        cout << "Obecnosc (1/0): "; cin >> status;

        if (tablicaList[nr_listy - 1].ustawObecnosc(nazwisko, status))
            cout << "Obecnosc zostala zaktualizowana!\n";
        else
            cout << "Blad: Nie znaleziono studenta na tej liscie!\n";
    }

    void menuUsunZListy() {
        cout << "Wybierz liste (1-" << iloscList << "): ";
        int nr_listy; cin >> nr_listy;
        if (nr_listy < 1 || nr_listy > iloscList) {
            cout << "Blad: Niepoprawny numer listy!\n";
            return;
        }
        string nazwisko;
        cout << "Nazwisko do usuniecia z listy: "; cin >> nazwisko;

        if (tablicaList[nr_listy - 1].usunStudenta(nazwisko))
            cout << "Student zostal usuniety z listy!\n";
        else
            cout << "Blad: Nie znaleziono studenta na tej liscie!\n";
    }

    void menuZmienDane() {
        cout << "Podaj nazwisko studenta do edycji: ";
        string nazwisko; cin >> nazwisko;
        int idx = znajdzStudenta(nazwisko);
        if (idx == -1) {
            cout << "Blad: Nie znaleziono studenta!\n";
            return;
        }

        cout << "Co chcesz zmienic?\n";
        cout << "1. Imie\n";
        cout << "2. Wzrost\n";
        cout << "3. Date urodzenia\n";
        int wybor; cin >> wybor;

        if (wybor == 1) {
            string imie; cout << "Nowe imie: "; cin >> imie;
            tabStudentow[idx].setImie(imie);
            cout << "Imie zaktualizowane!\n";
        } else if (wybor == 2) {
            int w; cout << "Nowy wzrost (cm): "; cin >> w;
            tabStudentow[idx].setWzrost(w);
            cout << "Wzrost zaktualizowany!\n";
        } else if (wybor == 3) {
            string d; cout << "Nowa data urodzenia: "; cin >> d;
            tabStudentow[idx].setDataUrodzenia(d);
            cout << "Data urodzenia zaktualizowana!\n";
        } else {
            cout << "Niepoprawny wybor!\n";
        }
    }

public:
    InterfejsUzytkownika(Student *tab, int iSt, ListaObecnosci *listy, int iList)
        : tabStudentow(tab), iloscStudentow(iSt), tablicaList(listy),
          iloscList(iList), licznik(0)
    {
        for (int i = 0; i < iloscList; i++) {
            tablicaList[i].setNr(i + 1);
            tablicaList[i].setTekst("Lista " + to_string(i + 1));
            tablicaList[i].setProg(50);
        }
    }

    void petla() {
        int wybor;
        while (true) {
            cout << "\n========= MENU =========\n";
            cout << "0. Dodaj studenta do bazy\n";
            cout << "1. Przypisz studenta do listy\n";
            cout << "2. Pokaz liste\n";
            cout << "3. Ustaw obecnosc studenta na liscie\n";
            cout << "4. Usun studenta z listy\n";
            cout << "5. Zmien dane studenta\n";
            cout << "9. Wyjscie\n";
            cout << "Wybor: ";
            cin >> wybor;

            switch (wybor) {
                case 0: menuDodajStudenta();    break;
                case 1: menuPrzypiszDoListy();  break;
                case 2: menuPokazListe();       break;
                case 3: menuUstawObecnosc();    break;
                case 4: menuUsunZListy();       break;
                case 5: menuZmienDane();        break;
                case 9: return;
                default: cout << "Niepoprawny wybor!\n";
            }
        }
    }
};

int main() {
    Student        tablicaStudentow[10];
    ListaObecnosci tablicaList[2];

    InterfejsUzytkownika ui(tablicaStudentow, 10, tablicaList, 2);
    ui.petla();

    return 0;
}