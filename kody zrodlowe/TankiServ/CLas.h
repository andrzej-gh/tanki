#pragma once
#include "cobiekt.h"

/// klasa dziedziczna klasy CObiekt, definiuje funkcje dla Drzew
class CLas: public CObiekt 
{
	 public:
		    /// konstruktor klasy CLas, przekazuje polozenie, wielkosc, ksztalt,  rodzaj bonusa i nakladanej bitmapy
            virtual int Kolizja();
            CLas(float X, float Y, float SKLADOWA,int FIGURE, int BM); 
            virtual void Wybuch();                                     /// Gdy las zostanie trafiony, to sie niszczy i zmienia jego wartosc kolizyjna
};