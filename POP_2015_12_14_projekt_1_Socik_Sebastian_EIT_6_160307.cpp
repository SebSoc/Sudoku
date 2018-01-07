//POP 2015-12-14 projekt 1 Socik Sebastian EIT 6 160307 Code::Blocks 13.12 GNU GCC Compiler

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int rozmiar = 9;                  //standardowy rozmiar sudoku

struct NieZmieniaj
{
    int a, b;
};

void pomoc(void);
int GenerowanieSudoku(char t[rozmiar][rozmiar], char dogry[rozmiar][rozmiar], NieZmieniaj *poczatkowe, int &IlePocz);
void ZapelnienieSpacjami(char dogry[rozmiar][rozmiar]);
void GornaKrawedz(void);
void Wiersz1(char t[rozmiar][rozmiar], int w);
void Wiersz2(void);
void SrodkowaKrawedz(void);
void DolnaKrawedz(void);
void PiszSudoku(char t[rozmiar][rozmiar]);
bool SprawdzanieCzyWypelniona(char dogry[rozmiar][rozmiar]);
bool SprawdzanieCzyPoczatkowe(char *wpisanie, int IlePocz, NieZmieniaj *poczatkowe);
void PiszMenu1(void);
void PiszMenu2(void);
void Menu1(char dogry[rozmiar][rozmiar], char *wpisanie, string historia);
void Menu2(char t[rozmiar][rozmiar], char dogry[rozmiar][rozmiar], char *wpisanie);
void gra(char dogry[rozmiar][rozmiar], char *wpisanie);
void PrzebiegGry(char dogry[rozmiar][rozmiar], int IlePocz, NieZmieniaj *poczatkowe, char *wpisanie, string historia);
void SprawdzaniePoprawnosci(char dogry[rozmiar][rozmiar], char t[rozmiar][rozmiar], char *wpisanie);

int main()
{
    char t[rozmiar][rozmiar];                       //tablica do przechowywania rozwiazania
    char dogry[rozmiar][rozmiar];                   //tablica, na ktorej przebiega gra
    NieZmieniaj poczatkowe[81];                     //tablica do przechwowywania liczb poczatkowych
    int IlePocz = 0;                                //licznik liczb poczatkowych
    char wpisanie[100];                             //tablica gdzie zapisywane beda komendy wpisane z klawiatury
    string historia;                                //do przechowywania historii ruchow

    pomoc();
    cout << "Podaj numer planszy, w ktora chcesz zagrac (1-5): ";
    if(GenerowanieSudoku(t, dogry, poczatkowe, IlePocz))
        return 1;
    system("cls");
    PiszSudoku(dogry);
    PiszMenu1();
    PrzebiegGry(dogry, IlePocz, poczatkowe, wpisanie, historia);
    system("cls");
    PiszSudoku(dogry);
    SprawdzaniePoprawnosci(dogry, t, wpisanie);
    return 0;
}

void pomoc(void)
{
    cout << "Gra polega na wypelnieniu calej planszy liczbami tak, aby ponizsze ograniczenia byly spelnione:" << endl
         << "- w kazdym polu znajduje sie liczba z zakresu <1,9>;" << endl
         << "- w kazdym wierszu wpisane sa rozne cyfry;" << endl
         << "- w kazdej kolumnie wpisane sa rozne cyfry;" << endl
         << "- plansza jest podzielona na 9 niezachodzacych na siebie kwadratow 3x3," << endl
         << "  w kazdym takim kwadracie wpisane sa rozne cyfry;" << endl
         << "Gracz konczy gre, gdy wszystkie pola zostana poprawnie wypelnione." << endl << endl
         << "Aby wpisac liczbe w wybrane pole wpisz komende w postaci: " << endl
         << "<wiersz><kolumna><cyfra> np. G16 - w pole G1 wpisz cyfre 6." << endl << endl;
}

int GenerowanieSudoku(char t[rozmiar][rozmiar], char dogry[rozmiar][rozmiar], NieZmieniaj *poczatkowe, int &IlePocz)
{
    char sudoku[12] = "sudoku1.txt";
    cin >> sudoku[6];                                       //wybor numery planszy
    ifstream plik(sudoku);
    if(!plik)
    {
        cout << "Zly numer planszy!" << endl;
        return 1;
    }
    for(int i = 0; i < rozmiar; i++)
        for(int j = 0; j < rozmiar; j++)
        {
            plik >> t[i][j];
        }

    ZapelnienieSpacjami(dogry);
//-------------------------------------------- wstawienie liczb poczatkowych
    char liczba;
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(plik)
            {
                plik >> liczba;
                if(liczba != '#')
                {
                    dogry[i][j] = liczba;
                    poczatkowe[IlePocz].a = i;
                    poczatkowe[IlePocz].b = j;
                    IlePocz++;
                }
            }
        }
    }
    plik.close();
return 0;
}

void ZapelnienieSpacjami(char dogry[rozmiar][rozmiar])
{
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            dogry[i][j] = ' ';
        }
    }
}

void GornaKrawedz(void)                             //gorna krawedz ramki sudoku
{
    cout << " ";
    cout << static_cast<char>(201);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 11;j++)
        {
            cout <<  static_cast<char>(205);
        }
        if(i<2)
        {
            cout <<  static_cast<char>(203);
        }
    }
    cout <<  static_cast<char>(187) << endl;
}

void Wiersz1(char t[rozmiar][rozmiar], int w)       //linia z liczbami
{
    int k = 0;                                      //licznik kolumn
    cout << static_cast<char>(186);
    for(int i = 0; i < 3; i++)
    {
        cout << " " << t[w][k] << " ";
        cout << static_cast<char>(179);
        k++;
        cout << " " << t[w][k] << " ";
        cout << static_cast<char>(179);
        k++;
        cout << " " << t[w][k] << " ";
        cout << static_cast<char>(186);
        k++;
    }
    cout << endl;
}

void Wiersz2(void)                                  //waska linia
{
    cout << " ";
    for(int i = 0; i < 3; i++)
    {
        cout << static_cast<char>(186);
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cout << static_cast<char>(196);
            }
            if(i < 2)
            {
               cout << static_cast<char>(197);
            }
        }
    }
    cout << static_cast<char>(186) << endl;
}

void SrodkowaKrawedz(void)                          //szeroka linia
{
    cout << " ";
    cout << static_cast<char>(204);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 11;j++)
        {
            cout <<  static_cast<char>(205);
        }
        if(i < 2)
        {
            cout <<  static_cast<char>(206);
        }
    }
    cout <<  static_cast<char>(185) << endl;
}

void DolnaKrawedz(void)                             //dolna krawedz ramki sudoku
{
    cout << " ";
    cout << static_cast<char>(200);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 11;j++)
        {
            cout <<  static_cast<char>(205);
        }
        if(i < 2)
        {
            cout <<  static_cast<char>(202);
        }
    }
    cout <<  static_cast<char>(188) << endl;
}

void PiszSudoku(char t[rozmiar][rozmiar])
{
    int w = 0;                                      //licznik wierszy
    GornaKrawedz();
    for(int i = 0; i < 9; i += 3)
    {
        cout << static_cast<char>(i + 65);
        Wiersz1(t, w);
        w++;
        Wiersz2();
        cout << static_cast<char>(i + 66);
        Wiersz1(t, w);
        w++;
        Wiersz2();
        cout << static_cast<char>(i + 67);
        Wiersz1(t, w);
        w++;
        if(i < 6)
        {
            SrodkowaKrawedz();
        }
    }
    DolnaKrawedz();
    cout << " ";
    for(int i = 1; i < rozmiar + 1; i++)
    {
        cout << "  " << i << " ";
    }
    cout << endl;
}

bool SprawdzanieCzyWypelniona(char dogry[rozmiar][rozmiar])
{
    for(int i = 0; i < rozmiar; i++)
        for(int j = 0; j < rozmiar; j++)
        {
            if(dogry[i][j] == ' ')
            {
                return false;
            }
        }
    return true;
}

bool SprawdzanieCzyPoczatkowe(char *wpisanie, int IlePocz, NieZmieniaj *poczatkowe)
{
    int k = (int)(wpisanie[0]) - 65;            //zamiana pierwszego znaku na liczbe
    int l = (int)(wpisanie[1]) - 49;            //zamiana drugiego znaku (z ASCII na int)
    for(int i = 0; i < IlePocz; i++)
    {
        if(poczatkowe[i].a == k && poczatkowe[i].b == l)
        {
            return true;
        }
    }
    return false;
}

void PiszMenu1(void)
{
    cout << "\"0\" - Wyswietlenie historii Twoich ruchow." << endl
         << "\"1\" - Wyswietlenie pomocy." << endl
         << "\"2\" - Powrot do gry" << endl;
}

void PiszMenu2(void)
{
    cout << "\"1\" - Wyswietl poprawne rozwiazanie." << endl
         << "\"2\" - Wyswietl Twoje rozwiazanie" << endl
         << "\"3\" - Zakoncz gre." << endl;
}

void Menu1(char dogry[rozmiar][rozmiar], char *wpisanie, string historia)
{
    if(wpisanie[0] == '0')                                                  //wyswietlenie historii
    {
        cout << "Historia Twoich ruchow: " << historia << endl;
    }
    else if(wpisanie[0] == '1')                                             //wyswietlenie pomocy
    {
        system("cls");
        pomoc();
        PiszMenu1();
    }
    else if(wpisanie[0] == '2')                                             //pononowne wyswietlenie planszy
    {
        system("cls");
        PiszSudoku(dogry);
        PiszMenu1();
    }
}

void Menu2(char t[rozmiar][rozmiar],char dogry[rozmiar][rozmiar], char *wpisanie)
{
    while(true)
    {
        cin >> wpisanie;
        if(wpisanie[0] == '1' && wpisanie[1] == NULL)                   //wyswietlenie poprawnego rozwiazania
        {
            system("cls");
            PiszSudoku(t);
            PiszMenu2();
        }
        else if(wpisanie[0] == '2' && wpisanie[1] == NULL)              //wyswietlenie sudoku gracza
        {
            system("cls");
            PiszSudoku(dogry);
            PiszMenu2();
        }
        else if(wpisanie[0] == '3' &&  wpisanie[1] == NULL)             //zakonczenie gry
        {
            return;
        }
        else
        {
            cout << "Zla komenda." << endl;
        }
    }
}

void gra(char dogry[rozmiar][rozmiar], char *wpisanie)
{
        int k = (int)(wpisanie[0]) - 65;            //zamiana pierwszego znaku na liczbe
        int l = (int)(wpisanie[1]) - 49;            //zamiana drugiego znaku (z ASCII na int)
        dogry[k][l] = wpisanie[2];                  //zapisanie odpowiedniej liczby(znaku) do tablicy
        PiszSudoku(dogry);
        PiszMenu1();
}

void PrzebiegGry(char dogry[rozmiar][rozmiar], int IlePocz, NieZmieniaj *poczatkowe, char *wpisanie, string historia)
{
    while(!SprawdzanieCzyWypelniona(dogry))
    {
        cin >> wpisanie;
        if(wpisanie[0] > 64 && wpisanie[0] < 74 && wpisanie[1] > 48 && wpisanie[1] < 58 && wpisanie[2] > 48 && wpisanie[2] < 58 && wpisanie[3] == NULL)
        {
            if(!SprawdzanieCzyPoczatkowe(wpisanie, IlePocz, poczatkowe))
            {
                system("cls");
                gra(dogry, wpisanie);
                historia += wpisanie;
                historia += "; ";
            }
            else
            {
                cout << "Nie mozesz zmieniac wartosci poczatkowych." << endl;
            }
        }
        else if (wpisanie[0] > 47 && wpisanie[0] < 51 && wpisanie[1] == NULL)
        {
            Menu1(dogry, wpisanie, historia);
        }
        else
        {
            cout << "Zla komenda." << endl;
        }
    }
}

void SprawdzaniePoprawnosci(char dogry[rozmiar][rozmiar], char t[rozmiar][rozmiar], char *wpisanie)
{
    for(int i = 0; i < rozmiar; i++)
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(dogry[i][j] != t[i][j])
            {
                cout << "Niepoprawne rozwiazanie." << endl;
                PiszMenu2();
                Menu2(t, dogry, wpisanie);
                return;
            }
        }
    }
    cout << endl << "Gratulacje, poprawnie rozwiazane sudoku !!!" << endl;
}
