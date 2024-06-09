#pragma once
#include "cobiekt.h"

/// klasa dziedziczna klasy CObiekt, definiuje funkcje dla Wody
class CWoda: public CObiekt 
{
	 public:
		    /// konstruktor klasy CWoda, przekazuje polozenie, wielkosc, ksztalt,  rodzaj bonusa i nakladanej bitmapy
            CWoda(float X, float Y, float SKLADOWA, int FIGURE, int BM); 
            virtual int Kolizja();
            virtual void Wybuch();
};