#include <iostream>
#include <ctime> //biblioteka potrzebna to losowania
#include <fstream> //biblioteka do wczytywania i zapisywania do txt
#include <chrono> //biblioteka do mierzenia czasu
using namespace std::chrono; //potrzebne do mierzenia czasu
using namespace std;


//Pierwsza funkcja sluzy do wczytania tabeli z pliku txt
int * WczytanieTablicy (){ //Funkcja zdefiniowana tak zeby nie przyjmowala zadnych argumentow i tak zeby zwracala wczytana tablicy

    fstream wczytywanie; //Tworzenie zmiennej, do ktorej zapisany bedzie plik, typu do tego przeznaczonego

    wczytywanie.open("Liczby.txt", ios::in); //Otwieranie wczesniej przygotowanego pliku tekstowego

    int i=0; //Deklaracja iteratora ktory bedzie sluzyl do zapisywania danych i rownoczesnie do zmierzenia dlugosci tablicy
    int * WczytanaTabela = new int[i]; //Tworzenie tablicy dynamicznej do ktorej zapisane beda liczby
    while(!wczytywanie.eof()){ //While wykonuje sie az skonczy sie plik
       wczytywanie >> WczytanaTabela[i]; //Po kolei wczytywane sa liczby na kolejne miejsca w tablicy
       i++; //Iterator jest zwiekszany przy kazdym wczytaniu liczby, co na raz liczy ile liczb jest wczytane i sluzy do wskazania kolejnego miejsca na ktore wpisywana jest liczba
    }
    wczytywanie.close(); //Zamykanie pliku

    //Wypisywanie do konsoli wczytanej tablicy
    cout<<"Wczytana Tablica = [ ";
    for (int j=0; j<i; j++){ //For idacy od 0 do i (ktore jest jest iloscia liczb)
        cout <<WczytanaTabela[j]<<" ";
    }
    cout<<"]"<<endl;

return WczytanaTabela; //Funkcja zwraca wczytana tablicy

}

//Druga funkcja generuje tablice liczb naturalnych od 0 do nadanego N
int * GenerowanieTablic (int N, int gran) { //Przyjmuje argument dlugosci tabicy do wygenerowania i granice rozrzutu wartości i zwraca tablice

srand((unsigned) time(0)); //Potrzebne do generowania liczb losowych
int * GenerowanaTablica = new int[N]; //Deklaracja tablicy dynamicznej na liczby

for (int j=0; j<N; j++){ //for dzialajacy N (przeslana do funkcji porzadana dlugosæ tablicy) razy
    GenerowanaTablica[j]=((rand()%gran)); }//Wykonywanie na rand modulo  np. 100 daje liczby od 0 do 100

//Kolejna sekcja do wyswietlania, przeszkadza przy generowaniu duzej ilosci tablic
//cout<<"Wygenerowana Tablica = [ ";
//for (int j=0; j<N; j++){
//    cout <<GenerowanaTablica[j]<<" ";
//}
//cout<<"]"<<endl;

return GenerowanaTablica; //Funkcja zwraca wygenerowana tablice
}

//Funkcja Sortowania Babelkowego
void SortowanieBabelkowe(int Tablica[], int N) //Przyjmuje tablice i jej dlugosc
{
    int minimum,maximum,i,pomocnicza; //Tworzone są  zmienne potrzebne nam do algorytmu, minimum i maximum mowia nam od którego do którego elementu mamy porownywac i pomocnicza ktora zapisuje ostatnia granice
    minimum = 0; maximum = N - 1; //Ustawinie pierwszego minimum na 0 i pierwszego maximum jako przedostatni element
  do //Wykonywana jest petla
  {
    pomocnicza = -1; //Przypisanie -1 do zmiennej pomocniczej
    for(i = minimum; i < maximum; i++) //Petla wykonuje sie od indeksu minimalnego elementu do maxymalnego
      if(Tablica[i] > Tablica[i+1]) //Sprawdzanie czy kolejny element jest mniejszy od poprzedniego
      {
        swap(Tablica[i], Tablica[i+1]); //Zamiana elementow miejscami
        if(pomocnicza < 0) minimum = i; //Gdy pomocnicza jest mniejsza od 0 minimum jest ustawiane na wartosc i
        pomocnicza = i; //Przypisanie wartosci i do pomocniczej
      }
    if(minimum) minimum--; //Jesli minimum nie jest rowne 0, to je zmniejszamy
    maximum = pomocnicza; //Maximum przyjmuje wartosc pomocniczej
  } while(pomocnicza >= 0); //Petla konczy sie jesli i jest rowne zero i po tym pomocnicza przejmie ta wartosc

}

int *pom; //Tablica pomocnicza, potrzebna przy scalaniu

//Scalenie posortowanych podtablic
void Scal(int Tablica[], int lewy, int srodek, int prawy) {//Przyjmuje Tablice, indeksy brzegowych elementow i srodek scalanej tablicy
	int i = lewy, j = srodek + 1; //Ustawianie i i j tak by przechodzic po odpowiednich elementach


  for(int i = lewy;i<=prawy; i++) //Kopiowanie calej tablicy do tablicy pomocniczej
    pom[i] = Tablica[i];

  for(int k=lewy;k<=prawy;k++) //Przechodzenie po tablicy od lewej granicy do prawej
  if(i<=srodek) //Jesli indeks idacy od lewej nie dotar jeszcze do srodka
    if(j <= prawy) //Jesli indeks idacy od srodka nie dotar jeszcze do prawej
         if(pom[j]<pom[i]) //Jesli element o indeksie j jest mniejszy od elementu o indeksie i (bierzemy z tabeli pomocniczej zeby nie byly zamienione)
             Tablica[k] = pom[j++];
         else                       //Do tablicy wstawiamy liczbe po prawej od mniejszej liczby
             Tablica[k] = pom[i++];
    else
        Tablica[k] = pom[i++]; //Dla wiekszego od prawy wstwaiamy element o jeden w prawo
  else
      Tablica[k] = pom[j++]; //Dla wiekszego od srodek wstwaiamy element o jeden w prawo
}

//Funkcja Sortowania Przez Scalanie
void SortowaniePrzezScalanie(int Tablica[],int lewy, int prawy) //Przyjmuje Tablice, lewy i prawy koniec
{


	if(prawy<=lewy) return; //Gdy jest jeden element, to jest on już posortowany


	int srodek = (prawy+lewy)/2; //Wyznaczanie srodka tablicy

	SortowaniePrzezScalanie(Tablica, lewy, srodek); //Rekursywnie wywołujemy funkcje na dwoch polowkach tablicy
	SortowaniePrzezScalanie(Tablica, srodek+1, prawy);

	Scal(Tablica, lewy, srodek, prawy); //Scalamy tablice spowrotem
}

//Funkcja do testowania
void TestyLosowe (int Tablica[]) //Przyjmuje pusta zmienna dla tablic
{

    fstream zapisywanie; //Tworzenie zmiennej, ktora bedzie przekazywaæ dane do pliku, typu do tego przeznaczonego
    zapisywanie.open("CzasyLosowe.txt", ios::out); //Otwieranie nowego pliku tekstowego do ktorego zapisywane beda wyniki

    for (int ile=10; ile<100000; ile+=10000){ //For ktory wykonuje sie 10 razy, wartosc iteratora jest na raz tez dlugoscia tablicy ktora kazemy wygenerowaæ programowi. Jest ona tak duza bo co dopiero taka dlugosæ daje jakikolwiek czas dzialania

        Tablica = GenerowanieTablic (ile,100); //Wywolanie generowania tablic o dlugosci zgodnej z iteratorem for'a
        auto startb = high_resolution_clock::now(); //Start mierzenia czasu
        SortowanieBabelkowe(Tablica,ile); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecb = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto BombelkoweCzas = duration_cast<milliseconds>(koniecb - startb); //Zapisujemy czas w typie double w formacie milisekund

        Tablica = GenerowanieTablic (ile,100); //Wywolanie generowania tablic o dlugosci zgodnej z iteratorem for'a
        pom = new int[ile]; //Dostosowanie tablicy pomocniczej do dlugosci wygenerowanej
        auto starts = high_resolution_clock::now(); //Start mierzenia czasu
        SortowaniePrzezScalanie(Tablica,0,ile-1); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecs = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto ScalanieCzas = duration_cast<milliseconds>(koniecs - starts); //Zapisujemy czas w typie double w formacie milisekund

        cout<<"Proba dla "<<ile<<" elementow dla sortowania babelkowego. Czas wykonania: "<<BombelkoweCzas.count()<<"ms"<<endl; //Wyswietlanie wynikow
        cout<<"Proba dla "<<ile<<" elementow dla sortowania przez scalanie. Czas wykonania: "<<ScalanieCzas.count()<<"ms"<<endl;

        zapisywanie<<ile<<","<<BombelkoweCzas.count()<<","<<ScalanieCzas.count()<<endl; //zapisywanie czasow do pliku
    }
    zapisywanie.close(); //zamkniecie pliku

}

//Funkcja do testowania
void TestyPosortowane (int Tablica[]) //Przyjmuje pusta zmienna dla tablic
{

    fstream zapisywanie; //Tworzenie zmiennej, ktora bedzie przekazywaæ dane do pliku, typu do tego przeznaczonego
    zapisywanie.open("CzasyPosortowane.txt", ios::out); //Otwieranie nowego pliku tekstowego do ktorego zapisywane beda wyniki

    for (int ile=10; ile<10000000; ile+=1000000){ //For ktory wykonuje sie 10 razy, wartosc iteratora jest na raz tez dlugoscia tablicy ktora kazemy wygenerowaæ programowi. Jest ona tak duza bo co dopiero taka dlugosæ daje jakikolwiek czas dzialania

        Tablica = new int[ile];
        for (int i=0; i<ile; i++){
            Tablica[i]=i;
        }

        auto startb = high_resolution_clock::now(); //Start mierzenia czasu
        SortowanieBabelkowe(Tablica,ile); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecb = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto BombelkoweCzas = duration_cast<milliseconds>(koniecb - startb); //Zapisujemy czas w typie double w formacie milisekund

        pom = new int[ile]; //Dostosowanie tablicy pomocniczej do dlugosci wygenerowanej
        auto starts = high_resolution_clock::now(); //Start mierzenia czasu
        SortowaniePrzezScalanie(Tablica,0,ile-1); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecs = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto ScalanieCzas = duration_cast<milliseconds>(koniecs - starts); //Zapisujemy czas w typie double w formacie milisekund

        cout<<"Proba dla "<<ile<<" elementow dla sortowania babelkowego. Czas wykonania: "<<BombelkoweCzas.count()<<"ms"<<endl; //Wyswietlanie wynikow
        cout<<"Proba dla "<<ile<<" elementow dla sortowania przez scalanie. Czas wykonania: "<<ScalanieCzas.count()<<"ms"<<endl;

        zapisywanie<<ile<<","<<BombelkoweCzas.count()<<","<<ScalanieCzas.count()<<endl; //zapisywanie czasow do pliku
    }
    zapisywanie.close(); //zamkniecie pliku

}

//Funkcja do testowania
void TestyOdwrotniePosortowane (int Tablica[]) //Przyjmuje pusta zmienna dla tablic
{

    fstream zapisywanie; //Tworzenie zmiennej, ktora bedzie przekazywaæ dane do pliku, typu do tego przeznaczonego
    zapisywanie.open("CzasyOdwrotniePosortowane.txt", ios::out); //Otwieranie nowego pliku tekstowego do ktorego zapisywane beda wyniki


    for (int ile=10; ile<100000; ile+=10000){ //For ktory wykonuje sie 10 razy, wartosc iteratora jest na raz tez dlugoscia tablicy ktora kazemy wygenerowaæ programowi. Jest ona tak duza bo co dopiero taka dlugosæ daje jakikolwiek czas dzialania

        Tablica = new int[ile+1];
        for (int i=ile; i>-1; i--){
            Tablica[ile-i]=i;
        }

        auto startb = high_resolution_clock::now(); //Start mierzenia czasu
        SortowanieBabelkowe(Tablica,ile); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecb = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto BombelkoweCzas = duration_cast<milliseconds>(koniecb - startb); //Zapisujemy czas w typie double w formacie milisekund

        pom = new int[ile]; //Dostosowanie tablicy pomocniczej do dlugosci wygenerowanej
        auto starts = high_resolution_clock::now(); //Start mierzenia czasu
        SortowaniePrzezScalanie(Tablica,0,ile-1); //Wywolanie glownej funkcji z wygnenrowana tablica
        auto koniecs = high_resolution_clock::now(); //Koniec mierzenia czasu
        auto ScalanieCzas = duration_cast<milliseconds>(koniecs - starts); //Zapisujemy czas w typie double w formacie milisekund

        cout<<"Proba dla "<<ile<<" elementow dla sortowania babelkowego. Czas wykonania: "<<BombelkoweCzas.count()<<"ms"<<endl; //Wyswietlanie wynikow
        cout<<"Proba dla "<<ile<<" elementow dla sortowania przez scalanie. Czas wykonania: "<<ScalanieCzas.count()<<"ms"<<endl;

        zapisywanie<<ile<<","<<BombelkoweCzas.count()<<","<<ScalanieCzas.count()<<endl; //zapisywanie czasow do pliku
    }
    zapisywanie.close(); //zamkniecie pliku

}

//Funkcja main, tu odpalane sa inne fukncje i ich obsluga
int main()
{
    int * Tablica; //Tworzenie tablicy dynamicznej do ktorej beda przypisywane wyniki

    TestyLosowe(Tablica); //Wywolywanie testow

    TestyPosortowane(Tablica);

    TestyOdwrotniePosortowane(Tablica);

    return 0;
}