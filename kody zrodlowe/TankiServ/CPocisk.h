#pragma once

/// klasa pocisku, zawiera funkcje i zmienne pociskow
class CPocisk 
{
      public:
            /// konstruktor pocisku, przekazuje informacje i bitmapie, polozeniu, kacie lotu, obrazeniach i o czolgu, ktory wystrzelil dany pocisk
            CPocisk(int BM, float X, float Y, float PHI, int DMG, int TANK); 
            int Kolizja();          /// sprawdza, czy pocisk w cos trafil; 
            void Lot();             /// przemieszcza pocisk;
            void Wybuch();          /// niszczy pocisk;
            
            int bm_id;              //< identyfikaor bitmapy pocisku (laser albo zwykly pocisk)
            int shot_id;            //< identyfikator pocisku
            float step;             //< odleglosc jaka przebywa pocisk podczas jednego cyklu zegarowego           
            int step_id;            //< ilosc krokow jakie wykona pocisk, jesli na nic nie natrafi
            int dmg;                //< obrazenia jakie zada pocisk jak kolizja==1 przekazywane z czolgu
            float x, y;             //< wspolrzedne grotu pocisku
            float phi;              //< kat lotu i dana do oblicznia punktu z ktorego stratuje pocisk;      
            int tank;               //< zawiera informacje, ktory czolg wystrzelil dany pocisk, zeby wiedziec, komu ew. przydzielic punkt;      
};
