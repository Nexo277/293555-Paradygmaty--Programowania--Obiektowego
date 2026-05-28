#include <iostream>
#include <string>
using namespace std;

class ISerializable {
public:
    virtual string serialize() = 0;
};

void drukuj(ISerializable *obj) {
    cout << obj->serialize() << "\n";
}

class Osoba {
protected:
    string imie;
    string nazwisko;
    bool   ustawiony;
    
public:
    Osoba() : ustawiony(false) {}

    void   setImie(string w)     {if (w.length() >= 3) imie = w; }
    void   setNazwisko(string w) {if (w.length() >= 3) nazwisko = w; }

    string getImie()             {return imie; }
    string getNazwisko()         {return nazwisko; }

    void setUstawiony(bool v)    {ustawiony = v; }
    bool czyUstawiony()          {return ustawiony; }

    virtual void drukuj() {
        cout << "Osoba: " << nazwisko << " " << imie << "\n";
    }
};

class Student : public Osoba, public ISerializable {
private:
    int nr_indeksu;
public:
    Student() : nr_indeksu(0) {}
    
    void setIndeks(int w) {if (to_string(w).length() >= 4) nr_indeksu = w; }
    int  getIndeks()      {return nr_indeksu; }

    void drukuj() {
        cout << "STUDENT: " << nr_indeksu << " | " << nazwisko << " " << imie << "\n";
    }

    string serialize() {
        return "STUDENT: " + to_string(nr_indeksu) + " | " + nazwisko + " " + imie;
    }
};

class Pracownik : public Osoba {
public:
    void drukuj() {
        cout << "PRACOWNIK: " << nazwisko << " " << imie << "\n";
    }
};

class ListaObecnosci : public ISerializable {
private:
    Osoba  *tabOsob[10];
    bool    tabObecnosc[10];
    int     iloscOsob;
    int     nr;
    string  tekst;
    int     prog;

public:
    ListaObecnosci() : iloscOsob(0), nr(0), tekst(""), prog(50) {
        for (int i = 0; i < 10; i++) {
            tabOsob[i]     = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void   setNr(int v)       {nr = v; }
    void   setTekst(string v) {tekst = v; }
    void   setProg(int v)     {if (v >= 0 && v <= 100) prog = v; }
    int    getNr()            {return nr; }
    string getTekst()         {return tekst; }
    int    getProg()          {return prog; }
    int    getIloscOsob()     {return iloscOsob; }

    bool dodajStudenta(Osoba *s) {
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

    string serialize() {
        string wynik = "Lista nr " + to_string(nr) + " - " + tekst;
        return wynik;
    }
};

class InterfejsUzytkownika {
private:
    Osoba          **tabStudentow;
    ListaObecnosci *tablicaList;
    int             iloscStudentow;
    int             iloscList;
    int             licznik;

    int znajdzStudenta(string nazwisko) {
        for (int i = 0; i < licznik; i++) {
            if (tabStudentow[i]->getNazwisko() == nazwisko)
                return i;
        }
        return -1;
    }

    void pokazWszystkichStudentow() {
        if (licznik == 0) {
            cout << "  (baza jest pusta)\n";
            return;
        }
        for (int i = 0; i < licznik; i++) {
            cout << "  " << i + 1 << ". ";
            tabStudentow[i]->drukuj();
        }
    }

    void menuDodajStudenta() {
        if (licznik >= iloscStudentow) {
            cout << "Blad: Baza jest pelna!\n";
            return;
        }
        
        cout << "Kogo chcesz dodac?\n1. Student\n2. Pracownik\nWybor: ";
        int typ; cin >> typ;
        if (typ != 1 && typ != 2) {
            cout << "Blad: Niepoprawny wybor!\n";
            return;
        }

        string nazwisko, imie;
        cout << "Nazwisko: "; cin >> nazwisko;
        cout << "Imie: ";     cin >> imie;

        if (nazwisko.length() < 3 || imie.length() < 3) {
            cout << "Blad: Imie i nazwisko musza miec min. 3 znaki!\n";
            return;
        }
        if (znajdzStudenta(nazwisko) != -1) {
            cout << "Blad: Osoba o takim nazwisku juz istnieje!\n";
            return;
        }

        if (typ == 1) {
            int nr;
            cout << "Indeks: "; cin >> nr;
            if (to_string(nr).length() < 4) {
                cout << "Blad: Indeks musi miec min. 4 cyfry!\n";
                return;
            }
            Student* s = new Student();
            s->setNazwisko(nazwisko);
            s->setImie(imie);
            s->setIndeks(nr);
            s->setUstawiony(true);
            tabStudentow[licznik] = s;
        } else {
            Pracownik* p = new Pracownik();
            p->setNazwisko(nazwisko);
            p->setImie(imie);
            p->setUstawiony(true);
            tabStudentow[licznik] = p;
        }

        licznik++;
        cout << "Osoba zostala dodana do bazy!\n";
    }

    void menuPrzypiszDoListy() {
        cout << "Dostepne osoby w bazie:\n";
        pokazWszystkichStudentow();

        string nazwisko;
        cout << "Podaj nazwisko osoby: "; cin >> nazwisko;
        int idx = znajdzStudenta(nazwisko);
        if (idx == -1) {
            cout << "Blad: Nie znaleziono osoby o takim nazwisku!\n";
            return;
        }

        cout << "Wybierz liste (1-" << iloscList << "): ";
        int nr_listy; cin >> nr_listy;
        if (nr_listy < 1 || nr_listy > iloscList) {
            cout << "Blad: Niepoprawny numer listy!\n";
            return;
        }

        if (tablicaList[nr_listy - 1].dodajStudenta(tabStudentow[idx]))
            cout << "Osoba zostala przypisana do listy!\n";
        else
            cout << "Blad: Osoba juz jest na tej liscie lub lista jest pelna!\n";
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
            cout << "Blad: Nie znaleziono osoby na tej liscie!\n";
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
            cout << "Osoba zostala usunieta z listy!\n";
        else
            cout << "Blad: Nie znaleziono osoby na tej liscie!\n";
    }

    void menuZmienDane() {
        cout << "Podaj nazwisko osoby do edycji: ";
        string nazwisko; cin >> nazwisko;
        int idx = znajdzStudenta(nazwisko);
        if (idx == -1) {
            cout << "Blad: Nie znaleziono osoby!\n";
            return;
        }

        cout << "Co chcesz zmienic?\n";
        cout << "1. Imie\n";
        int wybor; cin >> wybor;

        if (wybor == 1) {
            string imie; cout << "Nowe imie: "; cin >> imie;
            tabStudentow[idx]->setImie(imie);
            cout << "Imie zaktualizowane!\n";
        } else {
            cout << "Niepoprawny wybor!\n";
        }
    }

public:
    InterfejsUzytkownika(Osoba **tab, int iSt, ListaObecnosci *listy, int iList)
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
            cout << "0. Dodaj osobe do bazy\n";
            cout << "1. Przypisz osobe do listy\n";
            cout << "2. Pokaz liste\n";
            cout << "3. Ustaw obecnosc osoby na liscie\n";
            cout << "4. Usun osobe z listy\n";
            cout << "5. Zmien dane osoby\n";
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
    cout << "--- DEMO Z TABLICY ---\n";
    Student testStudent;
    testStudent.setNazwisko("Kowalski");
    testStudent.setImie("Jan");
    testStudent.setIndeks(1234);

    ListaObecnosci testLista;
    testLista.setNr(1);
    testLista.setTekst("Programowanie");

    drukuj(&testStudent);
    drukuj(&testLista);
    cout << "----------------------\n";

    Osoba* tablicaStudentow[10] = {nullptr};
    ListaObecnosci tablicaList[2];

    InterfejsUzytkownika ui(tablicaStudentow, 10, tablicaList, 2);
    ui.petla();

    return 0;
}