//POP 2020-12-10 projekt 1 Witold Graczyk EIT 2  184906 DEV-C++ 5.11 kompilator TDM GCC 4.9.2 64 bit
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

const unsigned int ROZMIAR=7;

void gornaramka()
{   
	cout<< "o==[]:::::::::::::::::::>";
}
void dolnaramka()
{
	cout<< "<:::::::::::::::::::[]==o"<<endl;
}
void rysuj(char plansza[ROZMIAR][ROZMIAR], int& energia, int& moc, int& skarb) //Generowanie ramek planszy
{
	system("cls");
	gornaramka(); 
	cout<<endl;
	for (int i = 0; i < ROZMIAR; i++) 
	{   cout<< " |";
		for (int j = 0; j < ROZMIAR; j++)
		{
			cout <<setw(2)<< plansza[i][j] << ' ';
		}
		cout<< "|";
		cout << endl;
	}
	dolnaramka(); 
	cout<<endl;
	cout << "energia: " << energia << endl;
	cout << "moc: " << moc << endl;
	cout << "skarby: " << skarb << endl;
	cout << "W ktora strone chcesz zwiedzac swiat? :";

}

char losujpole()  //losowanie pola, po % tego co bylo w polecaniu
{
	char z = 0;
	int x = ((rand() % 100) + 1);
	if (x <= 1)
	{
		z = 'M';
	}
	if (x > 1 && x <= 4)
	{
		z = '$';
	}
	if (x > 4 && x <= 10)
	{
		z = 'p';
	}
	if (x > 10 && x <= 20)
	{
		z = 'j';
	}
	if (x > 20 && x <= 35)
	{
		z = 'g';
	}
	if (x > 35 && x <= 100)
	{
		z = '_';
	}
	return z;
}

void przesuwaniezwiadowcy(int x, int y, char plansza[ROZMIAR][ROZMIAR], int& energia, int& moc, int& skarb,int &iloscruchow)
{
	switch (plansza[x][y]) //zakladam �e jak schodze z jakiegos pola to zostawiam tam lad
	{
	case '_':
		
			
		iloscruchow+=1;
		plansza[3][3] = '_';
		plansza[x][y] = 'z';
	    
		break;
	case 'g':
		if(moc > 0)
		{
	        iloscruchow += 1;
		    plansza[3][3] = '_';
			plansza[x][y] = 'z'; //Po uzyciu mocy gora znika (taka moc ze niszczee gore)
			
			moc -= 1;
		}
		break;
	case 'j':
		iloscruchow += 1;
		plansza[3][3] = '_';
		plansza[x][y] = 'z';
		energia += 3;
		break;
	case 'p':
		iloscruchow += 1;
		plansza[3][3] = '_';
		plansza[x][y] = 'z';
		energia = 0; 					//przegrana
		break;
	case 'M':
		iloscruchow += 1;
		plansza[3][3] = '_';
		plansza[x][y] = 'z';
		moc += 1;
		break;
	case '$':
		iloscruchow += 1;
		plansza[3][3] = '_';
		plansza[x][y] = 'z';
		skarb++;
		break;

	}
}

void ruch(int kierunek, char plansza[ROZMIAR][ROZMIAR],int &energia, int &moc, int &skarb,int &iloscruchow) //przesywanie tab w zalezonci od kieruni
{
	if (kierunek == 1) 
	{
		przesuwaniezwiadowcy(2, 3, plansza, energia, moc, skarb,iloscruchow);
		if (plansza[3][3] != 'z')
		{
			energia--;
			for (int i = ROZMIAR - 1; i > 0; i--)
			{
				for (int j = 0; j < ROZMIAR; j++)  //wgore
				{
					plansza[i][j] = plansza[i - 1][j];
				}
			}
			for (int j = 0; j < ROZMIAR; j++)
			{
				plansza[0][j] = losujpole();
			}
		}
	}
	else if (kierunek == 2)
	{
		przesuwaniezwiadowcy(4, 3, plansza, energia, moc, skarb,iloscruchow);
		if (plansza[3][3] != 'z')
		{
			energia--;
			for (int i = 0; i < ROZMIAR - 1; i++)
			{
				for (int j = 0; j < ROZMIAR; j++)  //w dol
				{
					plansza[i][j] = plansza[i + 1][j];
				}
			}
			for (int j = 0; j < ROZMIAR; j++)
			{
				plansza[ROZMIAR - 1][j] = losujpole();
			}
		}
	}
	else if (kierunek == 3)
	{
		przesuwaniezwiadowcy(3, 2, plansza, energia, moc, skarb,iloscruchow);
		if (plansza[3][3] != 'z')
		{
			energia--;
			for (int i = ROZMIAR - 1; i > 0; i--)
			{
				for (int j = 0; j < ROZMIAR; j++)
				{
					plansza[j][i] = plansza[j][i - 1];   //w lewo
				}
			}
			for (int j = 0; j < ROZMIAR; j++)
			{
				plansza[j][0] = losujpole();
			}
		}
	}
	else if (kierunek == 4)
	{
		przesuwaniezwiadowcy(3, 4, plansza, energia, moc, skarb,iloscruchow);
		if (plansza[3][3] != 'z')
		{
			energia--;
			for (int i = 0; i < ROZMIAR - 1; i++)
			{
				for (int j = 0; j < ROZMIAR; j++)
				{
					plansza[j][i] = plansza[j][i + 1];   //w prawo
				}
			}
			for (int j = 0; j < ROZMIAR; j++)
			{
				plansza[j][ROZMIAR-1] = losujpole();
			}
		}
	}
}

void wypiszsterowanie()
{
	cout<<endl<< "Sterowanie" <<endl;
	cout<< "w -> Na Przod"<<endl;
	cout<< "s -> Na Dol"<<endl;
	cout<< "a -> W Lewo"<<endl;
	cout<< "d -> W Prawo"<<endl;
	cout<< "po wpisaniu kazdego ruchu zatwierdzasz go enterem!"<<endl; //bo nie mozna conio.h :/ a nie wiem jak inaczej
	cout<< "mozesz wykonac pare ruchow za 1 razem, jak jestes kozakiem ale nie polecam bo jak wejdziesz na pulapke albo skoncza sie ruchy to sie buguje i dzieja sie dziwne rzeczy xD"<<endl;
}

void wypiszzasady()
{
	cout<< "Chodzisz se po swiecie i szukasz skarbow ($)" <<endl;
	cout<< "p- pulapka (wchodzisz raz i przegrywasz)" <<endl;
	cout<< "$ skarb (wchodzisz razy 5-wygywasz)" <<endl;
	cout<< "M-mozesz (Mozesz niczyc gory :DD)" <<endl;
	cout<< endl << endl << endl;
	
}

void wypisztabele() //tabelka z wynikami z pliku
{
 fstream plik; 
 
    plik.open("wyniki.txt"); 
    string linia;
 
    do
    {
        getline(plik, linia); 
        cout << linia << endl; 
    }
    while(linia != "");  
 
    plik.close(); 
}

void grajdalejczywyjdz(int &grajdalej)
{
		cout<< "1.zagraj jeszcze raz" << endl << "2 wyjdz" << endl;
		int wybor;
		cin>> wybor;
		switch (wybor)
		{
		case 1: grajdalej++; break;
		case 2: exit(0); break;
	    }
	
}


void startgry(int &iloscruchow,int &energia,bool &przegrana, int &grajdalej, float &wynik)
{
		srand(time(0));

	int moc = 0;
	int skarb = 0;
	char plansza[ROZMIAR][ROZMIAR];
	string imie;

	//GENEROWNIE PIERSZEJ PLANSZY
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			plansza[i][j] = losujpole();
		}
	}
	plansza[3][3] = 'z';


	rysuj(plansza,energia,moc,skarb); //Funkcja do ramek

	while (energia > 0 && skarb < 5)
	{
		rysuj(plansza, energia, moc, skarb);
		char znak;
		cin>> znak;
		switch (znak)
		{
		case 'w':
			ruch(1, plansza, energia, moc, skarb,iloscruchow);
			break;
		case 's':
			ruch(2, plansza, energia, moc, skarb,iloscruchow);
			break;
		case 'a':
			ruch(3, plansza, energia, moc, skarb,iloscruchow);
			break;
		case 'd':
			ruch(4, plansza, energia, moc, skarb,iloscruchow);
			break;
		default: cout<<"Sterowanie na W S A D";
			break;
		}
		
	}
	if (energia <= 0)
	{
		cout << "Przegrales" << endl;
		przegrana=true;
	    grajdalejczywyjdz(grajdalej);
	}
	else if (skarb >= 5)
	{
		cout << "Wygrales" << endl;
		
		if (przegrana == false)
{
cout<< "ilosc ruchow: " << iloscruchow << endl; 
   cout<< "posostala energia: " << energia << endl; 
      wynik = energia - iloscruchow/10;                //zapis do tabelii(dodatkowe)
        cout<< "wynik: "<< wynik << endl << endl;
         cout<< "Podaj swoj nick/imie (bez spacji)" <<endl;
         cin>>imie;
         
         fstream plik;
            plik.open( "wyniki.txt" , ios::out | ios::app);
               plik<< "Wynik: " << wynik << " gracza: " << imie << endl;
               plik.close();                
}

		grajdalejczywyjdz(grajdalej); 
	}
	
}

int main() 
{
	
	cout<<"ogolnie zakladam, ze dane sa wpisywanie poprawnie"<<endl<<endl;
	
int grajdalej=0;
while(grajdalej<10){
   int wybor;
       int starter = 0;
          int iloscruchow = 0; //nie wiem co tu komentowac, no wszystkie zmienne sa opisane tak, ze wiadmo co oznaczaja
              int energia = 30;
                  float wynik = 0;
                      bool przegrana = false;
                          string imie;
    
    
    	
    while(starter == 0){
		cout<< "Wybierz:" <<endl<< "1.Sterowanie" <<endl<< "2.zasady" <<endl<< "3.I od nowa gra gotowa" << endl << "4.Wypisz tabele wynikow" <<endl;
			cin>> wybor;
	switch (wybor)
	{
	case 1: wypiszsterowanie(); break;
	case 2: wypiszzasady(); break;
	case 3: startgry(iloscruchow, energia, przegrana, grajdalej, wynik); starter+=1; break;
	case 4: wypisztabele(); break;
    }  
}

}
	return 0;
}
