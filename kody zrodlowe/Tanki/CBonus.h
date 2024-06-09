#pragma once
#include "cobiekt.h"

/// klasa dziedziczna klasy CObiekt, definiuje funkcje dla bonusow
class CBonus: public CObiekt  
{
     public:
		    /// konstruktor klasy CBonus, przekazuje polozenie,  rodzaj bonusa i nakladanej bitmapy
            CBonus(int X, int Y, int BONUS, int BM); 
            virtual int Kolizja();                   /// przy generowaniu bonusow sprawdza, czy bonus nie upadl na wode, drzewo, badz gore, jak tak to go generuje od nowa
            virtual void Wybuch();                   /// wywolywana przy zebraniu bonusa, generuje nowy w innym miejscu.
};