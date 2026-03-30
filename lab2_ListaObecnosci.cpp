#include <iostream> 
#include <string>

using namespace std;

class Uczen{
    public:
    int nrIndeksu;
    string imie;
    string nazwisko;
    int wzrost;
    string dataUrodzenia;
    bool *obecnosc;



    Uczen(): obecnosc(nullptr), nrIndeksu(0), wzrost(0) {}

    void setImie(string wartosc){
        if(wartosc.length() >= 1){
            imie = wartosc;
        }
    }

    string getImie(){
        return imie;
    }
    void wpiszDane(int dni){
        obecnosc = new bool[dni];
        cout << "Nr indeksu: ";
        cin >> nrIndeksu;
        cout << "Imie: ";
        string tempImie;
        cin >> tempImie;
        setImie(tempImie);
        cout << "Nazwisko: ";
        cin >> nazwisko;
        cout << "Wzrost(cm): ";
        cin >> wzrost;
        cout << "Data urodzenia (dd.mm.rrrr): ";
        cin >> dataUrodzenia;

        for (int i = 0; i < dni; i++) {
            cout << "Obecnosc dzien " << i + 1 << " (1/0): ";
            cin >> *(obecnosc + i);
        }
    }
    void pokazDane(int dni) {
        cout<<nrIndeksu<<"|"<< getImie() <<" "<<nazwisko<<"|Wzrost: "<<wzrost<<"cm|Data urodzenia: "<<dataUrodzenia<<"|Dni: ";
        if(obecnosc != nullptr){
            for(int i=0;i<dni;i++){
                cout<<*(obecnosc+i)<<" ";
            }
        }
        cout<<endl;
    }
};

int main(){
int liczbaDni;
cout<<"Na ile dni zrobic liste? ";
cin>>liczbaDni;

Uczen *tablica1 = new Uczen[10];
Uczen *tablica2 = new Uczen[10];

int licznik1 = 0;
int licznik2 = 0;
int menu,nrTablicy;

while(true){
 cout<<"\n--MENU--";
 cout<<"\n1.Dodaj 2.Edytuj 3.Usun 4.Lista 0.Wyjscie: ";
  cin>>menu;

 if (menu==0)break;

   cout<<"Wybierz tablice (1/2): ";
    cin>>nrTablicy;

    Uczen*aktualnaTablica = (nrTablicy == 1) ? tablica1 : tablica2;
    int*aktualnyLicznik = (nrTablicy == 1) ? &licznik1 : &licznik2;

    if(menu==1){
        if(*aktualnyLicznik < 10){
            (aktualnaTablica+*aktualnyLicznik)->wpiszDane(liczbaDni);
            (*aktualnyLicznik)++;
        }else{
            cout<<"Tablica pelna!\n";
        }
    }else if(menu==2){
        string klucz;
        cout<<"Podaj nazwisko: ";
        cin>>klucz;
        for(int i=0;i<*aktualnyLicznik;i++){
            if((aktualnaTablica+i)->nazwisko == klucz){
                int dzien;
                cout<<"Podaj dzien do edycji (1-"<<liczbaDni<<"): ";
                cin>>dzien;
                if(dzien>=1 && dzien<=liczbaDni){
                    cout<<"Obecnosc"<<dzien<<" (1/0): ";
                    cin>>*((aktualnaTablica+i)->obecnosc + (dzien - 1));
                }
                break;
            }
        }
    }
    else if (menu == 3) {
            string klucz;
            cout << "Podaj nazwisko do usuniecia: ";
            cin >> klucz;
            for (int i = 0; i < *aktualnyLicznik; i++) {
                if ((aktualnaTablica + i)->nazwisko == klucz) {
                    for (int j = i; j < *aktualnyLicznik - 1; j++) {
                        *(aktualnaTablica + j) = *(aktualnaTablica + j + 1);
                    }
                    (*aktualnyLicznik)--;
                    break;
                }
            }
        } 
        else if (menu == 4) {
            cout << "\n--- Lista Obecnosci " << nrTablicy << " ---\n";
            for (int i = 0; i < *aktualnyLicznik; i++) {
                (aktualnaTablica + i)->pokazDane(liczbaDni);
            }
        }
    }
}