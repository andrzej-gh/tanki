#pragma once

/// klasa bazowa, wszystkich obiektow (Bonus,Gora,Las,Mina,Woda)
class CObiekt
{             
      public:                   
		    /// pusty konstruktor
            CObiekt(){};              
            virtual int Kolizja()=0;  /// wywolywana tylko przez klase bonus
            virtual void Wybuch()=0;  /// wywolywana przez znikajacy bonus- generuje nowy; lub niszczony las- zmienia bitmape i wartosc kolizyjna

            int object_id;            //< identyfikator obiektu         
            int figure;               //< ksztalt: kolo=0, kwadrat=1
            float x,y;                //< wspolrzedne punktu srodka
            float skladowa;           //< np. bok, przekatna, promien, cokolwiek
            int kol_id;               //< 0-jeziro i zniszczony las, 1-las, 2-gory, 3-mina 4-bonus
                                      //< kolizja pocisku z kol_id=0- nic sie nie dzieje, 1-las i pocisk sie niszcza, 2-pocisk sie niszczy, 3,4-nic sie nie dzieje
                                      //< kolizja czolgu z kol_id=0-2, czolg nie moze przejechac; 3-czolg dostaje obrazenia, zmienia mu sie predkosc, mina znika
            int bonus_id;             //< 0-"HP+=50", 1-"HP+=150", 2-"armor+=100", 3-"speed=1.5", 4-"iloscM+=5", 5-"iloscL+=10"
            int bm_id;                //< zawiera informacje o rodzaju nakladanej bitmapy
};
