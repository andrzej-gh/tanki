#pragma once

/**
* \file Tani.h
* \author Ró¿añski Piotr
* \author Wilczyñski Andrzej
* \author Witkowski Stefan
* \date 21-06-2007
*/

/// klasa czolgu, zawiera funkcje i zmienne czolgu
class CTank 
{
public:
		    /// konstruktor, przekazuje do czolgu rodzaj ladowanej bitmapy, wspolrzedne polozenia, kolor gracza i nick gracza sterujacego danym czolgiem
			CTank(int BM, int X, int Y,int kol,char* nick);  
			void Jazda(int i);        /// wywo³uje siê po wciœniêciu klawiszy W lub S, zmienia step_id
			int Kolizja();            /// sprawdza, czy czolg  nie koliduje z innym elementem na mapie
			void Mina();              /// po wcisnieciu M wywolywana jest ta funkcja i jesli gracz ma miny to tworzy nowa mine
			int Obrazenia(int DMG);   /// wywolywana jest po kolizji z pociskiem lub mina i zmiejsza armor i/badz zycie danego czolgu
			void Obrot(int i);        /// po wcisnieciu A lub D wywolywana jest ta funkcja i zmienia ona kat obrotu czolgu
			void Przesun();           /// wywolywana co cykl timera, przesuwa czolg na podstawie jego zmiennych
			void Strzelaj();          /// tworzy nowy pocisk jesli shot_reload=0
			void Wybuch();            /// niszczy czolg, tworzy go w nowym nieznanym polozeniu
			void ZmianaBroni(int i);  /// zmienia bron po wcisnieciu Q lub E, E dziala tylko jesli liczbaL jest wieksza od 0

			char name[20];            //< nick gracza
			int bm_id;                //< identyfikuje bitmape
			int tank_id;              //< kolor
			float x, y;               //< wspolrzedne polozenia
			float phi;                //< kat obrotu (wielokrotnosc pi/8)
		    float przekatna;          //< rozmiar czolgu; potrzebny tylko do obliczania kolizji
		    int score;                //< liczba fragow
			int HP, armor;            //< liczba zycia i pancerza
			int weapon_id;            //< identyfikator aktywnej bronii
			int iloscM, iloscL;       //< ilosc min i ilosc lasera
			float step;               //< odleglosc jaka czolg pokonuje podczas jednego kroku 
			int step_id;              //< identyfikator wykonywanego ruchu, moze miec wartosci -1,0,1; przod, stoi, wstecz
			float speed;              //< predkosc: podstawowa 1, po wjechaniu w mine 0.75 na 10s, po wjechaniu na speed bonus 1.5 na 20s
			int dmg_min, dmg_max;     //< zakres zadawanych obrazen przez normalny pocisk (laser jest zwiekszony o 50)
			int shot_time;            //< czas wykonywanego przeladowania
			int speed_time;           //< czas bonusowego speeda 
			int shot_reload;          //< jesli 1-"przeladowanie", 0-"pocisk w komorze"
			float bonus_speed;        //< jesli 1-czolg pod wplywem jakiejs modyfikacji predkosci, 0-speed=1
};
